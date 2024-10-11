#include "eregion/Core/KeyListener.hpp"

using namespace eregion;

namespace eregion {

KeyListener& KeyListener::getInstance() {
    // Guaranteed to be destroyed
    static KeyListener instance;
    return instance;
}

bool KeyListener::isKeyPressed(int keyCode) {
    KeyListener& inst = KeyListener::getInstance();
    return keyCode < MAX_KEY && inst.keysPressed[keyCode];
}

// TODO: Eventually we may want to keep track of the window as well
void KeyListener::keyCallback(GLFWwindow* glWindow, int keyCode, int scanCode, int action, int mods) {

    KeyListener& inst = KeyListener::getInstance();

    if (action == GLFW_PRESS) {
        debug("Pressed key: " + std::to_string(keyCode));
        inst.keysPressed[keyCode] = true;

        // Debug code to escape window
        if (keyCode == GLFW_KEY_ESCAPE) {
            warn("ESC key has been pressed in debug.");
            glfwSetWindowShouldClose(glWindow, GLFW_TRUE);
        }

    } else if (action == GLFW_RELEASE) {
        debug("Released key: " + std::to_string(keyCode));
        inst.keysPressed[keyCode] = false;
    }
}

KeyListener::KeyListener() { keysPressed = {}; }
} // namespace eregion
