#include "eregion/Core/MouseListener.h"

using namespace eregion;

namespace eregion {

MouseListener& MouseListener::getInstance() {
    // Guaranteed to be destroyed
    static MouseListener instance;
    return instance;
}

void MouseListener::mouseButtonCallback(GLFWwindow* glWindow, int keyCode, int action, int mods) {
    MouseListener& inst = MouseListener::getInstance();

    if (action == GLFW_PRESS) {
        debug("Pressed mouse button: " + std::to_string(keyCode));
        inst.keysPressed[keyCode] = true;

    } else if (action == GLFW_RELEASE) {
        debug("Released mouse button: " + std::to_string(keyCode));
        inst.keysPressed[keyCode] = false;
    }
}
void MouseListener::mousePosCallback(GLFWwindow* glWindow, double xPos, double yPos) {
    MouseListener& inst = MouseListener::getInstance();

    trace("Mouse position change: (" + std::to_string(xPos) + ", " + std::to_string(yPos) + ")");
    inst.prevPos[0] = inst.currPos[0];
    inst.prevPos[1] = inst.currPos[1];
    inst.currPos[0] = xPos;
    inst.currPos[1] = yPos;
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