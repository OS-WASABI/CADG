/**
 * Operates the gSOAP SOAP server for the OS-WASABI CADG Project
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley, Shawn Hulce, Michael McCulley
 *
 * @file        rest_server.cpp
 * @authors     Shawn Hulce
 * @date        March 2019
 */
#include <iostream>
#include <string>
#include "log_level.hpp"
#include "logger.hpp"
#include "gSOAPFiles/soapCAPSoapHttpService.h"
#include "gSOAPFiles/soapStub.h"
#include "gSOAPFiles/soapH.h"
#include "gSOAPFiles/stdsoap2.h"
#include "gSOAPFiles/CAPSoapHttp.nsmap"
#include "gSOAPFiles/plugin/threads.h"
#include "services/cap_validation.hpp"
using cadg_soap::LoggerInterface;
using cadg_soap::LogLevel;
using cadg_soap::Logger;

void *process_request(void *arg) {
    CAPSoapHttpService *service = (CAPSoapHttpService*) arg;
    THREAD_DETACH(THREAD_ID);
    if (service) {
        service->serve();
        service->destroy();
        delete service;
    }
    return NULL;
}

int main(int argc, const char * argv[]) {
    int port = 8000;
    if (std::strlen(*argv) == 1 ) {
        port = std::stoi(argv[0]);
    }
    LoggerInterface& logger(Logger::Instance());
    logger.LogLevel(LogLevel::DEBUG);
    struct soap soap;
    CAPSoapHttpService service(SOAP_IO_KEEPALIVE);
    service.soap->accept_timeout = 24*60*60;
    service.soap->send_timeout = service.soap->recv_timeout = 5;
    SOAP_SOCKET sock = service.bind(NULL, port, 100);
    if (soap_valid_socket(sock)) {
        while (soap_valid_socket(service.accept())) {
            THREAD_TYPE tid;
            void *arg = (void*)service.copy();
            if (!arg) { soap_closesock(&soap); }
            else { while (THREAD_CREATE(&tid, (void*(*)(void*)) process_request, arg));}
        }
    }
    service.soap_stream_fault(std::cerr);
    service.destroy();

    return 0;

}

int CAPSoapHttpService::getRequest(ns2__requestParameterList *ns1__getRequestTypeDef,
                                   ns3__responseParameterList &ns1__getResponseTypeDef) {
    return SOAP_OK;
}

int CAPSoapHttpService::postCAP(_ns1__postCAPRequestTypeDef *request,
                                _ns1__postCAPResponseTypeDef &response) {
    auto responseCode = SOAP_OK;
    auto const alert = request->ns4__alert;
    LoggerInterface& logger(Logger::Instance());
    logger.Log(LogLevel::INFO, alert->sender, "CAPSoapHttpService", "postCAP");
    if (!cap_validation::validate_soap_alert(*alert)) {
        responseCode = SOAP_MIME_ERROR;
    }

    return responseCode;
}

int CAPSoapHttpService::getMessage(ns2__requestParameterList *ns1__getMessageTypeDef,
                                   _ns1__messageResponseTypeDef &ns1__messageResponseTypeDef) {
    return SOAP_OK;
}