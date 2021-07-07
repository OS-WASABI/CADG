/// Converts any syntactically correct SOAP CAP document into a CMAC XML document.
/**
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file    cmac_converter.cpp
 * @authors Ross Arcemont
 * @date    January, 2019
 */
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <ctime>
#include "cmac_converter.hpp"
#include "../pugixml-1.9/src/pugixml.hpp"
#include "../pugixml-1.9/src/pugixml.cpp"
#include "../../rest-server/src/model/cmac/cmac_alert.hpp"

void CMAC::convert(CADG_REST_SERVER_CMAC_ALERT_HPP::cmac::CMAC_alert alert_content, std::string cmac_filename) {
    // Obtaining the current date-time for later use.
    std::time_t time = std::time(0);
    std::tm* current_date_time = std::localtime(&time);
    // TODO(Ross): Ensure correctness
    std::string date_time_str = std::to_string((current_date_time->tm_year + 1900)) +
                                '-' + std::to_string((current_date_time->tm_mon + 1)) +
                                '-' + std::to_string(current_date_time->tm_mday) +
                                'T' + std::to_string(current_date_time->tm_hour) +
                                ':' + std::to_string(current_date_time->tm_min) +
                                ':' + std::to_string(current_date_time->tm_sec) + 'Z';

    // Pulling the SOAP CAP document into memory.
//    pugi::xml_document soap_doc;
//    pugi::xml_parse_result result = soap_doc.load_file(soap_filename.c_str());
//    pugi::xml_node cap_message = soap_doc.first_child().first_child().first_child();

    // Creating the CMAC document and declaring its root node.
    pugi::xml_document cmac_doc;
    pugi::xml_node declaration_node = cmac_doc.append_child(pugi::node_declaration);
    declaration_node.append_attribute("version") = "1.0";
    pugi::xml_node root_node = cmac_doc.append_child("CMAC_Alert_Attributes");
    root_node.append_attribute("xmlns") = "cmac:2.0";  // TODO(Ross): Check value. Potentially temporary.

    // Creating the node structure and node content for the CMAC_Alert_Attributes block.
    // All node variable names match the corresponding CMAC structure as closely as possible.
    pugi::xml_node cmac_protocol_version = root_node.append_child("CMAC_protocol_version");
    cmac_protocol_version.text().set(alert_content.cmac_protocol_version.value().c_str());

    pugi::xml_node cmac_sending_gateway_id = root_node.append_child("CMAC_sending_gateway_id");
    cmac_sending_gateway_id.text().set(alert_content.cmac_sending_gateway_id.value().c_str());

    pugi::xml_node cmac_message_number = root_node.append_child("CMAC_message_number");
    cmac_message_number.text().set(alert_content.cmac_message_number.value().c_str());

    if (alert_content.cmac_referenced_message_number) {
        pugi::xml_node cmac_referenced_message_number = root_node.append_child("CMAC_referenced_message_number");
        cmac_referenced_message_number.text().set(alert_content.cmac_referenced_message_number.value().c_str());
    }

    if (alert_content.cmac_referenced_message_cap_identifier) {
        pugi::xml_node cmac_referenced_message_cap_identifier = root_node.append_child(
                "CMAC_referenced_message_cap_identifier");
        cmac_referenced_message_cap_identifier.text().set(
                alert_content.cmac_referenced_message_cap_identifier.value().c_str());
    }

    if (alert_content.cmac_special_handling) {
        pugi::xml_node cmac_special_handling = root_node.append_child("CMAC_special_handling");
        cmac_special_handling.text().set(alert_content.cmac_special_handling.value().c_str());
    }

    if (alert_content.cmac_sender) {
        pugi::xml_node cmac_sender = root_node.append_child("CMAC_sender");
        cmac_sender.text().set(alert_content.cmac_sender.value().c_str());
    }

    pugi::xml_node cmac_sent_date_time = root_node.append_child("CMAC_sent_date_time");
    cmac_sent_date_time.text().set(date_time_str.c_str());

    pugi::xml_node cmac_status = root_node.append_child("CMAC_status");
    cmac_status.text().set(alert_content.cmac_status.value().c_str());

    pugi::xml_node cmac_message_type = root_node.append_child("CMAC_message_type");
    cmac_message_type.text().set(alert_content.cmac_message_type.value().c_str());

    if (alert_content.cmac_response_code) {
        for (int i = 0; i < alert_content.cmac_response_code.value().size(); i++) {
            pugi::xml_node cmac_response_code = root_node.append_child("CMAC_response_code");
            cmac_response_code.text().set(alert_content.cmac_response_code.value().at(i).c_str());
        }
    }

    if (alert_content.cmac_note) {
        for (int i = 0; i < alert_content.cmac_note.value().size(); i++) {
            pugi::xml_node cmac_note = root_node.append_child("CMAC_note");
            cmac_note.text().set(alert_content.cmac_note.value().at(i).c_str());
        }
    }

    if (alert_content.cmac_cap_alert_uri) {
        pugi::xml_node cmac_cap_alert_uri = root_node.append_child("CMAC_cap_alert_uri");
        cmac_cap_alert_uri.text().set(alert_content.cmac_cap_alert_uri.value().c_str());
    }

    if (alert_content.cmac_cap_identifier) {
        pugi::xml_node cmac_cap_identifier = root_node.append_child("CMAC_cap_identifier");
        cmac_cap_identifier.text().set(alert_content.cmac_cap_identifier.value().c_str());
    }

    if (alert_content.cmac_cap_sent_date_time) {
        pugi::xml_node cmac_cap_sent_date_time = root_node.append_child("CMAC_cap_sent_date_time");
        cmac_cap_sent_date_time.text().set(alert_content.cmac_cap_sent_date_time.value().c_str());
    }

    // Creating the node structure and node content for the CMAC_alert_info block.
    // All node variable names match the corresponding CMAC structure as closely as possible.
    if (alert_content.cmac_alert_info) {
        pugi::xml_node cmac_alert_info = root_node.append_child("CMAC_alert_info");
        pugi::xml_node cmac_category = cmac_alert_info.append_child("CMAC_category");
        cmac_category.text().set(alert_content.cmac_alert_info.value().cmac_category.value().c_str());

        if (alert_content.cmac_alert_info.value().cmac_response_type) {
            pugi::xml_node cmac_response_type = cmac_alert_info.append_child("CMAC_response_type");
            cmac_response_type.text().set(alert_content.cmac_alert_info.value().cmac_response_type.value().c_str());
        }

        pugi::xml_node cmac_severity = cmac_alert_info.append_child("CMAC_severity");
        cmac_severity.text().set(alert_content.cmac_alert_info.value().cmac_severity.value().c_str());

        pugi::xml_node cmac_urgency = cmac_alert_info.append_child("CMAC_urgency");
        cmac_urgency.text().set(alert_content.cmac_alert_info.value().cmac_urgency.value().c_str());

        pugi::xml_node cmac_certainty = cmac_alert_info.append_child("CMAC_certainty");
        cmac_certainty.text().set(alert_content.cmac_alert_info.value().cmac_certainty.value().c_str());

        pugi::xml_node cmac_expires_date_time = cmac_alert_info.append_child("CMAC_expires_date_time");
        cmac_expires_date_time.text().set(alert_content.cmac_alert_info.value().cmac_expires_date_time.value().c_str());

        if (alert_content.cmac_alert_info.value().cmac_sender_name) {
            pugi::xml_node cmac_sender_name = cmac_alert_info.append_child("CMAC_sender_name");
            cmac_sender_name.text().set(alert_content.cmac_alert_info.value().cmac_sender_name.value().c_str());
        }

        if (alert_content.cmac_alert_info.value().cmac_alert_area) {
            for (int j = 0; j < alert_content.cmac_alert_info.value().cmac_alert_area.value().size(); j++) {
                // Creating the node structure and node content for the CMAC_Alert_Area block.
                // All node variable names match the corresponding CMAC structure as closely as possible.
                pugi::xml_node cmac_alert_area = cmac_alert_info.append_child("CMAC_Alert_Area");
                pugi::xml_node cmac_area_description = cmac_alert_area.append_child("CMAC_area_description");
                cmac_area_description.text().set(alert_content.cmac_alert_info.value().cmac_alert_area.value().at(j)
                .cmac_area_description.value().c_str());

                if (alert_content.cmac_alert_info.value().cmac_alert_area.value().at(j).cmac_polygon) {
                    for (int k = 0;
                         k < alert_content.cmac_alert_info.value().cmac_alert_area.value().at(j)
                         .cmac_polygon.value().size();
                         k++) {
                        pugi::xml_node cmac_polygon = cmac_alert_area.append_child("CMAC_polygon");
                        cmac_polygon.text().set(alert_content.cmac_alert_info.value().cmac_alert_area.value().at(j)
                        .cmac_polygon.value().at(k).c_str());
                    }
                }

                if (alert_content.cmac_alert_info.value().cmac_alert_area.value().at(j).cmac_circle) {
                    for (int k = 0;
                         k < alert_content.cmac_alert_info.value().cmac_alert_area.value().at(j)
                         .cmac_circle.value().size();
                         k++) {
                        pugi::xml_node cmac_circle = cmac_alert_area.append_child("CMAC_circle");
                        cmac_circle.text().set(alert_content.cmac_alert_info.value().cmac_alert_area.value().at(j)
                        .cmac_circle.value().at(k).c_str());
                    }
                }

                for (int k = 0;
                     k < alert_content.cmac_alert_info.value().cmac_alert_area.value().at(j)
                     .cmac_cmas_geocode.value().size();
                     k++) {
                    pugi::xml_node cmac_cmas_geocode = cmac_alert_area.append_child("CMAC_cmas_geocode");
                    cmac_cmas_geocode.text().set(alert_content.cmac_alert_info.value().cmac_alert_area.value().at(j)
                    .cmac_cmas_geocode.value().at(k).c_str());
                }

                // Creating geocode nodes and filling with content
                if (alert_content.cmac_alert_info.value().cmac_alert_area.value().at(j).cmac_cap_geocode) {
                    for (int k = 0;
                         k < alert_content.cmac_alert_info.value().cmac_alert_area.value().at(j)
                         .cmac_cap_geocode.value().size();
                         k++) {
                        pugi::xml_node cmac_cap_geocode = cmac_alert_area.append_child("CMAC_cap_geocode");
                        pugi::xml_node value_name = cmac_cap_geocode.append_child("valueName");
                        pugi::xml_node value = cmac_cap_geocode.append_child("value");

                        value_name.text().set(alert_content.cmac_alert_info.value().cmac_alert_area.value().at(j)
                        .cmac_cap_geocode.value().at(k).first.c_str());
                        value.text().set(alert_content.cmac_alert_info.value().cmac_alert_area.value().at(j)
                        .cmac_cap_geocode.value().at(k).first.c_str());
                    }
                }


                if (alert_content.cmac_alert_info.value().cmac_alert_area.value().at(j).cmac_gnis) {
                    for (int k = 0;
                         k < alert_content.cmac_alert_info.value().cmac_alert_area.value().at(j)
                         .cmac_gnis.value().size();
                         k++) {
                        pugi::xml_node cmac_gnis = cmac_alert_area.append_child("CMAC_gnis");
                        cmac_gnis.text().set(alert_content.cmac_alert_info.value().cmac_alert_area.value().at(j)
                        .cmac_gnis.value().at(k).c_str());
                    }
                }
            }
        }

        for (int j = 0; j < alert_content.cmac_alert_info.value().cmac_alert_text.value().size(); j++) {
            // Creating the node structure and node content for the CMAC_Alert_Text block.
            // All node variable names match the corresponding CMAC structure as closely as possible.
            pugi::xml_node cmac_alert_text = cmac_alert_info.append_child("CMAC_Alert_Text");
            pugi::xml_node cmac_text_language = cmac_alert_text.append_child("CMAC_text_language");
            cmac_text_language.text().set(
            alert_content.cmac_alert_info.value().cmac_alert_text.value().at(j).cmac_text_language.value().c_str());

            pugi::xml_node cmac_short_text_alert_message_length = cmac_alert_text.append_child(
                    "CMAC_short_text_alert_message_length");
            cmac_short_text_alert_message_length.text().set(alert_content.cmac_alert_info.value()
            .cmac_alert_text.value().at(j).cmac_short_text_alert_message_length.value().c_str());

            pugi::xml_node cmac_short_text_alert_message = cmac_alert_text.append_child(
                    "CMAC_short_text_alert_message");
            cmac_short_text_alert_message.text().set(alert_content.cmac_alert_info.value().cmac_alert_text.value().at(j)
            .cmac_short_text_alert_message.value().c_str());

            pugi::xml_node cmac_long_text_alert_message_length = cmac_alert_text.append_child(
                    "CMAC_long_text_alert_message_length");
            cmac_long_text_alert_message_length.text().set(alert_content.cmac_alert_info.value().cmac_alert_text.value()
            .at(j).cmac_long_text_alert_message_length.value().c_str());

            pugi::xml_node cmac_long_text_alert_message = cmac_alert_text.append_child("CMAC_long_text_alert_message");
            cmac_long_text_alert_message.text().set(alert_content.cmac_alert_info.value().cmac_alert_text.value().at(j)
            .cmac_long_text_alert_message.value().c_str());
        }
    }

    // Creating the node structure and node content for the CMAC_Digital_Signature block.
    // All node variable names match the corresponding CMAC structure as closely as possible.
    pugi::xml_node cmac_digital_signature = root_node.append_child("CMAC_Digital_Signature");
    cmac_digital_signature.text().set(alert_content.cmac_digital_signature.value().c_str());

    // Saving CMAC document.
    bool saved = cmac_doc.save_file(cmac_filename.c_str());
}

int main() {
    // Filling in the top level of an example CMAC alert
    cmac::CMAC_alert test_alert;
    test_alert.cmac_protocol_version = "2.0";
    test_alert.cmac_sending_gateway_id = "localhost";
    test_alert.cmac_message_number = "9001";
    test_alert.cmac_referenced_message_number = "9002";
    test_alert.cmac_referenced_message_cap_identifier = "9003";
    test_alert.cmac_special_handling = "Public Safety";
    test_alert.cmac_sender = "localhost";
    test_alert.cmac_sent_date_time = "02-27-2019-11:59am";
    test_alert.cmac_status = "Actual";
    test_alert.cmac_message_type = "Alert";

    std::vector<std::string> response_codes;
    test_alert.cmac_response_code = response_codes;
    test_alert.cmac_response_code.value().push_back("1337");
    test_alert.cmac_response_code.value().push_back("42");
    test_alert.cmac_response_code.value().push_back("1138");

    std::vector<std::string> notes;
    test_alert.cmac_note = notes;
    test_alert.cmac_note.value().push_back("Elite");
    test_alert.cmac_note.value().push_back("The answer to life, the universe, and everything");
    test_alert.cmac_note.value().push_back("The princess's cell block");

    test_alert.cmac_cap_alert_uri = "localhost";
    test_alert.cmac_cap_identifier = "9004";
    test_alert.cmac_cap_sent_date_time = "02-27-2019-11:58am";
    test_alert.cmac_digital_signature = "Ross";

    // Filling in the alert_info block of the example alert
    cmac::CMAC_alert_info info_test;
    test_alert.cmac_alert_info = info_test;
    test_alert.cmac_alert_info.value().cmac_category = "CBRNE";
    test_alert.cmac_alert_info.value().cmac_response_type = "Evacuate";
    test_alert.cmac_alert_info.value().cmac_severity = "Severe";
    test_alert.cmac_alert_info.value().cmac_urgency = "Immediate";
    test_alert.cmac_alert_info.value().cmac_certainty = "Observed";
    test_alert.cmac_alert_info.value().cmac_expires_date_time = "02-28-2019-11:58am";
    test_alert.cmac_alert_info.value().cmac_sender_name = "Ross";

    // Filling in the alert_area block of the example alert
    std::vector<cmac::CMAC_alert_area> area_vector;
    test_alert.cmac_alert_info.value().cmac_alert_area = area_vector;
    cmac::CMAC_alert_area area_test;
    test_alert.cmac_alert_info.value().cmac_alert_area.value().push_back(area_test);
    test_alert.cmac_alert_info.value().cmac_alert_area.value().at(0).cmac_area_description = "The whole world";

    std::vector<std::string> polygon_vector;
    test_alert.cmac_alert_info.value().cmac_alert_area.value().at(0).cmac_polygon = polygon_vector;
    test_alert.cmac_alert_info.value().cmac_alert_area.value().at(0)
    .cmac_polygon.value().push_back("0,0 0,90 90,0 90,90");

    std::vector<std::string> circle_vector;
    test_alert.cmac_alert_info.value().cmac_alert_area.value().at(0).cmac_circle = circle_vector;
    test_alert.cmac_alert_info.value().cmac_alert_area.value().at(0).cmac_circle.value().push_back("Full");

    std::vector<std::string> cmas_geocode_vector;
    test_alert.cmac_alert_info.value().cmac_alert_area.value().at(0).cmac_cmas_geocode = cmas_geocode_vector;
    test_alert.cmac_alert_info.value().cmac_alert_area.value().at(0).cmac_cmas_geocode.value().push_back("SAME");

    std::vector<std::pair<std::string, std::string>> cap_geocode_vector;
    std::pair<std::string, std::string> cap_geocode_content;
    cap_geocode_content.first = "SAME";
    cap_geocode_content.second = "CEM";
    test_alert.cmac_alert_info.value().cmac_alert_area.value().at(0).cmac_cap_geocode = cap_geocode_vector;
    test_alert.cmac_alert_info.value().cmac_alert_area.value().at(0)
    .cmac_cap_geocode.value().push_back(cap_geocode_content);

    std::vector<std::string> gnis_vector;
    test_alert.cmac_alert_info.value().cmac_alert_area.value().at(0).cmac_gnis = gnis_vector;
    test_alert.cmac_alert_info.value().cmac_alert_area.value().at(0).cmac_gnis.value().push_back("000000");

    // Filling in the alert_text block of the example alert
    std::vector<cmac::CMAC_alert_text> text_vector;
    test_alert.cmac_alert_info.value().cmac_alert_text = text_vector;
    cmac::CMAC_alert_text text_test;
    test_alert.cmac_alert_info.value().cmac_alert_text.value().push_back(text_test);

    test_alert.cmac_alert_info.value().cmac_alert_text.value().at(0).cmac_text_language = "English";
    test_alert.cmac_alert_info.value().cmac_alert_text.value().at(0).cmac_short_text_alert_message_length = "82";
    test_alert.cmac_alert_info.value().cmac_alert_text.value().at(0).cmac_short_text_alert_message =
            "Patient Zero has escaped! The dead have risen! No one is safe! Run for your lives!";
    test_alert.cmac_alert_info.value().cmac_alert_text.value().at(0).cmac_long_text_alert_message_length = "138";
    test_alert.cmac_alert_info.value().cmac_alert_text.value().at(0).cmac_long_text_alert_message =
            "Patient Zero has escaped containment. The zombie plague is airborne. Evacuate yourself and your "
            "loved ones immediately! This is not a drill!";


    CMAC::convert(test_alert, "cmac_output_test.xml");
}
