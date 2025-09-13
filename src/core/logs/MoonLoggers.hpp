#pragma once
#include <string>

enum class LogLevel {
    Debug,
    Info,
    Warning,
    Error
};

class Logger {
public:
    static void Log(LogLevel level, const std::string& category, const std::string& message);
};
