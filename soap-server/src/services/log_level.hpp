/// A struct for log level.
/**
 * Contains LogLevel which is a struct for setting the level of logging.
 * It is effectively an enum.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley, Shawn Hulce, Michael McCulley
 *
 * @file        log_level.hpp
 * @authors     Kristofer Hoadley
 * @date        November, 2018
 */
#ifndef LOG_LEVEL_H
#define LOG_LEVEL_H

namespace cadg_soap {
/// LegLevel is used for setting the level of logging.
struct LogLevel {
    static const int ALL    = 0;  ///< Everything should be logged, effectively same as trace.
    static const int DEBUG  = 1;  ///< Used for active debugging of application.
    static const int INFO   = 2;  ///< Used for general information, such as current state of the application.
    static const int WARN   = 3;  ///< Used for a potentially harmful situation.
    static const int ERR    = 4;  ///< Used for error events, where the application should continue still running.
    static const int FATAL  = 5;  ///< Used for fatal events, where the application will likely abort.
    static const int OFF    = 6;  ///< Intended to turn off logging.
};
}  // cadg_soap
#endif // LOG_LEVEL_H
