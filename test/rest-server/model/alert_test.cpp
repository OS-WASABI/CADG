/// Tests the Alert Struct
/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file    alert_test.cpp
 * @authors Vaniya Agrawal
 * @date    January, 2019
 */

#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include <string>
#include "alert.hpp"

using cadg_rest::Alert;

class AlertTest : public ::testing::Test {
 public:
    Alert alert;
    std::time_t time = std::time(0);
    AlertTest() {
        alert.sent_time = time;
        alert.alert_id = 0;
        alert.identifier = "First Alert Ever";
        alert.originator_id = 001;
        alert.message_type = "test";
        alert.scope = "private";
        alert.status = "active";
        alert.urgency = "immediate";
        alert.severity = "moderate";
        alert.cap_xml = "CAP MESSAGE TEXT";
    }
};

TEST_F(AlertTest, TimeConvertsToAndFromString) {
    alert.sent_time = std::time(0);
    std::string initial_time = alert.time_to_string();
    alert.sent_time = Alert::time_from_string(alert.time_to_string());
    ASSERT_EQ(initial_time, alert.time_to_string());
}

TEST_F(AlertTest, ConvertsToAndFromJSON) {
    web::json::value alert_json = alert.to_json();
    std::optional<Alert> new_alert = Alert::from_json(alert_json);
    // ASSERT_EQ(new_alert->sent_time, time);
    ASSERT_EQ(new_alert->alert_id, 0);
    ASSERT_EQ(new_alert->identifier, "First Alert Ever");
    ASSERT_EQ(new_alert->originator_id, 001);
    ASSERT_EQ(new_alert->message_type, "test");
    ASSERT_EQ(new_alert->scope, "private");
    ASSERT_EQ(new_alert->status, "active");
    ASSERT_EQ(new_alert->urgency, "immediate");
    ASSERT_EQ(new_alert->severity, "moderate");
    ASSERT_EQ(new_alert->cap_xml, "CAP MESSAGE TEXT");
}

TEST_F(AlertTest, ComparesToOtherAlerts) {
    Alert identical_alert;
    identical_alert.sent_time = time;
    identical_alert.alert_id = 0;
    identical_alert.identifier = "First Alert Ever";
    identical_alert.originator_id = 001;
    identical_alert.message_type = "test";
    identical_alert.scope = "private";
    identical_alert.status = "active";
    identical_alert.urgency = "immediate";
    identical_alert.severity = "moderate";
    identical_alert.cap_xml = "CAP MESSAGE TEXT";

    Alert non_identical_alert;
    identical_alert.sent_time = std::time(0);
    identical_alert.alert_id = 0;
    identical_alert.identifier = "First Alert Ever";
    identical_alert.originator_id = 001;
    identical_alert.message_type = "test";
    identical_alert.scope = "private";
    identical_alert.status = "active";
    identical_alert.urgency = "immediate";
    identical_alert.severity = "moderate";
    identical_alert.cap_xml = "CAP MESSAGE TEXT";
    ASSERT_TRUE(alert == alert);
    ASSERT_TRUE(alert == identical_alert);
    ASSERT_FALSE(alert == non_identical_alert);
}
