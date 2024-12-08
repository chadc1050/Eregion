#pragma once

#include "eregion/Logger/Logger.hpp"

#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <array>
#include <string>

namespace eregion {

class KeyListener {
  public:
    static KeyListener& getInstance();

    static bool isKeyPressed(int keyCode);

    // Delete copy constructor and assignment operator to prevent copying
    KeyListener(const KeyListener&) = delete;
    KeyListener& operator=(const KeyListener&) = delete;

  private:
    KeyListener();
    ~KeyListener() = default;
    static const int MAX_KEY = 350;

    std::array<bool, MAX_KEY> keysPressed;

    // Callback
    static void keyCallback(GLFWwindow* glWindow, int keyCode, int scanCode, int action, int mods);

    friend class Window;
};
} // namespace eregion