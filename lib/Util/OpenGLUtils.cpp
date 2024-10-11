#include "eregion/Util/OpenGLUtils.h"

using namespace eregion;

namespace eregion {

double getTime() { return glfwGetTime(); }

void errorCallback(int errCode, const char* desc) { error("GL ERROR [" + std::to_string(errCode) + "] - " + desc); }

void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                              const GLchar* message, const void* userParam) {

    bool isError = type == GL_DEBUG_TYPE_ERROR;

    if (isError) {
        error("GL Error: Source = " + getSource(source) + ", Type = " + getType(type) +
              ", Severity = " + getSeverity(severity) + ", message = " + message);
    } else {
        debug("GL Info: Source = " + getSource(source) + ", Type = " + getType(type) +
              ", Severity = " + getSeverity(severity) + ", message = " + message);
    }
}

std::string getType(GLenum type) {
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        return "Error";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        return "Deprecated Behaviour";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        return "Undefined Behaviour";
    case GL_DEBUG_TYPE_PORTABILITY:
        return "Portability";
    case GL_DEBUG_TYPE_PERFORMANCE:
        return "Performance";
    case GL_DEBUG_TYPE_MARKER:
        return "Marker";
    case GL_DEBUG_TYPE_PUSH_GROUP:
        return "Push Group";
    case GL_DEBUG_TYPE_POP_GROUP:
        return "Pop Group";
    case GL_DEBUG_TYPE_OTHER:
        return "Other";
    }
    return "Unknown";
}

std::string getSeverity(GLenum severity) {
    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        return "High";
    case GL_DEBUG_SEVERITY_MEDIUM:
        return "Medium";
    case GL_DEBUG_SEVERITY_LOW:
        return "Low";
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        return "Notification";
    }
    return "Unknown";
}

std::string getSource(GLenum source) {
    switch (source) {
    case GL_DEBUG_SOURCE_API:
        return "API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        return "Window System";
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        return "Shader Compiler";
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        return "Third Party";
    case GL_DEBUG_SOURCE_APPLICATION:
        return "Application";
    case GL_DEBUG_SOURCE_OTHER:
        return "Other";
    }
    return "Unknown";
}
} // namespace eregion