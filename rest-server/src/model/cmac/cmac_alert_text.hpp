#include <iostream>
#include <string>
#include <vector>
#include <optional>

#ifndef CADG_REST_SERVER_CMAC_ALERT_TEXT_HPP
#define CADG_REST_SERVER_CMAC_ALERT_TEXT_HPP

namespace cmac {
    struct CMAC_alert_text {
        std::optional<std::string> cmac_text_language;
        std::optional<std::string> cmac_short_text_alert_message_length;
        std::optional<std::string> cmac_short_text_alert_message;
        std::optional<std::string> cmac_long_text_alert_message_length;
        std::optional<std::string> cmac_long_text_alert_message;
    };
}

#endif //CADG_REST_SERVER_CMAC_ALERT_TEXT_HPP
