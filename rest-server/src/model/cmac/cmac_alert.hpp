#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include "cmac_alert_info.hpp"

#ifndef CADG_REST_SERVER_CMAC_ALERT_HPP
#define CADG_REST_SERVER_CMAC_ALERT_HPP

namespace cmac {
    struct CMAC_alert {
        std::optional<std::string> cmac_protocol_version;
        std::optional<std::string> cmac_sending_gateway_id;
        std::optional<std::string> cmac_message_number;
        std::optional<std::string> cmac_referenced_message_number;
        std::optional<std::string> cmac_referenced_message_cap_identifier;
        std::optional<std::string> cmac_special_handling;
        std::optional<std::string> cmac_sender;
        std::optional<std::string> cmac_sent_date_time;
        std::optional<std::string> cmac_status;
        std::optional<std::string> cmac_message_type;
        std::optional<std::vector<std::string>> cmac_response_code;
        std::optional<std::vector<std::string>> cmac_note;
        std::optional<std::string> cmac_cap_alert_uri;
        std::optional<std::string> cmac_cap_identifier;
        std::optional<std::string> cmac_cap_sent_date_time;
        std::optional<cmac::CMAC_alert_info> cmac_alert_info;
        std::optional<std::string> cmac_digital_signature;
    };
}

#endif //CADG_REST_SERVER_CMAC_ALERT_HPP
