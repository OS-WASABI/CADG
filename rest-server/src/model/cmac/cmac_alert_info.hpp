#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include "cmac_alert_area.hpp"
#include "cmac_alert_text.hpp"

#ifndef CADG_REST_SERVER_CMAC_ALERT_INFO_HPP
#define CADG_REST_SERVER_CMAC_ALERT_INFO_HPP

namespace cmac {
    struct CMAC_alert_info {
        std::optional<std::string> cmac_category;
        std::optional<std::string> cmac_response_type;
        std::optional<std::string> cmac_severity;
        std::optional<std::string> cmac_urgency;
        std::optional<std::string> cmac_certainty;
        std::optional<std::string> cmac_expires_date_time;
        std::optional<std::string> cmac_sender_name;
        std::optional<std::vector<cmac::CMAC_alert_area>> cmac_alert_area;
        std::optional<std::vector<cmac::CMAC_alert_text>> cmac_alert_text;
    };
}

#endif //CADG_REST_SERVER_CMAC_ALERT_INFO_HPP
