#pragma once

#include "eregion/Asset/AssetPool.h"
#include "eregion/Core/KeyListener.h"
#include "eregion/Core/MouseListener.h"
#include "eregion/Core/Result.h"
#include "eregion/Core/Scene.h"
#include "eregion/Logger/Logger.h"
#include "eregion/Render/ShaderProgram.h"

#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "linmath.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <variant>

namespace eregion {

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
    Scene currentScene;
    WindowConfig config;

    Window();
    Result<void> loop();
    static void errorCallback(int errCode, const char* desc);
    void setGlWindow(GLFWwindow* window);
    GLFWwindow* getGlWindow();
};
} // namespace eregion