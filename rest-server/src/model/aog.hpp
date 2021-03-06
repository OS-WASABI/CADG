//
// Created by shulce on 1/16/19.
//

#ifndef REST_SERVER_AOG_HPP
#define REST_SERVER_AOG_HPP

#endif //REST_SERVER_AOG_HPP

#include <string>
#include "cpprest/json.h"

namespace cadg_rest {
    /**
     * Data structure to model originator information.
     */
    struct Aog {
        int id;
        std::string name;
        std::string agency;
        /**
         * Converts an Aog struct into a json value object
         * @return web::json::value representation of Aog
         */
        web::json::value to_json() {
            auto aog_json = web::json::value::object();
            aog_json["id"] = id;
            aog_json["name"] = web::json::value::string(name);
            aog_json["agency"] = web::json::value::string(agency);
            return aog_json;
        }
        /**
         * Creates an Aog from an input json value
         * @param input json value representation of Aog
         * @return Aog struct version of input json, or nullopt if bad input
         */
        static std::optional<Aog> from_json(web::json::value input) {
            if (input.has_field("name") && input["name"].is_string() &&
                input.has_field("agency") && input["agency"].is_string()) {
                if (input.has_field("id") && input["id"].is_integer()) {
                    return Aog {input["id"].as_integer(),
                                input["name"].as_string(),
                                input["agency"].as_string()};
                } else {
                    return std::optional(Aog{0,
                               input["name"].as_string(),
                               input["agency"].as_string()});
                }
            } else {
                return std::nullopt;
            }
        }
        //Compares if two Aog constructs are the same
        inline bool operator==(const Aog& other) {
            return id == other.id && name == other.name && agency == other.agency;
        }
    };
}  // namespace cadg_rest
