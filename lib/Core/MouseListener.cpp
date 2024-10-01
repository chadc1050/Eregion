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

std::array<float, 2> MouseListener::getCurrPos() {
    MouseListener& inst = MouseListener::getInstance();
    return {inst.currPos[0], inst.currPos[1]};
}

std::array<float, 2> MouseListener::getPosChange() {
    MouseListener& inst = MouseListener::getInstance();
    return {inst.currPos[0] - inst.prevPos[0], inst.currPos[1] - inst.prevPos[1]};
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
    inst.prevPos[0] = inst.currPos[0];
    inst.prevPos[1] = inst.currPos[1];
    inst.currPos[0] = xPos;
    inst.currPos[1] = yPos;
}

void MouseListener::scrollCallback(GLFWwindow* glWindow, double xOffset, double yOffset) {

    MouseListener& inst = MouseListener::getInstance();
    debug("Mouse scroll offset change: (" + std::to_string(xOffset) + ", " + std::to_string(yOffset) + ")");

    inst.scroll[0] = xOffset;
    inst.scroll[1] = yOffset;
}

MouseListener::MouseListener() {
    keysPressed = {};
    currPos[0] = 0.0;
    currPos[1] = 0.0;
    prevPos[0] = 0.0;
    prevPos[1] = 0.0;
    scroll[0] = 0.0;
    scroll[1] = 0.0;
}

} // namespace eregion