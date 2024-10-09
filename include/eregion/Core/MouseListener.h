#pragma once

#include "eregion/Logger/Logger.h"

#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <array>
#include <string>

namespace eregion {

class MouseListener {
  public:
    static MouseListener& getInstance();

    static bool isButtonPressed(int button);
    static glm::vec2 getCurrPos();
    static glm::vec2 getPosChange();

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

    glm::vec2 prevPos;
    glm::vec2 currPos;
    glm::vec2 scroll;

    std::array<bool, MAX_KEY> keysPressed;
};
} // namespace eregion