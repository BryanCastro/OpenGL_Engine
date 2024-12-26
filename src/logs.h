#pragma once
#include <iostream>
#include <string>
#include <format>

class Logs {
public:
    enum class LogType {
        Success,
        Info,
        Warning,
        Error
    };

    static void log(const std::string& message, LogType type);

private:
    static void setColor(LogType type);
    static void resetColor();
};
