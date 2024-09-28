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
class Window {
  public:
    static Result<Window> create();

  private:
    GLFWwindow* glWindow;

    Window();
    static void errorCallback(int error, const char* description);
    void setGlWindow(GLFWwindow* window);
    GLFWwindow* getGlWindow();
};
} // namespace eregion

#endif