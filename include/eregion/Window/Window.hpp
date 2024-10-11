#pragma once

#include "eregion/Core/KeyListener.hpp"
#include "eregion/Core/MouseListener.hpp"
#include "eregion/Core/Result.hpp"
#include "eregion/Core/Scene.hpp"
#include "eregion/Logger/Logger.hpp"
#include "eregion/Util/OpenGLUtils.hpp"

#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

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
    Scene* currentScene;
    WindowConfig config;

    Window();
    Result<void> loop();
    static void frameSizeCallback(GLFWwindow* window, int width, int height);
    void setGlWindow(GLFWwindow* window);
    GLFWwindow* getGlWindow();
};
} // namespace eregion