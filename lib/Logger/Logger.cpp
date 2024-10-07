#include "eregion/Logger/Logger.h"

using namespace eregion;

namespace eregion {

std::mutex logMutex;
LogLevel minLevel = INFO;

void trace(std::string msg) { log(msg, TRACE); }

void debug(std::string msg) { log(msg, DEBUG); }

void info(std::string msg) { log(msg, INFO); }

void warn(std::string msg) { log(msg, WARN); }

void error(std::string msg) { log(msg, ERROR); }

void log(std::string msg, LogLevel level) {

    if (level < minLevel) {
        return;
    }

    std::string levelStr = getLevelStr(level);

    std::time_t now = std::time(0);
    std::tm* localTime = std::localtime(&now);

#if defined(_WIN32)
    DWORD processId = GetCurrentProcessId();
#else
    pid_t processId = getpid();
#endif

    std::lock_guard<std::mutex> guard(logMutex);

    std::cout << "[" << levelStr << "][" << std::put_time(localTime, "%Y-%m-%dT%H:%M:%S") << "][" << processId << "] "
              << msg << std::endl;
}

void setLogLevel(LogLevel level) { minLevel = level; }

std::string getLevelStr(LogLevel level) {
    switch (level) {
    case TRACE:
        return "\033[37mTRACE\033[0m";
    case DEBUG:
        return "\033[34mDEBUG\033[0m";
    case INFO:
        return "\033[32mINFO\033[0m";
    case WARN:
        return "\033[33mWARN\033[0m";
    case ERROR:
        return "\033[31mERROR\033[0m";
    default:
        return "UNKNOWN";
    }
}
} // namespace eregion