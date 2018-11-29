// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * Implementation of the UserController class.
 *
 * @file        user_controller.cpp
 * @authors     Kristofer Hoadley
 * @date        November, 2018
 */
#include <cpprest/uri_builder.h>
#include <cpprest/base_uri.h>
#include <algorithm>
#include <iostream>
#include <string>
#include "user_controller.hpp"
#include "log_level.hpp"
using cadg_rest::LogLevel;

namespace cadg_rest {
void UserController::InitHandlers() {
    listener__.support(methods::GET, std::bind(&UserController::HandleGet, this, std::placeholders::_1));
    listener__.support(methods::PUT, std::bind(&UserController::HandlePut, this, std::placeholders::_1));
    listener__.support(methods::POST, std::bind(&UserController::HandlePost, this, std::placeholders::_1));
    listener__.support(methods::DEL, std::bind(&UserController::HandleDelete, this, std::placeholders::_1));
}
void UserController::HandleGet(http_request message) {
    logger__.LogNetworkActivity(message, endpoint(), 2);
    try {
        auto response = json::value::object();
        response["users"] = json::value::object();
        auto queries = Queries(message.relative_uri().query());
        auto relative_path = message.relative_uri().to_string();
        if (relative_path.length() > 1 && relative_path.at(1) != '?') {
            GetUserByID(response, relative_path);
        } else if (queries.count("name") > 0) {
            GetUsersByName(response, queries["name"]);
        } else {
            auto users = dao__.GetUsers();
            for (auto& user : users) {
                response["users"][std::to_string(user.id)] = user.to_json();
            }
        }
        message.reply(status_codes::OK, response);
    } catch (std::exception&  e) {
        // return error for testing purposes only
        logger__.Log(LogLevel::WARN, e.what(), "UserController", "HandleGet");
        message.reply(status_codes::InternalError, json::value::string(e.what()));
    }
}
void UserController::HandlePut(http_request message) {
    logger__.LogNetworkActivity(message, endpoint(), 1);
    try {
        // extract submitted user info
        const json::value body_json = message.extract_json().get();
        // get user id from uri
        auto relative_path = message.relative_uri().to_string();
        if (relative_path.length() > 1 && relative_path.at(1) != '?') {
            std::string id_as_string = ParseUserID(relative_path);
            dao__.UpdateUser(std::stoi(id_as_string), body_json.as_object());
        }
        message.reply(status_codes::ResetContent);
    }
    catch (std::exception& e) {
        message.reply(status_codes::BadRequest, e.what());
    }
}
void UserController::HandlePost(http_request message) {
    logger__.LogNetworkActivity(message, endpoint(), 1);
    try {
        // parse body and extract user data
        const json::value body_json = message.extract_json().get();
        // validate user data
        // if valid add using dao
        auto users_json = body_json.at("users").as_object();
        for (auto iter = users_json.cbegin(); iter != users_json.cend(); ++iter) {
            auto &key = iter->first;
            const json::value &value = iter->second;
            if (value.is_object()) {
                auto user_json = value.as_object();
                dao__.AddUser(
                        User {user_json["name"].as_string(),
                        std::stoi(key), user_json["password"].as_string()});
            }
        }
        // respond with successfully created (201)
        message.reply(status_codes::Created);
    } catch (std::exception&  e) {  // for testing purposes
        logger__.Log(LogLevel::WARN, e.what(), "UserController", "HandlePost");
        message.reply(status_codes::BadRequest, e.what());
    }
}
void UserController::HandleDelete(http_request message) {
    logger__.LogNetworkActivity(message, endpoint(), 1);
    try {
        auto replyStatus = status_codes::OK;
        auto path = message.relative_uri().to_string();
        auto userID = ParseUserID(path);
        if (userID.length() > 0) {  // Verify request has user id
            auto user = dao__.GetUserByID(std::stoi(userID));  // Gets user from DAO
            if (user.size() > 0) {  // Verifies user was found
                dao__.RemoveUser(user[0]);
            } else {
                replyStatus = status_codes::NotFound;
            }
        } else {
            replyStatus = status_codes::BadRequest;
        }
        message.reply(replyStatus);
    } catch (std::exception& e) {
        message.reply(status_codes::BadRequest, e.what());
    }
}
void UserController::GetUserByID(json::value& response, const std::string& path) {
    auto id_as_string = ParseUserID(path);
    if (id_as_string.find_first_not_of("0123456789") == std::string::npos) {
        int id = std::stoi(id_as_string);
        auto users = dao__.GetUserByID(id);
        if (users.size() > 0) {
            logger__.Log(LogLevel::DEBUG, "name of found user: " + users[0].name);
            response["users"][std::to_string(users[0].id)] = users[0].to_json();
        }
    }
}
void UserController::GetUsersByName(json::value& response, const std::string& user_name) {
    logger__.Log(LogLevel::DEBUG, "user name query: " + user_name);
    auto users = dao__.GetUsersByName(user_name);
    for (auto& user : users) {
        response["users"][std::to_string(user.id)] = user.to_json();
    }
}
/// Currently assumes the path only contains a slash and numbers.
// TO-DO(Kris): Return valid ID or code for invalid ID (empty string)
std::string UserController::ParseUserID(const std::string& path) {
    logger__.Log(LogLevel::DEBUG, "path to extract id as string: " + path, "UserController", "ParseUserID");
    auto next_forward_slash = path.find("/", 1);
    std::string id_as_string;
    if (next_forward_slash == std::string::npos)  // no more slashes
        id_as_string = path.substr(1);
    else
        id_as_string = path.substr(1, next_forward_slash - 1);
    logger__.Log(LogLevel::DEBUG, "id_as_string: " + id_as_string, "UserController", "ParseUserID");
    return id_as_string;
}
}  // namespace cadg_rest
