// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef LOGGER_INTERFACE_H
#define LOGGER_INTERFACE_H
#include <string>
#include <vector>
#include <cpprest/http_msg.h>
#include <cpprest/http_listener.h>
#include "log_level.hpp"
using namespace web;
using namespace http;

namespace cadg_rest {

class LoggerInterface {
  public:
    /**
     * Generic log method.
     * 
     * @param log_level the log level [ALL, DEBUG, INFO, WARN, ERR, FATAL, OFF].
     * @param message what to log.
     * 
     */
    virtual void Log(int log_level, std::string message) = 0;
    /**
     * Generic log method for logging method calls.
     * 
     * @param log_level The log level [ALL, DEBUG, INFO, WARN, ERR, FATAL, OFF].
     * @param message The message to log.
     * @param calling_class The class that is calling the method.
     * @param calling_method The method that is being called.
     * 
     */
    virtual void Log(int log_level, std::string message, std::string calling_class,
                    std::string calling_method) = 0;
    /**
     * Generic log method for logging method calls.
     * 
     * @param log_level The log level [ALL, DEBUG, INFO, WARN, ERR, FATAL, OFF].
     * @param message The message to log.
     * @param calling_class The class that is calling the method.
     * @param calling_method The method that is being called.
     * @param args The method arguments.
     * 
     */
    virtual void Log(int log_level, std::string message, std::string calling_class,
                    std::string calling_method, std::vector<std::string> args) = 0;
    /**
     * Generic log method for logging network calls.
     * 
     * @param message The http request message to log.
     * 
     */
    virtual void LogNetworkActivity(http_request message, std::string endpoint, int verbosity = 0) = 0;
    /**
     * Set the logging level.
     * 
     * @param log_level the log level [ALL, DEBUG, INFO, WARN, ERR, FATAL, OFF]
     * 
     */
    virtual void LogLevel(int log_level) = 0;
};
}
#endif // LOGGER_INTERFACE_H
