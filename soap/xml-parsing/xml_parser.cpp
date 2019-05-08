/// Parses existing SOAP XML documents and generates new CMAC XML documents.
/**
 * This class has two primary functions: Reading and writing XML documents.
 * The read functionality parses an existing SOAP XML document and stores
 * it in memory for future use via a CAPMessage struct. The write functionality
 * uses this struct to build a new CMAC XML document.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file        XMLParser.hpp
 * @authors     Ross Arcemont
 * @date        November, 2018
 */

#include "xml_parser.hpp"
#include <boost/foreach.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

/**
 * new_message is used to store the incoming CAP message
 * held within the SOAP message body into memory. Once
 * all attributes in new_message are defined, it is used
 * to build a new CMAC message compatible for CMSP use.
 */
typedef CAPMessage new_message;

CAPMessage ReadXML(std::istream & is) {
    using boost::property_tree::ptree;
    ptree pt;
    read_xml(is, pt);

    CAPMessage parsed_xml;
    parsed_xml.identifier = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.identifier");
    parsed_xml.sender = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.sender");
    parsed_xml.sent = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.sent");
    parsed_xml.status = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.status");
    parsed_xml.msg_type = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.msgType");
    parsed_xml.scope = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.scope");
    parsed_xml.category = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.category");
    parsed_xml.event = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.event");
    parsed_xml.response_type = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.responseType");
    parsed_xml.urgency = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.urgency");
    parsed_xml.severity = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.severity");
    parsed_xml.certainty = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.certainty");
    parsed_xml.event_code.valueName =
            pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.eventCode.valueName");
    parsed_xml.event_code.value = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.eventCode.value");
    parsed_xml.expires = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.expires");
    parsed_xml.sender_name = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.senderName");
    parsed_xml.headline = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.headline");
    parsed_xml.description = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.description");
    parsed_xml.instruction = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.instruction");
    parsed_xml.contact = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.contact");
    parsed_xml.area.area_desc = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.area.areaDesc");
    parsed_xml.area.polygon = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.area.polygon");

    // This method is modified from the first response of the following StackOverflow post:
    // https://stackoverflow.com/questions/40393765/accessing-multi-valued-keys-in-property-tree
    auto &info_root = pt.get_child("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info");
    for (auto &area_child : info_root.get_child("area")) {
        if (area_child.first == "geocode") {
            CAPCode new_geo_code;
            new_geo_code.valueName = area_child.second.get<std::string>("valueName");
            new_geo_code.value = area_child.second.get<std::string>("value");
            parsed_xml.area.geo_code.push_back(new_geo_code);
        }
    }
    return parsed_xml;
}

void WriteXML(CAPMessage new_message, std::ostream & os) {
    using boost::property_tree::ptree;
    ptree pt;

    // TODO(Ross): Replace all hard-coded values with system-generated values.
    pt.add("CMAC_Alert_Attributes.CMAC_protocol_version", 1.0);
    pt.add("CMAC_Alert_Attributes.CMAC_sending_gateway_id", "localhost");
    pt.add("CMAC_Alert_Attributes.CMAC_message_number", "mvjfo92513");
    pt.add("CMAC_Alert_Attributes.CMAC_special_handling", "Public Safety message");
    pt.add("CMAC_Alert_Attributes.CMAC_sender", new_message.sender);
    pt.add("CMAC_Alert_Attributes.CMAC_sent_date_time", new_message.sent);
    pt.add("CMAC_Alert_Attributes.CMAC_status", new_message.status);
    pt.add("CMAC_Alert_Attributes.CMAC_message_type", new_message.msg_type);
    pt.add("CMAC_Alert_Attributes.CMAC_response_code", new_message.response_type);
    pt.add("CMAC_Alert_Attributes.CMAC_cap_alert_uri", "localhost/alerturi");
    pt.add("CMAC_Alert_Attributes.CMAC_cap_identifier", new_message.identifier);
    pt.add("CMAC_Alert_Attributes.CMAC_cap_sent_date_time", new_message.sent);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_category", new_message.category);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_event_code", "TestCode");
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_response_type", new_message.response_type);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_severity", new_message.severity);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_urgency", new_message.urgency);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_certainty", new_message.certainty);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_expires_date_time", new_message.expires);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_sender_name", new_message.sender_name);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_text_language", "English");
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_text_alert_message_length", new_message.description.length());
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_text_alert_message", new_message.description);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_Alert_Area.CMAC_area_description", "United States");
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_Alert_Area.CMAC_cmas_geocode",
            new_message.event_code.value);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_Alert_Area.CMAC_cap_geocode.valueName",
            new_message.event_code.valueName);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_Alert_Area.CMAC_cap_geocode.value",
            new_message.event_code.value);
    pt.add("CMAC_Alert_Attributes.CMAC_Digital_Signature.Signature.SignedInfo.CanonicalizationMethod",
            "Algorithm=\"http://www.w3.org/2001/10/xml-exc-c14n#\"");
    pt.add("CMAC_Alert_Attributes.CMAC_Digital_Signature.Signature.SignedInfo.SignatureMethod",
            "Algorithm=\"http://www.w3.org/2001/04/xmldsig-more#rsa-sha256\"");
    pt.add("CMAC_Alert_Attributes.CMAC_Digital_Signature.Signature.SignedInfo.Reference.Transform.Transform",
            "Algorithm=\"http://www.w3.org/2000/09/xmldsig#enveloped-signature\"");
    pt.add("CMAC_Alert_Attributes.CMAC_Digital_Signature.Signature.SignedInfo.Reference.DigestMethod",
            "Algorithm=\"http://www.w3.org/2001/04/xmlenc#sha256\"");
    pt.add("CMAC_Alert_Attributes.CMAC_Digital_Signature.Signature.SignedInfo.Reference.DigestValue", "TestValue");
    pt.add("CMAC_Alert_Attributes.CMAC_Digital_Signature.Signature.SignatureValue", "TestSignatureValue");
    pt.add("CMAC_Alert_Attributes.CMAC_Digital_Signature.Signature.KeyInfo.X509Data.X509SubjectName",
            "TestX509SubjectName");
    pt.add("CMAC_Alert_Attributes.CMAC_Digital_Signature.Signature.KeyInfo.X509Data.X509Certificate",
            "TestX509Certificate");

    write_xml(os, pt);
}

// int main() {
//    std::ifstream input("soap_message_test.xml");
//    CAPMessage new_message = ReadXML(input);
//    std::ofstream output("test_cmac_message.xml");
//    WriteXML(new_message, output);
//    return 0;
// }
