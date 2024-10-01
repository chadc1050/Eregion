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

    static bool isButtonPressed(int button);
    static std::array<float, 2> getCurrPos();
    static std::array<float, 2> getPosChange();

    // Delete copy constructor and assignment operator to prevent copying
    MouseListener(const MouseListener&) = delete;
    MouseListener& operator=(const MouseListener&) = delete;

    // Callbacks
    // TODO: This should potentially be set up as a friend to Window to make access stricter
    static void buttonCallback(GLFWwindow* glWindow, int keyCode, int action, int mods);
    static void posCallback(GLFWwindow* glWindow, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* glWindow, double xOffset, double yOffset);

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