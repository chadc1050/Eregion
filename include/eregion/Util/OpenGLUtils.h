#pragma once

#include "eregion/Logger/Logger.h"

#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>

namespace eregion {
// Time
double getTime();

// Logging Callbacks
void errorCallback(int errCode, const char* desc);
void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                              const GLchar* message, const void* userParam);
std::string getType(GLenum type);
std::string getSeverity(GLenum severity);
std::string getSource(GLenum source);
} // namespace eregion