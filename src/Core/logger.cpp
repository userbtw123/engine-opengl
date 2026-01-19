#include "Core/logger.hpp"
#include <format>
#include <stdexcept>

std::ofstream Logger::m_file;

void Logger::init(const std::filesystem::path& path) {
    m_file.open(path, std::ios::out | std::ios::trunc);
    if (!m_file.is_open()) {
        throw std::runtime_error("failed to open the log file");
    }
}

void Logger::output(LogLevel level, const std::string& message) {
    std::string out_message =
        std::format("{} {}: {}", getTimeStamp(), levelToString(level), message);
    m_file << out_message << std::endl;
}

std::string Logger::getTimeStamp() {
    using namespace std::chrono;
    auto now      = system_clock::now();
    std::time_t t = system_clock::to_time_t(now);
    std::tm tm;
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
    case LogLevel::Info:
        return "INFO";
    case LogLevel::Warning:
        return "WARN";
    case LogLevel::Critical:
        return "CRITICAL";
    case LogLevel::Error:
        return "ERROR";
    }
    return "UNKNOWN";
}
