#pragma once

#if defined(_WIN32)
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <ctime>
#include <iomanip>
#include <iostream>

namespace eregion {

enum LogLevel { TRACE, DEBUG, INFO, WARN, ERROR };

void trace(std::string msg);
void debug(std::string msg);
void info(std::string msg);
void warn(std::string msg);
void error(std::string msg);
void log(std::string msg, LogLevel level);
std::string getLevelStr(LogLevel level);

} // namespace eregion