/// Tests the XML Parser
/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 * @file    xml_parser_test.cpp
 * @authors { Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley, Shawn Hulce, Michael McCulley }
 * @date    January, 2019
 */

#include "xml_parser.hpp"
#include <gtest/gtest.h>
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>

TEST(xml_parse_tests, import) {
    std::ifstream input("../soap/xml-parsing/soap_message_test.xml");
    CAPMessage test_message = ReadXML(input);
    EXPECT_EQ(test_message.identifier, "KSTO1055887203");
    EXPECT_EQ(test_message.sender, "KSTO@NWS.NOAA.GOV");
    EXPECT_EQ(test_message.sent, "2003-06-17T14:57:00-07:00");
    EXPECT_EQ(test_message.status, "Actual");
    EXPECT_EQ(test_message.msg_type, "Alert");
    EXPECT_EQ(test_message.scope, "Public");
    EXPECT_EQ(test_message.category, "Met");
    EXPECT_EQ(test_message.event, "SEVERE THUNDERSTORM");
    EXPECT_EQ(test_message.response_type, "Shelter");
    EXPECT_EQ(test_message.urgency, "Immediate");
    EXPECT_EQ(test_message.severity, "Severe");
    EXPECT_EQ(test_message.certainty, "Observed");
    EXPECT_EQ(test_message.event_code.valueName, "SAME");
    EXPECT_EQ(test_message.event_code.value, "SVR");
    EXPECT_EQ(test_message.expires, "2003-06-17T16:00:00-07:00");
    EXPECT_EQ(test_message.sender_name, "NATIONAL WEATHER SERVICE SACRAMENTO CA");
    EXPECT_EQ(test_message.headline, "SEVERE THUNDERSTORM WARNING");
    EXPECT_EQ(test_message.description,
            "AT 254 PM PDT...NATIONAL WEATHER SERVICE DOPPLER RADAR INDICATED A SEVERE THUNDERSTORM OVER "
            "SOUTH CENTRAL ALPINE COUNTY...OR ABOUT 18 MILES SOUTHEAST OF KIRKWOOD...MOVING SOUTHWEST AT 5 "
            "MPH. HAIL...INTENSE RAIN AND STRONG DAMAGING WINDS ARE LIKELY WITH THIS STORM.");
    EXPECT_EQ(test_message.instruction, "TAKE COVER IN A SUBSTANTIAL SHELTER UNTIL THE STORM PASSES.");
    EXPECT_EQ(test_message.event, "SEVERE THUNDERSTORM");
    EXPECT_EQ(test_message.contact, "BARUFFALDI/JUSKIE");
    EXPECT_EQ(test_message.area.area_desc,
            "EXTREME NORTH CENTRAL TUOLUMNE COUNTY IN CALIFORNIA, EXTREME "
            "NORTHEASTERN CALAVERAS COUNTY IN CALIFORNIA, SOUTHWESTERN ALPINE COUNTY IN CALIFORNIA");
    EXPECT_EQ(test_message.area.polygon, "38.47,-120.14 38.34,-119.95 38.52,-119.74 38.62,-119.89 38.47,-120.14");
    EXPECT_EQ(test_message.area.geo_code[0].valueName, "SAME");
    EXPECT_EQ(test_message.area.geo_code[0].value, "006109");
    EXPECT_EQ(test_message.area.geo_code[1].valueName, "SAME");
    EXPECT_EQ(test_message.area.geo_code[1].value, "006009");
    EXPECT_EQ(test_message.area.geo_code[2].valueName, "SAME");
    EXPECT_EQ(test_message.area.geo_code[2].value, "006003");
}
