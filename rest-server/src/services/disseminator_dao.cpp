// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * Implementation of DisseminatorDao.
 *
 * @file        disseminator_dao.cpp
 * @authors     Michael McCulley, Kristofer Hoadley
 * @date        February, 2019
 */
#include <string>
#include <vector>
#include "disseminator_dao.hpp"
#include "nanodbc.hpp"

// TODO(Kris): Kris database queries async.

namespace cadg_rest {
DisseminatorDao& DisseminatorDao::Instance() {
    static DisseminatorDao instance;
    return instance;
}
DisseminatorDao::DisseminatorDao() : logger__(Logger::Instance()) {
    db_disseminators_table__ = getEnvVar("DB_DISSEMINATOR_TABLE");
    std::string db_cadg_name__ = getEnvVar("DB_CADG_NAME");
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
    std::string db_driver = getEnvVar("DB_ODBC_DRIVER");
    if (db_driver.empty()) {
        db_driver = "MySQL8Driver";
    }
    conn_str__ = "Driver={"+ db_driver +"};Server="+ db_server +";Port="+ db_port
            +";Database="+ db_cadg_name__ +";Uid="+ db_uid +";Pwd="+ db_password +";";
    logger__.Log(LogLevel::INFO, "DisseminatorDao connection string is: " + conn_str__);
}
bool DisseminatorDao::Requery() {
    try {
        nanodbc::connection connection(conn_str__);
        nanodbc::result results;
        results = execute(connection, NANODBC_TEXT(
                std::string("SELECT disseminator_id, disseminator_name, ") +
                std::string("disseminator_type, message_format, ip, port, backup_port, status ") +
                std::string("FROM ") + db_disseminators_table__ + ";"));
        std::vector<Disseminator> temp_disseminators;
        while (results.next()) {
            Disseminator temp;
            temp.id = results.get<int>(0, 0);
            temp.name = results.get<std::string>(1, "");
            temp.type = results.get<std::string>(2, "");
            temp.format = results.get<std::string>(3, "");
            temp.ip = results.get<std::string>(4, "");
            temp.port = results.get<int>(5, 0);
            temp.backup_port = results.get<int>(6, 0);
            temp.status = results.get<std::string>(7, "");
            // TODO(Kris): Verify all fields were populated and valid?
            temp_disseminators.push_back(temp);
        }
        disseminators__ = temp_disseminators;
        return true;
    } catch (std::exception&  e) {
        logger__.Log(LogLevel::ERR, e.what(), "DisseminatorDao", "Requery");
        return false;
    }
}
std::optional<std::vector<Disseminator>> DisseminatorDao::GetDisseminators() {
    if (DisseminatorDao::Requery()) {
        return disseminators__;
    } else {
        return std::nullopt;
    }
}
std::optional<std::vector<Disseminator>> DisseminatorDao::GetDisseminatorsByName(const std::string& name) {
    // TODO(Any): Does not handle a space ' ' in the url correctly. Will need to convert '%20' to space ' '.
    if (DisseminatorDao::Requery()) {
        std::vector<Disseminator> matching_disseminators;
        for (auto& disseminator : disseminators__) {
            if (std::search(disseminator.name.begin(), disseminator.name.end(),
                        name.begin(), name.end(),
                        [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2);
                        }) != disseminator.name.end()) {
                matching_disseminators.push_back(disseminator);
            }
        }
        return matching_disseminators;
    } else {
        return std::nullopt;
    }
}
std::optional<std::vector<Disseminator>> DisseminatorDao::GetDisseminatorByID(int id) {
    if (DisseminatorDao::Requery()) {
        std::vector<Disseminator> matching_disseminators;
        for (auto& disseminator : disseminators__) {
            if (disseminator.id == id) {
                matching_disseminators.push_back(disseminator);
                return matching_disseminators;
            }
        }
        return matching_disseminators;
    } else {
        return std::nullopt;
    }
}
std::optional<bool> DisseminatorDao::RemoveDisseminator(int id) {
    try {
        nanodbc::connection connection(conn_str__);
        nanodbc::statement statement(connection);
        prepare(statement, NANODBC_TEXT(
                std::string("DELETE FROM ") +
                db_disseminators_table__ +
                std::string("WHERE disseminator_id =?;")));
        statement.bind(0, &id);
        execute(statement);
        // check db to see if entry still exists?
        return true;
    } catch (std::exception&  e) {
        logger__.Log(LogLevel::ERR, e.what(), "DisseminatorDao", "RemoveDisseminator");
        return std::nullopt;
    }
}
std::optional<bool> DisseminatorDao::AddDisseminator(Disseminator disseminator) {
    try {
        nanodbc::connection connection(conn_str__);
        nanodbc::statement statement(connection);
        prepare(statement, NANODBC_TEXT(
            std::string("insert into ") + db_disseminators_table__ +
            std::string(" (disseminator_name, disseminator_type, message_format, ip, port, backup_port, status)") +
            std::string(" values(?,?,?,?,?,?,?);")));
        nanodbc::string const name = NANODBC_TEXT(disseminator.name);
        statement.bind(0, name.c_str());
        nanodbc::string const type = NANODBC_TEXT(disseminator.type);
        statement.bind(1, type.c_str());
        nanodbc::string const format = NANODBC_TEXT(disseminator.format);
        statement.bind(2, format.c_str());
        nanodbc::string const ip = NANODBC_TEXT(disseminator.ip);
        statement.bind(3, ip.c_str());
        int const port = disseminator.port;
        statement.bind(4, &port);
        int const backup_port = disseminator.backup_port;
        statement.bind(5, &backup_port);
        nanodbc::string const status = NANODBC_TEXT(disseminator.status);
        statement.bind(6, status.c_str());
        execute(statement);
        // Get the ID of the newly created user record.
        nanodbc::result results;
        results = execute(connection, NANODBC_TEXT("select last_insert_id();"));
        int new_id = 0;
        if (results.next()) {
            new_id = results.get<int>(0, 0);
        }
        if (new_id > 0) {
            disseminator.id = new_id;
            disseminators__.push_back(disseminator);
            return true;
        } else {
            return false;
        }
    } catch (std::exception&  e) {
        logger__.Log(LogLevel::ERR, e.what(), "DisseminatorDao", "AddDisseminators");
        return std::nullopt;
    }
}
std::optional<bool> DisseminatorDao::UpdateDisseminator(Disseminator disseminator) {
    try {
        nanodbc::connection connection(conn_str__);
        nanodbc::statement statement(connection);
        prepare(statement, NANODBC_TEXT(
                std::string("UPDATE") + db_disseminators_table__ +
                std::string("SET disseminator_name = ?, disseminator_type = ?, ") +
                std::string("message_format = ?, ip = ?, port = ?, backup_port = ?, status = ? ") +
                std::string("WHERE id = ?;")));
        nanodbc::string const name = NANODBC_TEXT(disseminator.name);
        statement.bind(0, name.c_str());
        nanodbc::string const type = NANODBC_TEXT(disseminator.type);
        statement.bind(1, type.c_str());
        nanodbc::string const format = NANODBC_TEXT(disseminator.format);
        statement.bind(2, format.c_str());
        nanodbc::string const ip = NANODBC_TEXT(disseminator.ip);
        statement.bind(3, ip.c_str());
        statement.bind(4, &disseminator.port);
        statement.bind(5, &disseminator.backup_port);
        nanodbc::string const status = NANODBC_TEXT(disseminator.status);
        statement.bind(6, status.c_str());
        statement.bind(7, &disseminator.id);
        execute(statement);
        for (auto& temp : disseminators__) {
            if (temp.id == disseminator.id) {
                temp.name = disseminator.name;
                temp.type = disseminator.type;
                temp.format = disseminator.format;
                temp.ip = disseminator.ip;
                temp.port = disseminator.port;
                temp.backup_port = disseminator.backup_port;
                temp.status = disseminator.status;
                break;
            }
        }
        return true;
    } catch (std::exception&  e) {
        logger__.Log(LogLevel::ERR, e.what(), "DisseminatorDao", "UpdateDisseminators");
        return std::nullopt;
    }
}
}  // namespace cadg_rest
