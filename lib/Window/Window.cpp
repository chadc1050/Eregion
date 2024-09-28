#include "eregion/Window/Window.h"

using namespace eregion;

namespace eregion {
Result<Window> Window::create() {

    Window window = Window();

    // Error callback to recieve error information
    glfwSetErrorCallback(errorCallback);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* glWindow = glfwCreateWindow(640, 480, "Celebrimbor", NULL, NULL);
    if (!glWindow) {
        return Result<Window>(Error{"Error creating window"});
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(glWindow);

    // vsync
    glfwSwapInterval(1);

    window.setGlWindow(glWindow);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(glWindow)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(glWindow);
        /* Poll for and process events */
        glfwPollEvents();
    }

    return Result<Window>(Success<Window>{window});
}

Window::Window() {}

void Window::errorCallback(int error, const char* description) { fprintf(stderr, "Error: %s\n", description); }

void Window::setGlWindow(GLFWwindow* glWindow) { this->glWindow = glWindow; }

GLFWwindow* Window::getGlWindow() { return glWindow; }
} // namespace eregion
