#ifndef EREGION_WINDOW_H
#define EREGION_WINDOW_H

#include "eregion/Core/Result.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
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
    WindowConfig config;

    Window();
    static void errorCallback(int error, const char* description);
    void setGlWindow(GLFWwindow* window);
    GLFWwindow* getGlWindow();
};
} // namespace eregion

#endif