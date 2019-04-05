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
        web::json::value to_json() {
            auto alert_json = web::json::value::object();
            alert_json["alert_id"] = web::json::value::number(alert_id);
            alert_json["identifier"] = web::json::value::string(identifier);
            alert_json["originator_id"] = web::json::value::number(originator_id);
            alert_json["message_type"] = web::json::value::string(message_type);
            alert_json["scope"] = web::json::value::string(scope);
            alert_json["status"] = web::json::value::string(status);
            alert_json["urgency"] = web::json::value::string(urgency);
            alert_json["severity"] = web::json::value::string(severity);
            alert_json["cap_xml"] = web::json::value::string(cap_xml);
            alert_json["sent_time"] = web::json::value::string(time_to_string());
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
        static std::optional<Alert> from_json(web::json::value alert_json) {
            // TODO(ALL): Only require fields that the DB requires (set as NOT NULL).
            if( alert_json.has_field("identifier")      && alert_json["identifier"].is_string() &&
                alert_json.has_field("originator_id")   && alert_json["originator_id"].is_integer() &&
                alert_json.has_field("message_type")    && alert_json["message_type"].is_string() &&
                alert_json.has_field("scope")           && alert_json["scope"].is_string() &&
                alert_json.has_field("status")          && alert_json["status"].is_string() &&
                alert_json.has_field("urgency")         && alert_json["urgency"].is_string() &&
                alert_json.has_field("severity")        && alert_json["severity"].is_string() &&
                alert_json.has_field("sent_time")       && alert_json["sent_time"].is_string() &&
                alert_json.has_field("cap_xml")         && alert_json["cap_xml"].is_string()) {

                Alert alert;
                if(alert_json.has_field("alert_id") && alert_json["alert_id"].is_integer()) {
                    alert.alert_id = alert_json["alert_id"].as_integer();
                }
                alert.identifier = alert_json["identifier"].as_string();
                alert.originator_id = alert_json["originator_id"].as_integer();
                alert.message_type = alert_json["message_type"].as_string();
                alert.scope = alert_json["scope"].as_string();
                alert.status = alert_json["status"].as_string();
                alert.urgency = alert_json["urgency"].as_string();
                alert.severity = alert_json["severity"].as_string();
                alert.sent_time = time_from_string(alert_json["sent_time"].as_string());
                alert.cap_xml = alert_json["cap_xml"].as_string();
                return alert;
            } else {
                return std::nullopt;
            }
        }

        static std::optional<Alert> from_ns4__alert(_ns4__alert soap_alert) {
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
<<<<<<< Updated upstream
}  // namespace cadg_soap
=======
}
>>>>>>> Stashed changes
#endif //CADG_REST_SERVER_ALERT_HPP
