#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include "cmac_alert_info.hpp"
#include "../../../../soap-server/src/gSOAPFiles/soapStub.h"

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
        // TODO(Ross): Determine how to obtain from the gateway.
        std::optional<std::string> cmac_cap_alert_uri;
        std::optional<std::string> cmac_cap_identifier;
        std::optional<std::string> cmac_cap_sent_date_time;
        std::optional<cmac::CMAC_alert_info> cmac_alert_info;
        std::optional<std::string> cmac_digital_signature;
    };

    // NOTE: This method currently DOES NOT WORK. It is here to serve as a starting point
    // for future developers to refine, build upon, and complete. Its intent is to take an external
    // object containing the SOAP CAP input of an incoming message and use it to create a CMAC
    // data object based on the logic outlined in the ATIS-0700037 PDF. This data object will then
    // be passed to the cmac_converter.cpp convert method found in the soap/cmac-conversion directory.
    // Finally, this method should make calls to similar methods found in the cmac_alert_info,
    // cmac_alert_area, cmac_alert_text hpp files as necessary in order to complete the cmac_alert object.
    // Those methods currently do not exist.
    void fillAlertObject(_ns4__alert soap_input, cmac::CMAC_alert new_alert) {
        // TODO(Ross): Determine how to get the protocol version based on either CAP message or other source.
        new_alert.cmac_protocol_version = "Temp value";
        // TODO(Ross): Determine how to get gateway IP or URI.
        new_alert.cmac_sending_gateway_id = "Temp value";
        // TODO(Ross): Determine how to identify CMSP-initiated value, when applicable.
        new_alert.cmac_message_number = soap_input.identifier; // Likely temporary value
        new_alert.cmac_referenced_message_number = soap_input.identifier; // Likely temporary value
        new_alert.cmac_referenced_message_cap_identifier = soap_input.identifier; // Maybe temporary value?
        // TODO(Ross): Determine value
        new_alert.cmac_special_handling = "Temp value";
    }
}

#endif //CADG_REST_SERVER_CMAC_ALERT_HPP