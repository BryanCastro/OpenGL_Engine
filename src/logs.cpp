#include "logs.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void Logs::log(const std::string& message, LogType type) {
    setColor(type);
    std::cout << message << std::endl;
    resetColor();
}

void Logs::setColor(LogType type) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (type) {
        case LogType::Success:
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            break;
        case LogType::Info:
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            break;
        case LogType::Warning:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            break;
        case LogType::Error:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            break;
    }
#else
    switch (type) {
        case LogType::Success:
            std::cout << "\033[32m"; // Green
            break;
        case LogType::Info:
            std::cout << "\033[36m"; // Cyan
            break;
        case LogType::Warning:
            std::cout << "\033[33m"; // Yellow
            break;
        case LogType::Error:
            std::cout << "\033[31m"; // Red
            break;
    }
#endif
}

void Logs::resetColor() {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    std::cout << "\033[0m"; // Reset to default
#endif
}