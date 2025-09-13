#include "MoonLoggers.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

static std::string GetTimestamp() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto itt = system_clock::to_time_t(now);
    std::tm bt{};
#if defined(_WIN32)
    localtime_s(&bt, &itt);
#else
    localtime_r(&itt, &bt);
#endif
    std::ostringstream oss;
    oss << std::put_time(&bt, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

static std::string LevelToString(LogLevel lvl) {
    switch (lvl) {
        case LogLevel::Debug:   return "DEBUG";
        case LogLevel::Info:    return "INFO";
        case LogLevel::Warning: return "WARNING";
        case LogLevel::Error:   return "ERROR";
    }
    return "UNKNOWN";
}

void Logger::Log(LogLevel level, const std::string& category, const std::string& message) {
    std::cout 
        << "[" << GetTimestamp() << "] "
        << "[" << LevelToString(level) << "] "
        << "(" << category << ") "
        << message 
        << std::endl;
}