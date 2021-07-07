#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <optional>

#ifndef CADG_REST_SERVER_CMAC_ALERT_AREA_HPP
#define CADG_REST_SERVER_CMAC_ALERT_AREA_HPP

namespace cmac {
    struct CMAC_alert_area {
        std::optional<std::string> cmac_area_description;
        std::optional<std::vector<std::string>> cmac_polygon;
        std::optional<std::vector<std::string>> cmac_circle;
        std::optional<std::vector<std::string>> cmac_cmas_geocode;
        // First string value in the pair contains the CAP geocode valueName, second contains value
        std::optional<std::vector<std::pair<std::string, std::string>>> cmac_cap_geocode;
        std::optional<std::vector<std::string>> cmac_gnis;
    };
}

#endif //CADG_REST_SERVER_CMAC_ALERT_AREA_HPP
