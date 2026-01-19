#pragma once

#include <filesystem>
#include <format>
#include <fstream>
#include <string>
#include <string_view>

enum class LogLevel { Info, Warning, Error, Critical };

class Logger {
  public:
    static void init(const std::filesystem::path& path);
    template <typename... Args>
    static void log(LogLevel level, std::string_view fmt, Args&&... args) {
        std::string message = std::vformat(fmt, std::make_format_args(args...));
        output(level, message);
    }

  private:
    static std::ofstream m_file;
    static void output(LogLevel level, const std::string& message);
    static std::string getTimeStamp();
    static std::string levelToString(LogLevel level);
};
