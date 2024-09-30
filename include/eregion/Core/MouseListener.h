#ifndef EREGION_MOUSELISTENER_H
#define EREGION_MOUSELISTENER_H

#include "eregion/Logger/Logger.h"

#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "linmath.h"

#include <array>
#include <string>

namespace eregion {

class MouseListener {
  public:
    static MouseListener& getInstance();

    // Delete copy constructor and assignment operator to prevent copying
    MouseListener(const MouseListener&) = delete;
    MouseListener& operator=(const MouseListener&) = delete;

    // Callbacks
    // TODO: This should potentially be set up as a friend to Window to make access stricter
    static void mouseButtonCallback(GLFWwindow* glWindow, int keyCode, int action, int mods);
    static void mousePosCallback(GLFWwindow* glWindow, double xpos, double ypos);

  private:
    MouseListener();
    ~MouseListener() = default;
    static const int MAX_KEY = 5;

    vec2 prevPos;
    vec2 currPos;
    vec2 scroll;

    std::array<bool, MAX_KEY> keysPressed;
};
} // namespace eregion

#endif