/// A REST endpoint controller implementation class for disseminators.
/**
 * DisseminatorController implements the interface defined by Controller.
 * This provides an example of how to use and inject a Data Access Object
 * as well as passing a logger to the base Controller.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file        disseminator_controller.hpp
 * @authors     Kristofer Hoadley
 * @date        January, 2019
 */
#include <optional>
#include <cpprest/uri_builder.h>
#include <cpprest/base_uri.h>
#include <string>
#include <vector>
#include "disseminator_controller.hpp"
#include "log_level.hpp"
using cadg_rest::DisseminatorDaoInterface;

namespace cadg_rest {
void DisseminatorController::InitHandlers() {
    listener__.support(methods::GET, std::bind(&DisseminatorController::HandleGet, this, std::placeholders::_1));
    listener__.support(methods::PUT, std::bind(&DisseminatorController::HandlePut, this, std::placeholders::_1));
    listener__.support(methods::POST, std::bind(&DisseminatorController::HandlePost, this, std::placeholders::_1));
    listener__.support(methods::DEL, std::bind(&DisseminatorController::HandleDelete, this, std::placeholders::_1));
}
void DisseminatorController::HandleGet(http_request message) {
    logger__.LogNetworkActivity(message, endpoint(), 2);
    try {
        auto response = json::value::object();
        auto queries = Queries(message.relative_uri().query());
        auto relative_path = message.relative_uri().to_string();
        std::optional<std::vector<Disseminator>> disseminators_optional;
        logger__.Log(LogLevel::INFO, relative_path);

        if (relative_path.length() > 1) {  // There is a relative path
            if (relative_path.at(1) != '?') {  // It is not a query
                std::vector<std::string> path_segments = PathSegments(relative_path);
                if (path_segments[0].find_first_not_of("0123456789") == std::string::npos) {  // It is a disseminator ID
                    int id = std::stoi(path_segments[0]);
                    disseminators_optional = dao__.GetDisseminatorByID(id);
                } else {  // first path section must be a id to be valid
                    message.reply(status_codes::BadRequest, json::value::string("Bad Request"));
                }
            } else {  // Query string present
                if (queries.count("name") > 0) {
                    disseminators_optional = dao__.GetDisseminatorsByName(queries["name"]);
                }
            }
        } else {
            disseminators_optional = dao__.GetDisseminators();
        }
        if (disseminators_optional.has_value()) {
            response["disseminators"] = json::value::object();
            auto disseminators = disseminators_optional.value();
            for (auto disseminator : disseminators) {
                response["disseminators"][std::to_string(disseminator.id)] = disseminator.to_json();
            }
            message.reply(status_codes::OK, response);
        } else {
            message.reply(status_codes::InternalError, json::value::string("Internal Error"));
        }
    } catch (std::exception&  e) {
        logger__.Log(LogLevel::WARN, e.what(), "DisseminatorController", "HandleGet");
        // TODO(Kris): Remove error return e.what, returned for testing purposes only
        message.reply(status_codes::InternalError, json::value::string(e.what()));
    }
}
void DisseminatorController::HandlePut(http_request message) {
    logger__.LogNetworkActivity(message, endpoint(), 1);
    auto relative_path = message.relative_uri().to_string();
    std::vector<std::string> path_segments = PathSegments(relative_path);
    const json::value disseminator_json = message.extract_json().get();
    if (path_segments.size() > 0 &&
            path_segments[0].find_first_not_of("0123456789") == std::string::npos) {
        if (auto disseminator_optional = Disseminator::from_json(disseminator_json)) {
            int id = std::stoi(path_segments[0]);
            Disseminator disseminator = disseminator_optional.value();
            disseminator.id = id;
            if (auto success_optional = dao__.UpdateDisseminator(disseminator)) {
                auto success = success_optional.value();
                if (success) {
                    message.reply(status_codes::NoContent);
                } else {
                    logger__.Log(LogLevel::ERR, "DisseminatorController",
                            "HandlePut", "Put disseminator returned false.");
                    message.reply(status_codes::InternalError, json::value::string("Internal Error"));
                }
            } else {
                message.reply(status_codes::InternalError, json::value::string("Internal Error"));
            }
        } else {
            message.reply(status_codes::BadRequest, json::value::string("Bad Request"));
        }
    } else {
        message.reply(status_codes::BadRequest, json::value::string("Bad Request"));
    }
}
void DisseminatorController::HandlePost(http_request message) {
    logger__.LogNetworkActivity(message, endpoint(), 1);
    try {
        const json::value disseminator_json = message.extract_json().get();
        if (auto disseminator_optional = Disseminator::from_json(disseminator_json)) {
            Disseminator disseminator = disseminator_optional.value();
            if (auto success_optional = dao__.AddDisseminator(disseminator)) {
                message.reply(status_codes::Created);
            } else {
                message.reply(status_codes::InternalError, json::value::string("Unable to post data"));
            }
        } else {
            message.reply(status_codes::BadRequest, json::value::string("Bad Request"));
        }
    } catch (std::exception&  e) {  // for testing purposes
        logger__.Log(LogLevel::WARN, e.what(), "DisseminatorController", "HandlePost");
        message.reply(status_codes::InternalError, json::value::string("Internal Error"));
    }
}
void DisseminatorController::HandleDelete(http_request message) {
    logger__.LogNetworkActivity(message, endpoint(), 1);
    auto relative_path = message.relative_uri().to_string();
    std::vector<std::string> path_segments = PathSegments(relative_path);
    if (path_segments.size() > 0 &&
            path_segments[0].find_first_not_of("0123456789") == std::string::npos) {
        int id = std::stoi(path_segments[0]);
        if (auto success_optional = dao__.RemoveDisseminator(id)) {
            auto success = success_optional.value();
            if (success) {
                message.reply(status_codes::NoContent);
            } else {
                logger__.Log(LogLevel::ERR, "DisseminatorController",
                        "HandleDelete", "Delete disseminator returned false.");
                message.reply(status_codes::InternalError, json::value::string("Internal Error"));
            }
        } else {
            message.reply(status_codes::InternalError, json::value::string("Internal Error"));
        }
    } else {  // first path section must be a id to be valid
        message.reply(status_codes::BadRequest, json::value::string("Bad Request"));
    }
}
}  // namespace cadg_rest
