#ifndef EREGION_KEYLISTENER_H
#define EREGION_KEYLISTENER_H

#include "eregion/Logger/Logger.h"

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

    // TODO: This should potentially be set up as a friend to Window to make access stricter
    static void keyCallback(GLFWwindow* glWindow, int keyCode, int scanCode, int action, int mods);

    // Delete copy constructor and assignment operator to prevent copying
    KeyListener(const KeyListener&) = delete;
    KeyListener& operator=(const KeyListener&) = delete;

  private:
    KeyListener();
    ~KeyListener() = default;
    static const int MAX_KEY = 350;

    std::array<bool, MAX_KEY> keysPressed;
};
} // namespace eregion

#endif