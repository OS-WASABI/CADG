// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <iostream>
#include <string>
#include "data_access_object.hpp"
#include "logger.hpp"
#include "user_controller.hpp"
#include "log_level.hpp"
using cadg_rest::DataAccessObject;
using cadg_rest::Logger;
using cadg_rest::LoggerInterface;
using cadg_rest::UserController;
using cadg_rest::LogLevel;

int main(int argc, const char * argv[]) {
    LoggerInterface& logger(Logger::Instance());
    logger.LogLevel(LogLevel::DEBUG);
    logger.Log(LogLevel::INFO, "Starting cadg rest server");
    // TODO: Create database and update connection string.
    DataAccessObject::Instance().SetConnectionString("Server=myServerAddress;Port=1234;Database=myDataBase;Uid=myUsername;Pwd=myPassword;");
    UserController user_controller(Logger::Instance(), DataAccessObject::Instance());
    std::string server_address;
    if (argc > 2)
        server_address.append(argv[2]);
    else
        server_address.append("http://host_auto_ip4");
    if (argc > 1)
        server_address.append(argv[1]);
    else
        server_address.append(":8080");
    server_address.append("/v1/cadg/api");
    user_controller.endpoint(server_address + "/users");
    try {
        user_controller.Accept().wait();
        logger.Log(LogLevel::INFO, "Listening for requests at: " +  user_controller.endpoint());
        logger.Log(LogLevel::INFO, "Press ENTER to exit.");
        std::string line;
        std::getline(std::cin, line);
        user_controller.Shutdown().wait();
    }
    catch(std::exception&  e) {
        logger.Log(LogLevel::ERR, "There was an error");
       logger.Log(LogLevel::ERR, e.what());
    }
    return 0;
}
