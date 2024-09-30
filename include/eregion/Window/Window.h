#ifndef EREGION_WINDOW_H
#define EREGION_WINDOW_H

#include "eregion/Asset/AssetPool.h"
#include "eregion/Core/Result.h"
#include "eregion/Logger/Logger.h"

#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "linmath.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <variant>

namespace eregion {

typedef struct Vertex {
    vec2 pos;
    vec3 col;
} Vertex;

static const Vertex vertices[3] = {
    {{-0.6f, -0.4f}, {1.f, 0.f, 0.f}}, {{0.6f, -0.4f}, {0.f, 1.f, 0.f}}, {{0.f, 0.6f}, {0.f, 0.f, 1.f}}};

struct WindowConfig {
    int width;
    int height;
    std::string title;
};

class Window {
  public:
    static Window* create(WindowConfig config);
    Result<void> run();
    ~Window();

  private:
    GLFWwindow* glWindow;
    WindowConfig config;

    Window();
    Result<GLuint> createProgram(Shader vertex, Shader fragment);
    Result<GLuint> createShader(Shader shader);
    Result<GLuint> getShaderRef(ShaderType type);
    static void keyCallback(GLFWwindow* glWindow, int key, int scancode, int action, int mods);
    static void errorCallback(int error, const char* description);
    void setGlWindow(GLFWwindow* window);
    GLFWwindow* getGlWindow();
};
} // namespace eregion

#endif