/// A REST endpoint controller implementation class for admins.
/**
 * AdminController implements the interface defined by Controller.
 * This provides an example of how to use and inject a Data Access Object
 * as well as passing a logger to the base Controller.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file        admin_controller.hpp
 * @authors     Kristofer Hoadley
 * @date        January, 2019
 */
#include <optional>
#include <cpprest/uri_builder.h>
#include <cpprest/base_uri.h>
#include <string>
#include <vector>
#include "admin_controller.hpp"
#include "log_level.hpp"
using cadg_rest::AdminDaoInterface;

namespace cadg_rest {
void AdminController::InitHandlers() {
    listener__.support(methods::GET, std::bind(&AdminController::HandleGet, this, std::placeholders::_1));
    listener__.support(methods::PUT, std::bind(&AdminController::HandlePut, this, std::placeholders::_1));
    listener__.support(methods::POST, std::bind(&AdminController::HandlePost, this, std::placeholders::_1));
    listener__.support(methods::DEL, std::bind(&AdminController::HandleDelete, this, std::placeholders::_1));
}
void AdminController::HandleGet(http_request message) {
    logger__.LogNetworkActivity(message, endpoint(), 2);
    try {
        auto response = json::value::object();
        auto queries = Queries(message.relative_uri().query());
        auto relative_path = message.relative_uri().to_string();
        logger__.Log(LogLevel::INFO, relative_path);
        if (relative_path.length() > 1) {  // There is a relative path
            if (relative_path.at(1) != '?') {  // It is not a query
                std::vector<std::string> path_segments = PathSegments(relative_path);
                if (path_segments[0].find_first_not_of("0123456789") == std::string::npos) {  // It is a user ID
                    int id = std::stoi(path_segments[0]);
                    if (path_segments.size() > 1) {
                        if (path_segments[1] == "password") {  // Checking user password
                            const json::value body_json = message.extract_json().get();
                            auto username = body_json.at("username").as_string();
                            auto password = body_json.at("password").as_string();
                            if (auto id_optional = dao__.VerifyAdminPassword(username, password)) {
                                if (id_optional.value() != 0) {
                                    logger__.Log(LogLevel::INFO, "Verified User ID: "+
                                            std::to_string(id_optional.value()));
                                    message.reply(status_codes::NoContent);
                                } else {
                                    // password update unsuccessful.
                                    message.reply(status_codes::BadRequest,
                                            json::value::string("Wrong Username or Password"));
                                }
                            }
                        }
                    } else {  // just id, return admin.
                        if (auto admin_response = dao__.GetAdminByID(id)) {
                            auto admin = admin_response.value();
                            logger__.Log(LogLevel::DEBUG, "Username of found admin: " + admin.username);
                            if (admin.id > 0) {
                                response["admin"] = admin.to_json();
                                message.reply(status_codes::OK, response);
                            } else {
                                message.reply(status_codes::NotFound);
                            }
                        }
                    }
                } else {
                    message.reply(status_codes::BadRequest, json::value::string("Bad Request"));
                }
            } else {  // Query string present
                message.reply(status_codes::NotImplemented,
                        json::value::string("Queries on Admins not implemented yet."));
            }
        } else if (auto admin_optional = dao__.GetAdmins()) {
            response["admins"] = json::value::object();
            auto admins = admin_optional.value();
            for (auto& admin : admins) {
                response["admins"][std::to_string(admin.id)] = admin.to_json();
                // TODO(All): Remove next line, for testing only
                response["admins"][std::to_string(admin.id)]["password"] =
                        json::value::string(dao__.GetAdminPassword(admin.id).value());
            }
            message.reply(status_codes::OK, response);
        } else {
            message.reply(status_codes::BadRequest, json::value::string("Bad Request"));
        }
    } catch (std::exception&  e) {
        logger__.Log(LogLevel::WARN, e.what(), "AdminController", "HandleGet");
        // TODO(Kris): Remove error return e.what, returned for testing purposes only
        message.reply(status_codes::InternalError, json::value::string(e.what()));
    }
}
void AdminController::HandlePut(http_request message) {
    logger__.LogNetworkActivity(message, endpoint(), 1);
    try {
        const json::value body_json = message.extract_json().get();
        auto relative_path = message.relative_uri().to_string();
        if (relative_path.length() > 1) {
            // parse user ID, and verify password
            std::vector<std::string> path_segments = PathSegments(relative_path);
            if (path_segments[0].find_first_not_of("0123456789") == std::string::npos) {
                int id = std::stoi(path_segments[0]);
                if (path_segments[1] == "password") {
                    auto new_password = body_json.at("password").as_string();
                    if (auto success_optional = dao__.UpdateAdminPassword(id, new_password)) {
                        if (success_optional.value()) {
                            // successfully update password in DB
                            message.reply(status_codes::NoContent);
                        } else {
                            // password update unsuccessful.
                            message.reply(status_codes::InternalError, json::value::string("Unable to save password"));
                        }
                    }
                }
            }
        } else {
            message.reply(status_codes::BadRequest, json::value::string("Bad Request"));
        }
    } catch (std::exception&  e) {  // for testing purposes
        logger__.Log(LogLevel::WARN, e.what(), "AdminController", "HandlePut");
        message.reply(status_codes::InternalError, json::value::string("Internal Error"));
    }
}
void AdminController::HandlePost(http_request message) {
    logger__.LogNetworkActivity(message, endpoint(), 1);
    try {
        const json::value admin_json = message.extract_json().get();
        if (auto admin_optional = Admin::from_json(admin_json)) {
            Admin admin = admin_optional.value();
            if (auto success_optional = dao__.AddAdmin(admin)) {
                message.reply(status_codes::Created);
            } else {
                message.reply(status_codes::InternalError, json::value::string("Unable to post data"));
            }
        } else {
            message.reply(status_codes::BadRequest, json::value::string("Bad Request"));
        }
    } catch (std::exception&  e) {  // for testing purposes
        logger__.Log(LogLevel::WARN, e.what(), "AdminController", "HandlePost");
        message.reply(status_codes::InternalError, json::value::string("Internal Error"));
    }
}
void AdminController::HandleDelete(http_request message) {
    // TODO(Kris): Implement
}
bool AdminController::GetAdminByID(json::value& response, const std::string& path) {
    // TODO(Kris): Implement
    return false;
}
bool AdminController::GetAdminsByUsername(json::value& response, const std::string& username) {
    // TODO(Kris): Implement
    return false;
}
}  // namespace cadg_rest
