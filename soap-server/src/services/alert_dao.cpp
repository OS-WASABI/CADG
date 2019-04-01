/// Implements the AlertDao.
/**
 * Implementation of AlertDao.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley
 *                  Shawn Hulce, Michael McCulley
 *
 * @file    alert_dao.cpp
 * @authors Vaniya Agrawal
 * @date    January, 2019
 */

#include <string>
#include <vector>
#include "alert_dao.hpp"
#include "nanodbc.hpp"

namespace cadg_soap {
    AlertDao& AlertDao::Instance() {
        static AlertDao instance;
        return instance;
    }
    AlertDao::AlertDao() : logger(Logger::Instance()) {
        std::string db_cadg_name__ = getEnvVar("DB_CADG_NAME");
        logger.Log(LogLevel::INFO, "The env db_cadg_name__ is: " + db_cadg_name__);
        db_alert_table__ = getEnvVar("DB_ALERT_TABLE");
        logger.Log(LogLevel::INFO, "The env db_alert_table__ is: " + db_alert_table__);
        std::string db_password = getEnvVar("DB_PASSWORD");
        std::string db_port = getEnvVar("DB_PORT");
        if (db_port.empty()) {
            db_port = "3306";  // default port
        }
        std::string db_server = getEnvVar("DB_SERVER");
        if (db_server.empty()) {
            db_server = "127.0.0.1";  // localhost
        }
        std::string db_uid = getEnvVar("DB_UID");
        conn_str__ = "Driver={MySQL8Driver};Server="+ db_server +";Port="+ db_port +";Database="
                     + db_cadg_name__ +";Uid="+ db_uid +";Pwd="+ db_password +";";
        logger.Log(LogLevel::INFO, "The connection string is: " + conn_str__);
    }
    std::optional<std::vector<Alert>> AlertDao::GetAlerts() {
        try {
            nanodbc::connection connection(conn_str__);
            nanodbc::result results = execute(connection, NANODBC_TEXT(
                    std::string("select alert_id, identifier, originator_id, message_type, scope, status, ") +
                    std::string("urgency, severity, sent_time, cap_xml from ") +
                    db_alert_table__ + ";"));
            std::vector<Alert> db_alerts;
            while (results.next()) {
                db_alerts.push_back(Alert{
                    results.get<int>(0, 0),
                    results.get<std::string>(1, ""),
                    results.get<int>(2, 0),
                    results.get<std::string>(3, ""),
                    results.get<std::string>(4, ""),
                    results.get<std::string>(5, ""),
                    results.get<std::string>(6, ""),
                    results.get<std::string>(7, ""),
                    Alert::time_from_string(results.get<std::string>(8, "")),
                    results.get<std::string>(9, "")});
            }
            return db_alerts;
        } catch (std::exception& e) {
            logger.Log(LogLevel::ERR, e.what(), "AlertDao", "GetAlerts");
            return std::nullopt;
        }
    }
    std::optional<std::vector<Alert>> AlertDao::GetAlertsByOriginator(int id) {
        // TODO(All): Implement
        return std::nullopt;
    }
    std::optional<std::vector<Alert>> AlertDao::GetAlertsByStatus(const std::string& status) {
        // TODO(All): Implement
        return std::nullopt;
    }
    std::optional<bool> AlertDao::AddAlert(Alert alert) {
        logger.Log(LogLevel::INFO, "AlertDao", "AlertDao",
                   std::string("Alert alert_id: ") + std::to_string(alert.alert_id) +
                   ", identifier: " + alert.identifier +
                   ", originator_id: " + std::to_string(alert.originator_id) +
                   ", message_type: " + alert.message_type +
                   ", scope: " + alert.scope +
                   ", status: " + alert.status +
                   ", urgency: " + alert.urgency +
                   ", severity: " + alert.severity +
                   ", sent_time: " + alert.time_to_string());
        try {
            nanodbc::connection connection(conn_str__);
            nanodbc::statement statement(connection);
            prepare(statement, NANODBC_TEXT("insert into " + db_alert_table__ +
                                            " (identifier, originator_id, message_type, scope, status," +
                                            " urgency, severity, sent_time, cap_xml)" +
                                            " values(?,?,?,?,?,?,?,?,?);"));
            nanodbc::string const identifier = NANODBC_TEXT(alert.identifier);
            statement.bind(0, identifier.c_str());
            int const originator_id = alert.originator_id;
            statement.bind(1, &originator_id);
            nanodbc::string const message_type = NANODBC_TEXT(alert.message_type);
            statement.bind(2, message_type.c_str());
            nanodbc::string const scope = NANODBC_TEXT(alert.scope);
            statement.bind(3, scope.c_str());
            nanodbc::string const status = NANODBC_TEXT(alert.status);
            statement.bind(4, status.c_str());
            nanodbc::string const urgency = NANODBC_TEXT(alert.urgency);
            statement.bind(5, urgency.c_str());
            nanodbc::string const severity = NANODBC_TEXT(alert.severity);
            statement.bind(6, severity.c_str());
            nanodbc::string const sent_time = NANODBC_TEXT(alert.time_to_string());
            statement.bind(7, sent_time.c_str());
            nanodbc::string const cap_xml = NANODBC_TEXT(alert.cap_xml);
            statement.bind(8, cap_xml.c_str());
            // TODO(Vaniya): Verify the DB inserted successfully.
            execute(statement);

            nanodbc::result results;
            results = execute(connection, NANODBC_TEXT("SELECT LAST_INSERT_ID();"));
            results.next();
            int newId = results.get<int>(0, 0);
            logger.Log(LogLevel::DEBUG, "Has id: " + std::to_string(newId));
            if (results.next() && newId > 0) {
                alert.alert_id = newId;
            }
        } catch (std::exception &e) {
            logger.Log(LogLevel::ERR, e.what(), "AlertDao", "AddAlert");
            return std::nullopt;
        }
        return true;
    }
}   // namespace cadg_soap
