#include "eregion/Core/MouseListener.h"

using namespace eregion;

namespace eregion {

MouseListener& MouseListener::getInstance() {
    // Guaranteed to be destroyed
    static MouseListener instance;
    return instance;
}

bool MouseListener::isButtonPressed(int button) {
    MouseListener& inst = MouseListener::getInstance();
    return button < 5 && inst.keysPressed[button];
}

glm::vec2 MouseListener::getCurrPos() {
    MouseListener& inst = MouseListener::getInstance();
    return {inst.currPos.x, inst.currPos.y};
}

glm::vec2 MouseListener::getPosChange() {
    MouseListener& inst = MouseListener::getInstance();
    return {inst.currPos.x - inst.prevPos.x, inst.currPos.y - inst.prevPos.y};
}

void MouseListener::buttonCallback(GLFWwindow* glWindow, int keyCode, int action, int mods) {
    MouseListener& inst = MouseListener::getInstance();

    if (action == GLFW_PRESS) {
        debug("Pressed mouse button: " + std::to_string(keyCode));
        inst.keysPressed[keyCode] = true;

    } else if (action == GLFW_RELEASE) {
        debug("Released mouse button: " + std::to_string(keyCode));
        inst.keysPressed[keyCode] = false;
    }
}
void MouseListener::posCallback(GLFWwindow* glWindow, double xPos, double yPos) {
    MouseListener& inst = MouseListener::getInstance();

    trace("Mouse position change: (" + std::to_string(xPos) + ", " + std::to_string(yPos) + ")");
    inst.prevPos.x = inst.currPos.x;
    inst.prevPos.y = inst.currPos.y;
    inst.currPos.x = xPos;
    inst.currPos.y = yPos;
}

void MouseListener::scrollCallback(GLFWwindow* glWindow, double xOffset, double yOffset) {

    MouseListener& inst = MouseListener::getInstance();
    debug("Mouse scroll offset change: (" + std::to_string(xOffset) + ", " + std::to_string(yOffset) + ")");

    inst.scroll.x = xOffset;
    inst.scroll.y = yOffset;
}

MouseListener::MouseListener() {
    keysPressed = {};
    currPos.x = 0.0;
    currPos.y = 0.0;
    prevPos.x = 0.0;
    prevPos.y = 0.0;
    scroll.x = 0.0;
    scroll.y = 0.0;
}

} // namespace eregion