/// Defines a model that represents an alert message.
/**
 * Contains an alert data structure for moving alert data to and
 * from a data store and a REST endpoint.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file    alert.hpp
 * @authors Vaniya Agrawal
 * @date    January, 2019
 */

#ifndef ALERT_H
#define ALERT_H

#include <optional>
#include <ctime>
#include <sstream>
#include <string>
#include <jsoncpp/json/json.h>
#include <iomanip>
#include "soapH.h"

namespace cadg_soap {

    /// An alert struct.
    /**
     * An alert struct that contains the most important
     * information of the alert.
     */
    struct Alert {
        int alert_id;
        std::string identifier;
        int originator_id;
        std::string message_type;   /// Options: actual, exercise, system, test, draft
        std::string scope;          /// Options: public, restricted, private
        std::string status;         /// Options: active, canceled, expired
        std::string urgency;        /// Options: immediate, expected, future, past, unknown
        std::string severity;       /// Options: extreme, severe, moderate, minor, unknown
        std::time_t sent_time;
        std::string cap_xml;

        /// Convert Alert struct to JSON format.
        /**
         * Converts an struct to a json object.
         * @return The JSON representation of an alert.
         */
        Json::Value to_json() {
            auto alert_json = Json::Value();
            alert_json["alert_id"] = Json::valueToString(alert_id);
            alert_json["identifier"] = identifier;
            alert_json["originator_id"] = Json::valueToString(originator_id);
            alert_json["message_type"] = message_type;
            alert_json["scope"] = scope;
            alert_json["status"] = status;
            alert_json["urgency"] = urgency;
            alert_json["severity"] = severity;
            alert_json["cap_xml"] = cap_xml;
            alert_json["sent_time"] = time_to_string();
            return alert_json;
        }

        /// Create an Alert struct from a json value.
        /**
         * Creates an Alert struct from a json value. If the JSON value does not pass
         * validation, a nullopt will be returned.
         *
         * @param alert_json    The json value representing the alert.
         * @return              The alert in Alert format, or a nullopt.
         */
        static std::optional<Alert> from_json(Json::Value alert_json) {
            // TODO(ALL): Only require fields that the DB requires (set as NOT NULL).
            if( alert_json.isMember("identifier")      && alert_json["identifier"].isConvertibleTo(Json::ValueType(Json::ValueType::stringValue)) &&
                alert_json.isMember("originator_id")   && alert_json["originator_id"].isConvertibleTo(Json::ValueType(Json::ValueType::intValue)) &&
                alert_json.isMember("message_type")    && alert_json["message_type"].isConvertibleTo(Json::ValueType(Json::ValueType::stringValue)) &&
                alert_json.isMember("scope")           && alert_json["scope"].isConvertibleTo(Json::ValueType(Json::ValueType::stringValue)) &&
                alert_json.isMember("status")          && alert_json["status"].isConvertibleTo(Json::ValueType(Json::ValueType::stringValue)) &&
                alert_json.isMember("urgency")         && alert_json["urgency"].isConvertibleTo(Json::ValueType(Json::ValueType::stringValue)) &&
                alert_json.isMember("severity")        && alert_json["severity"].isConvertibleTo(Json::ValueType(Json::ValueType::stringValue)) &&
                alert_json.isMember("sent_time")       && alert_json["sent_time"].isConvertibleTo(Json::ValueType(Json::ValueType::stringValue)) &&
                alert_json.isMember("cap_xml")         && alert_json["cap_xml"].isConvertibleTo(Json::ValueType(Json::ValueType::stringValue))) {

                Alert alert;
                if(alert_json.isMember("alert_id") && alert_json["alert_id"].isConvertibleTo(Json::ValueType::intValue)) {
                    alert.alert_id = alert_json["alert_id"].asInt();
                }
                alert.identifier = alert_json["identifier"].asString();
                alert.originator_id = alert_json["originator_id"].asInt();
                alert.message_type = alert_json["message_type"].asString();
                alert.scope = alert_json["scope"].asString();
                alert.status = alert_json["status"].asString();
                alert.urgency = alert_json["urgency"].asString();
                alert.severity = alert_json["severity"].asString();
                alert.sent_time = time_from_string(alert_json["sent_time"].asString());
                alert.cap_xml = alert_json["cap_xml"].asString();
                return alert;
            } else {
                return std::nullopt;
            }
        }

        static std::optional<Alert> from_ns4__alert(_ns4__alert soap_alert) {
            /**
            Alert alertStruct;
            alertStruct.identifier = soap_alert.identifier;
            alertStruct.originator_id = soap_alert.sender; // Not sure which would map there ??
            alertStruct.message_type = soap_alert.msgType.to_string(); // Not sure this will work
            alertStruct.scope = soap_alert.scope.to_string(); // Not sure this will work
            alertStruct.status = soap_alert.status.to_string(); // Not sure this will work either
            alertStruct.urgency = soap_alert.info.data()->urgency;
            alertStruct.severity = soap_alert.info.data()->severity;
            alertStruct.sent_time = soap_alert.sent.to_string();
            alertStruct.cap_xml = ""; // Unsure what to put here. I'm not sure how easily we will have access to the base XML string
             **/
             return std::nullopt;
        }
        /// Converts current sent_time to string.
        /**
         * Converts the current sent_time to localtime and then to a string.
         * @return sent_time in string representation based on local time.
         */
        std::string time_to_string() {
            auto tm = *std::localtime(&sent_time);
            std::ostringstream oss;
            oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S %z");
            std::string sent_time_str = oss.str();
            return sent_time_str;
        }
        /// Converts from localtime string to epoch.
        /**
         * Converts a string representation of a local time into a time_t object
         * in epoch.
         * @param str   The string representing the local time in the format:  %Y-%m-%d %H:%M:%S %z
         * @return      The new time object.
         */
        static std::time_t time_from_string(std::string str) {
            std::tm tm;
            std::istringstream iss(str);
            iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S %z");
            std::time_t time = mktime(&tm);
            return time;
        }
    };
    /// Compares two alerts.
    /**
     * Returns whether or not two alerts match on all fields (excluding the CAP XML).
     * @param a The first alert.
     * @param b The second alert.
     * @return  True if the alerts match on every field (exc. CAP XML).
     */
    inline bool operator == (const Alert &a, const Alert &b) {
        return  a.alert_id == b.alert_id &&
                a.identifier == b.identifier &&
                a.originator_id == b.originator_id &&
                a.message_type == b.message_type &&
                a.scope == b.scope &&
                a.status == b.status &&
                a.urgency == b.urgency &&
                a.severity == b.severity &&
                a.sent_time == b.sent_time;
    }
}  // namespace cadg_soap

#endif //CADG_REST_SERVER_ALERT_HPP
