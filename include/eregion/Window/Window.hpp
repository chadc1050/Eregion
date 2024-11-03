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
    bool vSync;
};

class Window {
  public:
    static Result<Window*> create(WindowConfig config);
    Result<void> run();
    void changeScene(Scene* next);
    ~Window();

  private:
    GLFWwindow* glWindow;
    Scene* currentScene;
    WindowConfig config;

    Window(GLFWwindow* window, WindowConfig config);
    Result<void> loop();
    static void frameSizeCallback(GLFWwindow* window, int width, int height);
};
} // namespace eregion