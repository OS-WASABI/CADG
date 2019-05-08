/// An interface logging.
/**
 * This defines the interface for a logger. A logger handles general application
 * logging as well as network logging.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley, Shawn Hulce, Michael McCulley
 *
 * @file        logger_interface.hpp
 * @authors     Kristofer Hoadley
 * @date        November, 2018
 */
#ifndef LOGGER_INTERFACE_H
#define LOGGER_INTERFACE_H
#include <string>
#include <vector>

namespace cadg_soap {
/**
 * LoggerInterface defines several ways to log information, as well as netowrk activity.
 * This interface must be defines in an inheriting class.
 */
class LoggerInterface {
  public:
    ///  Generic log method.
    /**
     * @param log_level the log level [ALL, DEBUG, INFO, WARN, ERR, FATAL, OFF].
     * @param message what to log.
     */
    virtual void Log(int log_level, std::string message) = 0;
    /// Generic log method for logging method calls.
    /**
     * For use within a calling method of a calling class.
     * @param log_level The log level [ALL, DEBUG, INFO, WARN, ERR, FATAL, OFF].
     * @param message The message to log.
     * @param calling_class The class that is calling the method.
     * @param calling_method The method that is being called.
     */
    virtual void Log(int log_level, std::string message, std::string calling_class,
                    std::string calling_method) = 0;
    /// Generic log method for logging method calls.
    /**
     * For use within a calling method (that contains arguments) within a calling class.
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
    /// Generic log method for logging method calls.
    /**
     * Set the logging level.
     * @param log_level the log level [ALL, DEBUG, INFO, WARN, ERR, FATAL, OFF]
     */
    virtual void LogLevel(int log_level) = 0;
};
}  // end cadg_soap
#endif // LOGGER_INTERFACE_H
