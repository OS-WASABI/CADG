// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
// Created by Shawn on 11/26/2018.
//

#ifndef SOAP_CONTROLLER_HPP
#define SOAP_CONTROLLER_HPP
#include <controller.hpp>
#include "../../gSoapFiles/CAP/soapH.h"
#include <logger.hpp>
#include <logger_interface.hpp>
using cadg_rest::LoggerInterface;
using cadg_rest::Logger;

namespace cadg_soap {
class SoapController: public cadg_rest::Controller {
        public:
        SoapController() : logger__(Logger::Instance()), Controller() { }
        ~SoapController() {}

        void InitHandlers() override;
        void HandleGet(http_request message) override;
        void HandlePut(http_request message) override;
        void HandlePost(http_request message) override;
        void HandleDelete(http_request message) override;
        private:
        LoggerInterface& logger__;
};

} //end cadg_soap
#endif //CADG_REST_SERVER_SOAP_CONTROLLER_HPP
