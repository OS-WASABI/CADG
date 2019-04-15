// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * Implementation of Logger.
 *
 * @file        logger.cpp
 * @authors     Kristofer Hoadley
 * @date        November, 2018
 */
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "logger.hpp"

namespace cadg_soap {
Logger& Logger::Instance() {
    static Logger instance;
    return instance;
}
std::string Logger::StringifyCollection(std::string name, std::map<std::string, std::string> map) {
    std::string json_string;
    json_string.append("\"" + name +"\": [");
    for (auto const& item : map)
        json_string.append("\"" + item.first + "\": \"" + item.second + "\", ");
    json_string = json_string.substr(0, json_string.size()-2);
    json_string.append("] ");
    return json_string;
}
void Logger::Log(int log_level, std::string message) {
    if (log_level__ <= log_level)
        p_logger__->log(ConvertLogLevel(log_level), message);
}
void Logger::Log(int log_level, std::string message, std::string calling_class,
            std::string calling_method) {
    if (log_level__ <= log_level) {
        std::string message_constructor("");
        message_constructor.append("Class: " + calling_class);
        message_constructor.append(" Method: " + calling_method);
        message_constructor.append(" Message: " + message);
        Log(log_level, message_constructor);
    }
}
void Logger::Log(int log_level, std::string message, std::string calling_class,
            std::string calling_method, std::vector<std::string> args) {
    if (log_level__ <= log_level) {
        std::string message_constructor("");
        message_constructor.append("Class: " + calling_class);
        message_constructor.append(" Method: " + calling_method);
        message_constructor.append(" Message: " + message);
        message_constructor.append(" Args: ");
        for (const auto& arg : args)
            message_constructor.append(arg + ", ");
        message_constructor = message_constructor.substr(0, message_constructor.size()-2);
        Log(log_level, message_constructor);
    }
}

void Logger::LogLevel(int log_level) {
    /* to set the internal log level */
    log_level__ = log_level;

    /* alternatively, to only adjust the logging at the spdlog console level */
    // p_logger__->sinks()[0]->set_level(ConvertLogLevel(log_level));

    /* alternatively, to set all spdlog logging sinks to the same level below */
    // for(auto& sink : )
    //     sink->set_level(ConvertLogLevel(log_level));
}
spdlog::level::level_enum Logger::ConvertLogLevel(int log_level) {
    switch (log_level) {
        case 0: return spdlog::level::trace;
        case 1: return spdlog::level::debug;
        case 2: return spdlog::level::info;
        case 3: return spdlog::level::warn;
        case 4: return spdlog::level::err;
        case 5: return spdlog::level::critical;
        default: return spdlog::level::off;
    }
}
/**
 * Private constructor for logger. Configuration and setup of the spdlog
 * loggers is handled here. Logging output goes to files and console.
 */
Logger::Logger() {
    auto log_console_sink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
    log_console_sink->set_level(spdlog::level::trace);  // trace level will log everything

    auto log_file_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/logs.txt", 2, 30);
    log_file_sink->set_level(spdlog::level::trace);  // trace level will log everything

    p_logger__.reset(new spdlog::logger("multi_sink", {log_console_sink, log_file_sink}));
    p_logger__->set_level(spdlog::level::trace);  // trace level will log everything
    p_logger__->flush_on(spdlog::level::trace);  // trace level will flush to file on every log message

}
}  // namespace cadg_soap
