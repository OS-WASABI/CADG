//
// Created by shulce on 11/27/18.
//
#include <cpprest/uri_builder.h>
#include <cpprest/base_uri.h>
#include <algorithm>
#include <iostream>
#include <string>
#include "soap_controller.hpp"
#include "log_level.hpp"
#include "../../gSoapFiles/CAP/soapH.h"
#include "../../gSoapFiles/CAP/ns2.nsmap"
using cadg_rest::LogLevel;

namespace cadg_soap {
    void SoapController::InitHandlers() {
        listener__.support(methods::GET, std::bind(&SoapController::HandleGet, this, std::placeholders::_1));
        listener__.support(methods::PUT, std::bind(&SoapController::HandlePut, this, std::placeholders::_1));
        listener__.support(methods::POST, std::bind(&SoapController::HandlePost, this, std::placeholders::_1));
        listener__.support(methods::DEL, std::bind(&SoapController::HandleDelete, this, std::placeholders::_1));
    }

    void SoapController::HandlePost(http_request message) {
        logger__.LogNetworkActivity(message, endpoint(), 1);
        try {
            _ns2__alert alertMessage;
            // Should generate soap context that can read input and create alert. Not sure how
            struct soap ctx = *soap_new2(SOAP_XML_STRICT, SOAP_XML_INDENT);
            auto body = message.extract_string().get();
            logger__.Log(LogLevel::DEBUG, "SOAP Received: " + body, "SoapController", "HandlePost");
            std::stringstream str_stream;
            str_stream.str(body);  // passes message body to into the string stream
            ctx.is = &str_stream;  // sets the instream of the soap ctx  object to the string input stream
            // should read the soap context and output the details to the alertMessage object
            soap_read__ns2__alert(&ctx, &alertMessage);
            logger__.Log(LogLevel::DEBUG, "Alert: " + std::to_string(alertMessage.status), "SoapController", "HandlePost");
            message.reply(status_codes::OK, "Got it");
        } catch (std::exception& e) {
            message.reply(SOAP_FAULT);
        }
    }

    void SoapController::HandleGet(http_request message) {
        message.reply(status_codes::NotImplemented);
    }

    void SoapController::HandlePut(http_request message) {
        message.reply(status_codes::NotImplemented);
    }

    void SoapController::HandleDelete(http_request message) {
        message.reply(status_codes::NotImplemented);
    }

} //end cadg_soap
