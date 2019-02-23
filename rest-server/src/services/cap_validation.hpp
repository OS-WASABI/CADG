// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/// Functions for validating CAP Alert Messages.
/**
 * This class contains functions for validating CAP Alert Messages.
 *
 * @file        cap_validation.hpp
 * @authors     Michael McCulley
 * @date        February, 2019
 */

#ifndef CAP_VALIDATION_H
#define CAP_VALIDATION_H
#include <logger.hpp>
#include <logger_interface.hpp>
#include "log_level.hpp"
#include "../gSoapFiles/CAP/soapH.h"
#include <time.h>
#include <regex.h>

namespace cap_validation {

    // TODO(All): Create a DAO for this and maintain in DB.
    // SAME event codes per FCC Part 11.31 paragraph (e)
    static const std::array<std::string, 56> SAME_EVENT_CODES = {"EAN", "NIC", "NPT", "RMT", "RWT"
                , "ADR", "AVW", "AVA", "BZW", "BLU", "CAE", "CDW", "CEM", "CFW", "CFA"
                , "DSW", "EQW", "EVI", "EWW", "FRW", "FFW", "FFA", "FFS", "FLW", "FLA"
                , "FLS", "HMW", "HWW", "HWA", "HUW", "HUA", "HLS", "LEW", "LAE", "NMN"
                , "TOE", "NUW", "DMO", "RHW", "SVR", "SVA", "SVS", "SPW", "SMW", "SPS"
                , "SSA", "SSW", "TOR", "TOA", "TRW", "TRA", "TSW", "TSA", "VOW", "WSW", "WSA"};

    // SAME org codes per FCC Part 11.31 paragraph (d)
    static const std::array<std::string, 4> SAME_ORG_CODES = {"EAS", "CIV", "WXR", "RMT"};

    static std::string time_t_to_xml_dt_string(const time_t &time) {
        struct tm* time_info = localtime(&time);
        char date_buffer [27];
        strftime (date_buffer, 27,"%FT%T%z", time_info);
        std::string date_str = date_buffer;
        if (date_str.size() > 2)
            date_str = date_str.substr(0, date_str.size() - 2) + ":" + date_str.substr(date_str.size() - 2);
        return date_str;
    }

    static void string_to_vector(std::string s, std::string delimiter, std::vector<std::string> &elems) {
        size_t pos = 0;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            if (s.substr(0, pos) != "" )
                elems.push_back(s.substr(0, pos));
            s.erase(0, pos + delimiter.length());
        }
        if (s != "") {
            elems.push_back(s);
        }
    }

    static std::vector<std::string> parse_double_quoted_then_spaces(std::string s) {
        std::vector<std::string> elems;
        std::string delimiter = "\"";
        size_t pos = 0;
        int start_pos = 0;
        bool in_quote = false;
        while ((pos = s.find(delimiter, start_pos)) != std::string::npos) {
            if (!in_quote) {
                string_to_vector(s.substr(0, pos), " ", elems);
                s.erase(0, pos);
                start_pos = delimiter.length();
            } else {
                if (s.substr(start_pos, pos - delimiter.length()) != "") {
                    elems.push_back(s.substr(start_pos, pos - delimiter.length()));
                }
                s.erase(0, pos + delimiter.length());
                start_pos = 0;
            }
            in_quote = !in_quote;
        }
        string_to_vector(s, " ", elems);
        return elems;
    }

    static bool validate_addresses(std::string addresses) {
        // TODO(All): Are these addresses URLs?
        return true;
    }

    static bool validate_references(std::string references) {
        std::vector<std::string> refs = parse_double_quoted_then_spaces(references);
        for (auto ref = refs.begin(); ref != refs.end(); ++ref) {
            std::vector<std::string> ref_ids;
            string_to_vector(*ref, ",", ref_ids);
            // TODO(All): Validate individual elements: (sender,identifier,sent)
            if(ref_ids.size() != 3)
                return false;
        }
        return true;
    }

    static bool validate_soap_alert_info(const _ns2__alert_info alert_info) {
        try {
            auto &logger(cadg_rest::Logger::Instance());

            logger.Log(cadg_rest::LogLevel::DEBUG, "Validating required CAP info fields...", "cap_validation", "validate_soap_alert_info");
            // Validate required fields.
            if (alert_info.category.size() < 1) {
                logger.Log(cadg_rest::LogLevel::DEBUG, "Info category missing.", "cap_validation", "validate_soap_alert_info");
                return false;
            }
            for (auto category = alert_info.category.begin(); category != alert_info.category.end(); ++category) {
                logger.Log(cadg_rest::LogLevel::DEBUG, "Info category: " + std::to_string(*category), "cap_validation", "validate_soap_alert_info");
                if (*category < 0) {
                    return false;
                }
            }
            logger.Log(cadg_rest::LogLevel::DEBUG, "Info event: " + alert_info.event, "cap_validation", "validate_soap_alert_info");
            if (alert_info.event == "") {
                return false;
            }
            logger.Log(cadg_rest::LogLevel::DEBUG, "Info urgency: " + std::to_string(alert_info.urgency), "cap_validation", "validate_soap_alert_info");
            if (alert_info.urgency < 0) {
                return false;
            }
            logger.Log(cadg_rest::LogLevel::DEBUG, "Info severity: " + std::to_string(alert_info.severity), "cap_validation", "validate_soap_alert_info");
            if (alert_info.severity < 0) {
                return false;
            }
            logger.Log(cadg_rest::LogLevel::DEBUG, "Info certainty: " + std::to_string(alert_info.certainty), "cap_validation", "validate_soap_alert_info");
            if (alert_info.certainty < 0) {
                // TODO(All): Modify generated gSoap object to recognize "Very Likely" as "Likely".
                return false;
            }
            if (alert_info.expires && *alert_info.expires > 0) {
                // TODO(All): Alert.expires should change from a pointer to a required element if we update gSoap with IPAWS profile schema.
                logger.Log(cadg_rest::LogLevel::DEBUG, "Info expires: " + *alert_info.expires, "cap_validation", "validate_soap_alert_info");
            } else {
                logger.Log(cadg_rest::LogLevel::DEBUG, "Info expires missing.", "cap_validation", "validate_soap_alert_info");
                return false;
            }
            if (alert_info.eventCode.size() < 1) {
                logger.Log(cadg_rest::LogLevel::DEBUG, "Info eventCode missing.", "cap_validation",
                           "validate_soap_alert_info");
                return false;
            }
            // TODO(All): Decide if SAME validation belongs here. Pertains to both eventCode and parameter.
            // The below requirement for eventCode with a valueName SAME is dependant upon intended dissemination type.
            int same_event_code_count = 0;
            for (auto event_code = alert_info.eventCode.begin(); event_code != alert_info.eventCode.end(); ++event_code) {
                logger.Log(cadg_rest::LogLevel::DEBUG, "Info eventCode valueName: " + (*event_code).valueName, "cap_validation", "validate_soap_alert_info");
                logger.Log(cadg_rest::LogLevel::DEBUG, "Info eventCode value: " + (*event_code).value, "cap_validation", "validate_soap_alert_info");
                if ((*event_code).valueName == "SAME") {
                    same_event_code_count++;
                    if (same_event_code_count > 1) {
                        logger.Log(cadg_rest::LogLevel::DEBUG, "Multiple SAME codes provided.", "cap_validation", "validate_soap_alert_info");
                        return false;
                    }
                    bool same_code_found = false;
                    for (auto same_code = SAME_EVENT_CODES.begin(); same_code != SAME_EVENT_CODES.end(); ++same_code) {
                        if (*same_code == (*event_code).value) {
                            same_code_found = true;
                            break;
                        }
                    }
                    if (!same_code_found) {
                        logger.Log(cadg_rest::LogLevel::DEBUG, "Info eventCode: valid SAME event not provided.", "cap_validation", "validate_soap_alert_info");
                        return false;
                    }
                }
            }

            int same_parameter_count = 0;
            for (auto parameter = alert_info.parameter.begin(); parameter != alert_info.parameter.end(); ++parameter) {
                logger.Log(cadg_rest::LogLevel::DEBUG, "Info parameter valueName: " + (*parameter).valueName, "cap_validation", "validate_soap_alert_info");
                logger.Log(cadg_rest::LogLevel::DEBUG, "Info parameter value: " + (*parameter).value, "cap_validation", "validate_soap_alert_info");
                if ((*parameter).valueName == "EAS-ORG") {
                    same_parameter_count++;
                    if (same_parameter_count > 1) {
                        logger.Log(cadg_rest::LogLevel::DEBUG, "Multiple SAME org codes provided.", "cap_validation", "validate_soap_alert_info");
                        return false;
                    }
                    bool same_org_code_found = false;
                    for (auto same_code = SAME_ORG_CODES.begin(); same_code != SAME_ORG_CODES.end(); ++same_code) {
                        if (*same_code == (*parameter).value) {
                            same_org_code_found = true;
                            break;
                        }
                    }
                    if (!same_org_code_found) {
                        logger.Log(cadg_rest::LogLevel::DEBUG, "Info parameter: valid SAME org code not provided.", "cap_validation", "validate_soap_alert_info");
                        return false;
                    }
                }
            }

            logger.Log(cadg_rest::LogLevel::DEBUG, "Validating optional CAP info fields...", "cap_validation", "validate_soap_alert_info");
            // Validate optional fields.
            if (alert_info.language) {
                // TODO(All): Implement a language table per [RFC 3066] and validate this element.
            }
            for (auto response_type = alert_info.responseType.begin(); response_type != alert_info.responseType.end(); ++response_type) {
                logger.Log(cadg_rest::LogLevel::DEBUG, "Info responseType: " + std::to_string(*response_type), "cap_validation", "validate_soap_alert_info");
                if (*response_type < 0) {
                    return false;
                }
            }
            return true;
        } catch (...) {
            return false;
        }
    }

    static bool validate_soap_alert(const _ns2__alert &alert) {
        try {
            auto &logger(cadg_rest::Logger::Instance());
            logger.Log(cadg_rest::LogLevel::DEBUG, "Validating required CAP fields...", "cap_validation", "validate_soap_alert");

            // Validate required fields.
            logger.Log(cadg_rest::LogLevel::DEBUG, "Identifier: " + alert.identifier, "cap_validation", "validate_soap_alert");
            if (alert.identifier == "") {
                // TODO(All): Validate uniqueness against DAO.
                return false;
            }
            logger.Log(cadg_rest::LogLevel::DEBUG, "Sender: " + alert.sender, "cap_validation", "validate_soap_alert");
            if (alert.sender == "") {
                // TODO(All): Validate valid sender against DAO.
                return false;
            }
            logger.Log(cadg_rest::LogLevel::DEBUG, "Sent: " + std::to_string(alert.sent), "cap_validation", "validate_soap_alert");
            if (alert.sent <= 0) {
                // TODO(All): Constrain dates logically?
                return false;
            }
            logger.Log(cadg_rest::LogLevel::DEBUG, "Status: " + std::to_string(alert.status), "cap_validation", "validate_soap_alert");
            if (alert.status < 0) {
                return false;
            }
            logger.Log(cadg_rest::LogLevel::DEBUG, "Message Type: " + std::to_string(alert.msgType), "cap_validation", "validate_soap_alert");
            if (alert.msgType < 0) {
                return false;
            }
            logger.Log(cadg_rest::LogLevel::DEBUG, "Scope: " + std::to_string(alert.scope), "cap_validation", "validate_soap_alert");
            if (alert.scope < 0) {
                return false;
            }
            logger.Log(cadg_rest::LogLevel::DEBUG, "Code vector size: " + std::to_string(alert.code.size()), "cap_validation", "validate_soap_alert");
            if (alert.code.size() == 0) {
                // TODO(All): Is this really required? It is required per the IPAWS profile but omitted in examples.
                return false;
            }
            bool ipaws_profile_code_found = false;
            for (int i = 0; i < alert.code.size(); ++i) {
                logger.Log(cadg_rest::LogLevel::DEBUG, "Code[" + std::to_string(i+1) + "]: " + alert.code[i], "cap_validation", "validate_soap_alert");
                if (alert.code[i].find("IPAWSv1.0") != std::string::npos) {
                    ipaws_profile_code_found = true;
                    break;
                }
            }
            if (!ipaws_profile_code_found)
                return false;
            // Validate conditional fields.
            if (alert.restriction && *alert.restriction != "") {
                logger.Log(cadg_rest::LogLevel::DEBUG, "Restriction: " + *alert.restriction, "cap_validation", "validate_soap_alert");
            } else if (alert.scope == _ns2__alert_scope__Restricted) {
                logger.Log(cadg_rest::LogLevel::DEBUG, "No restriction provided with restricted scope.",
                           "cap_validation", "validate_soap_alert");
                // TODO(All): Decide if this required if scope is restricted.
                return false;
            }
            if (alert.addresses && *alert.addresses != "") {
                logger.Log(cadg_rest::LogLevel::DEBUG, "Addresses: " + *alert.addresses, "cap_validation", "validate_soap_alert");
                if (!validate_addresses(*alert.addresses)) {
                    logger.Log(cadg_rest::LogLevel::DEBUG, "Invalid format for addresses.", "cap_validation", "validate_soap_alert");
                    return false;
                }
            } else if (alert.scope == _ns2__alert_scope__Private) {
                logger.Log(cadg_rest::LogLevel::DEBUG, "No addresses provided with private scope.", "cap_validation", "validate_soap_alert");
                return false;
            }
            // Validate  optional fields.
            if (alert.references && *alert.references != "") {
                logger.Log(cadg_rest::LogLevel::DEBUG, "References string: " + *alert.references, "cap_validation", "validate_soap_alert");
                if (!validate_references(*alert.references)){
                    logger.Log(cadg_rest::LogLevel::DEBUG, "Invalid reference format.", "cap_validation", "validate_soap_alert");
                    return false;
                }
            }
            // Validate alert info.
            logger.Log(cadg_rest::LogLevel::DEBUG, "Validating alert info.", "cap_validation", "validate_soap_alert");
            std::vector<_ns2__alert_info> alert_infos = alert.info;
            if (alert_infos.size() < 1)
                return false;
            for (auto alert_info = alert_infos.begin(); alert_info != alert_infos.end(); ++alert_info) {
                if (!validate_soap_alert_info(*alert_info)) {
                    return false;
                }
            }
            return true;
        } catch (...) {
            return false;
        }
    };
}
#endif //CAP_VALIDATION_H