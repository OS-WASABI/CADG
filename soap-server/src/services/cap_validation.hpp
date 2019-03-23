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
#include "../gSOAPFiles/soapH.h"
#include <time.h>
#include <regex>

namespace cap_validation {

    // TODO(All): Create a DAO for this and maintain in DB.
    // SAME event codes per FCC Part 11.31 paragraph (e)
    static const std::array<std::string, 56> SAME_EVENT_CODES {"EAN", "NIC", "NPT", "RMT", "RWT"
                , "ADR", "AVW", "AVA", "BZW", "BLU", "CAE", "CDW", "CEM", "CFW", "CFA"
                , "DSW", "EQW", "EVI", "EWW", "FRW", "FFW", "FFA", "FFS", "FLW", "FLA"
                , "FLS", "HMW", "HWW", "HWA", "HUW", "HUA", "HLS", "LEW", "LAE", "NMN"
                , "TOE", "NUW", "DMO", "RHW", "SVR", "SVA", "SVS", "SPW", "SMW", "SPS"
                , "SSA", "SSW", "TOR", "TOA", "TRW", "TRA", "TSW", "TSA", "VOW", "WSW", "WSA"};

    // SAME org codes per FCC Part 11.31 paragraph (d)
    static const std::array<std::string, 4> SAME_ORG_CODES {"EAS", "CIV", "WXR", "RMT"};

    static std::string time_t_to_xml_dt_string(const time_t &time) {
        struct tm* time_info = localtime(&time);
        char date_buffer [27];
        strftime (date_buffer, 27,"%FT%T%z", time_info);
        std::string date_str = date_buffer;
        if (date_str.size() > 2)
            date_str = date_str.substr(0, date_str.size() - 2) + ":" + date_str.substr(date_str.size() - 2);
        return date_str;
    }

    static void string_to_vector(std::string s, const std::string &delimiter, std::vector<std::string> &elems) {
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

    static bool validate_circle_string(const std::string &circle_string) {
        std::regex pattern {"-?\\d+(\\.\\d+)?,-?\\d+(\\.\\d+)?\\s\\d+(\\.\\d+)?"};
        return std::regex_match(circle_string, pattern);
    }

    static bool validate_coordinate_pair_string(const std::string &coordinate_pair) {
        std::regex pattern {"-?\\d+(\\.\\d+)?,-?\\d+(\\.\\d+)?"};
        return std::regex_match(coordinate_pair, pattern);
    }

    static bool validate_soap_alert_info_resource(const _ns4__alert_info_resource resource) {
        try {
            auto &logger(cadg_soap::Logger::Instance());

            logger.Log(cadg_soap::LogLevel::DEBUG, "Validating required CAP info resource fields...", "cap_validation", "validate_soap_alert_info_resource");
            // Validate required fields.
            logger.Log(cadg_soap::LogLevel::DEBUG, "Info resource resourceDesc: " + resource.resourceDesc, "cap_validation", "validate_soap_alert_info_resource");
            if (resource.resourceDesc == "" ) {
                return false;
            }
            logger.Log(cadg_soap::LogLevel::DEBUG, "Info resource mimeType: " + resource.mimeType, "cap_validation", "validate_soap_alert_info_resource");
            if (resource.mimeType == "" ) {
                // TODO(All): Decide if this is required.
                // This is required according to the documentation but missing from examples.
                // The list of mime types appears to be extensive.
                return false;
            }
            if (resource.uri) {
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info resource URI: " + *resource.uri, "cap_validation", "validate_soap_alert_info_resource");
                // TODO(All): Validate URI format.
                // Note: relative URI's are supported (to the derefUri element).
            }
            if (resource.derefUri) {
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info resource dereferenced URI: " + *resource.derefUri, "cap_validation", "validate_soap_alert_info_resource");
                // TODO(All): Validate URI format.
            }
            return true;
        } catch (...) {
            return false;
        }
    }

    static bool validate_soap_alert_info_area(const _ns4__alert_info_area area) {
        try {
            auto &logger(cadg_soap::Logger::Instance());

            logger.Log(cadg_soap::LogLevel::DEBUG, "Validating required CAP info area fields...", "cap_validation", "validate_soap_alert_info_area");
            // Validate required fields.
            logger.Log(cadg_soap::LogLevel::DEBUG, "Info area areaDesc: " + area.areaDesc, "cap_validation", "validate_soap_alert_info_area");
            if (area.areaDesc == "" ) {
                return false;
            }
            for (auto circle = area.circle.begin(); circle != area.circle.end(); ++circle) {
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info area circle: " + *circle, "cap_validation", "validate_soap_alert_info_area");
            if (!validate_circle_string(*circle)) {
                    logger.Log(cadg_soap::LogLevel::DEBUG, "Info area circle elements.", "cap_validation", "validate_soap_alert_info_area");
                    return false;
                }
            }
            for (auto polygon = area.polygon.begin(); polygon != area.polygon.end(); ++polygon) {
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info area polygon: " + *polygon, "cap_validation", "validate_soap_alert_info_area");
                std::vector<std::string> coordinate_pairs;
                string_to_vector(*polygon, " ", coordinate_pairs);
                if (coordinate_pairs.size() < 4) {
                    logger.Log(cadg_soap::LogLevel::DEBUG, "Info area polygon: not enough coordinate pairs.", "cap_validation", "validate_soap_alert_info_area");
                    return false;
                }
                for (auto coordinate_pair = coordinate_pairs.begin(); coordinate_pair != coordinate_pairs.end(); ++coordinate_pair) {
                    if (!validate_coordinate_pair_string(*coordinate_pair)) {
                        logger.Log(cadg_soap::LogLevel::DEBUG, "Info area polygon: Invalid coordinate pair.", "cap_validation", "validate_soap_alert_info_area");
                        return false;
                    }
                }
                if (coordinate_pairs[0] != coordinate_pairs[coordinate_pairs.size() - 1]) {
                    logger.Log(cadg_soap::LogLevel::DEBUG, "Info area polygon: Start and end coordinates do not match.", "cap_validation", "validate_soap_alert_info_area");
                    return false;
                }
            }
            for (auto geocode = area.geocode.begin(); geocode != area.geocode.end(); ++geocode) {
                // TODO(All): Validate geocodes.
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info area geocode valueName: " + geocode->valueName, "cap_validation", "validate_soap_alert_info_area");
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info area geocode value: " + geocode->value, "cap_validation", "validate_soap_alert_info_area");
            }
            if (area.ceiling && !area.altitude) {
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info area ceiling used without altitude.", "cap_validation", "validate_soap_alert_info_resource");
                return false;
            }
            return true;
        } catch (...) {
            return false;
        }
    }

    static bool validate_soap_alert_info(const _ns4__alert_info info) {
        try {
            auto &logger(cadg_soap::Logger::Instance());

            logger.Log(cadg_soap::LogLevel::DEBUG, "Validating required CAP info fields...", "cap_validation", "validate_soap_alert_info");
            // Validate required fields.
            if (info.category.size() < 1) {
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info category missing.", "cap_validation", "validate_soap_alert_info");
                return false;
            }
            for (auto category = info.category.begin(); category != info.category.end(); ++category) {
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info category: " + std::to_string(*category), "cap_validation", "validate_soap_alert_info");
                if (*category < 0) {
                    return false;
                }
            }
            logger.Log(cadg_soap::LogLevel::DEBUG, "Info event: " + info.event, "cap_validation", "validate_soap_alert_info");
            if (info.event == "") {
                return false;
            }
            logger.Log(cadg_soap::LogLevel::DEBUG, "Info urgency: " + std::to_string(info.urgency), "cap_validation", "validate_soap_alert_info");
            if (info.urgency < 0) {
                return false;
            }
            logger.Log(cadg_soap::LogLevel::DEBUG, "Info severity: " + std::to_string(info.severity), "cap_validation", "validate_soap_alert_info");
            if (info.severity < 0) {
                return false;
            }
            logger.Log(cadg_soap::LogLevel::DEBUG, "Info certainty: " + std::to_string(info.certainty), "cap_validation", "validate_soap_alert_info");
            if (info.certainty < 0) {
                // TODO(All): Modify generated gSoap object to recognize "Very Likely" as "Likely".
                return false;
            }
            if (info.expires && *info.expires > 0) {
                //TODO(All): Alert.expires should change from a pointer to a required element if we update gSoap with IPAWS profile schema.
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info expires: " + std::to_string(*info.expires), "cap_validation", "validate_soap_alert_info");
            } else {
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info expires missing.", "cap_validation", "validate_soap_alert_info");
                return false;
            }

            if (info.eventCode.size() < 1) {
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info eventCode missing.", "cap_validation",
                           "validate_soap_alert_info");
                return false;
            }
            // TODO(All): Decide if SAME validation belongs here. Pertains to both eventCode and parameter.
            // The below requirement for eventCode with a valueName SAME is dependant upon intended dissemination type.
            // We may want to allow these to pass validation, but then perform this check when sending outgoing messages.
            int same_event_code_count = 0;
            for (auto event_code = info.eventCode.begin(); event_code != info.eventCode.end(); ++event_code) {
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info eventCode valueName: " + event_code->valueName, "cap_validation", "validate_soap_alert_info");
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info eventCode value: " + event_code->value, "cap_validation", "validate_soap_alert_info");
                if (event_code->valueName == "SAME") {
                    same_event_code_count++;
                    if (same_event_code_count > 1) {
                        logger.Log(cadg_soap::LogLevel::DEBUG, "Multiple SAME codes provided.", "cap_validation", "validate_soap_alert_info");
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
                        logger.Log(cadg_soap::LogLevel::DEBUG, "Info eventCode: valid SAME event not provided.", "cap_validation", "validate_soap_alert_info");
                        return false;
                    }
                }
            }

            int same_parameter_count = 0;
            for (auto parameter = info.parameter.begin(); parameter != info.parameter.end(); ++parameter) {
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info parameter valueName: " + parameter->valueName, "cap_validation", "validate_soap_alert_info");
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info parameter value: " + parameter->value, "cap_validation", "validate_soap_alert_info");
                if (parameter->valueName == "EAS-ORG") {
                    same_parameter_count++;
                    if (same_parameter_count > 1) {
                        logger.Log(cadg_soap::LogLevel::DEBUG, "Multiple SAME org codes provided.", "cap_validation", "validate_soap_alert_info");
                        return false;
                    }
                    bool same_org_code_found = false;
                    for (auto same_code = SAME_ORG_CODES.begin(); same_code != SAME_ORG_CODES.end(); ++same_code) {
                        if (*same_code == parameter->value) {
                            same_org_code_found = true;
                            break;
                        }
                    }
                    if (!same_org_code_found) {
                        logger.Log(cadg_soap::LogLevel::DEBUG, "Info parameter: valid SAME org code not provided.", "cap_validation", "validate_soap_alert_info");
                        return false;
                    }
                }
            }

            logger.Log(cadg_soap::LogLevel::DEBUG, "Validating optional CAP info fields...", "cap_validation", "validate_soap_alert_info");
            // Validate optional fields.
            if (info.language) {
                // TODO(All): Implement a language table per [RFC 3066] and validate this element.
            }
            for (auto response_type = info.responseType.begin(); response_type != info.responseType.end(); ++response_type) {
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info responseType: " + std::to_string(*response_type), "cap_validation", "validate_soap_alert_info");
                if (*response_type < 0) {
                    return false;
                }
            }

            for (auto resource = info.resource.begin(); resource != info.resource.end(); ++resource) {
                if (!validate_soap_alert_info_resource(*resource)) {
                    return false;
                }
            }
            if (info.area.size() < 1) {
                logger.Log(cadg_soap::LogLevel::DEBUG, "Info area missing.", "cap_validation", "validate_soap_alert_info");
                return false;
            }
            for (auto area = info.area.begin(); area != info.area.end(); ++area) {
                if (!validate_soap_alert_info_area(*area)) {
                    return false;
                }
            }
            return true;
        } catch (...) {
            return false;
        }
    }

    static bool validate_soap_alert(const _ns4__alert &alert) {
        try {
            auto &logger(cadg_soap::Logger::Instance());
            logger.Log(cadg_soap::LogLevel::DEBUG, "Validating required CAP fields...", "cap_validation", "validate_soap_alert");

            // Validate required fields.
            logger.Log(cadg_soap::LogLevel::DEBUG, "Identifier: " + alert.identifier, "cap_validation", "validate_soap_alert");
            if (alert.identifier == "") {
                // TODO(All): Validate uniqueness against DAO.
                return false;
            }
            logger.Log(cadg_soap::LogLevel::DEBUG, "Sender: " + alert.sender, "cap_validation", "validate_soap_alert");
            if (alert.sender == "") {
                // TODO(All): Validate valid sender against DAO.
                return false;
            }
            logger.Log(cadg_soap::LogLevel::DEBUG, "Sent: " + std::to_string(alert.sent), "cap_validation", "validate_soap_alert");
            if (alert.sent <= 0) {
                // TODO(All): Constrain dates logically?
                return false;
            }
            logger.Log(cadg_soap::LogLevel::DEBUG, "Status: " + std::to_string(alert.status), "cap_validation", "validate_soap_alert");
            if (alert.status < 0) {
                return false;
            }
            logger.Log(cadg_soap::LogLevel::DEBUG, "Message Type: " + std::to_string(alert.msgType), "cap_validation", "validate_soap_alert");
            if (alert.msgType < 0) {
                return false;
            }
            logger.Log(cadg_soap::LogLevel::DEBUG, "Scope: " + std::to_string(alert.scope), "cap_validation", "validate_soap_alert");
            if (alert.scope < 0) {
                return false;
            }
            logger.Log(cadg_soap::LogLevel::DEBUG, "Code vector size: " + std::to_string(alert.code.size()), "cap_validation", "validate_soap_alert");
            if (alert.code.size() == 0) {
                // TODO(All): Is this really required? It is required per the IPAWS profile but omitted in examples.
                return false;
            }
            bool ipaws_profile_code_found = false;
            for (int i = 0; i < alert.code.size(); ++i) {
                logger.Log(cadg_soap::LogLevel::DEBUG, "Code[" + std::to_string(i+1) + "]: " + alert.code[i], "cap_validation", "validate_soap_alert");
                if (alert.code[i].find("IPAWSv1.0") != std::string::npos) {
                    ipaws_profile_code_found = true;
                    break;
                }
            }
            if (!ipaws_profile_code_found)
                return false;
            // Validate conditional fields.
            if (alert.restriction && *alert.restriction != "") {
                logger.Log(cadg_soap::LogLevel::DEBUG, "Restriction: " + *alert.restriction, "cap_validation", "validate_soap_alert");
            } else if (alert.scope == _ns4__alert_scope__Restricted) {
                logger.Log(cadg_soap::LogLevel::DEBUG, "No restriction provided with restricted scope.",
                           "cap_validation", "validate_soap_alert");
                // TODO(All): Decide if this required if scope is restricted.
                return false;
            }
            if (alert.addresses && *alert.addresses != "") {
                logger.Log(cadg_soap::LogLevel::DEBUG, "Addresses: " + *alert.addresses, "cap_validation", "validate_soap_alert");
                if (!validate_addresses(*alert.addresses)) {
                    logger.Log(cadg_soap::LogLevel::DEBUG, "Invalid format for addresses.", "cap_validation", "validate_soap_alert");
                    return false;
                }
            } else if (alert.scope == _ns4__alert_scope__Private) {
                logger.Log(cadg_soap::LogLevel::DEBUG, "No addresses provided with private scope.", "cap_validation", "validate_soap_alert");
                return false;
            }
            // Validate  optional fields.
            if (alert.references && alert.references->empty()) {
                logger.Log(cadg_soap::LogLevel::DEBUG, "References string: " + *alert.references, "cap_validation", "validate_soap_alert");
                if (!validate_references(*alert.references)){
                    logger.Log(cadg_soap::LogLevel::DEBUG, "Invalid reference format.", "cap_validation", "validate_soap_alert");
                    return false;
                }
            }
            // Validate alert info.
            logger.Log(cadg_soap::LogLevel::DEBUG, "Validating alert info.", "cap_validation", "validate_soap_alert");
            std::vector<_ns4__alert_info> infos = alert.info;
            if (infos.size() < 1)
                return false;
            for (auto info = infos.begin(); info != infos.end(); ++info) {
                if (!validate_soap_alert_info(*info)) {
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