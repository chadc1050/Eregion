#include "eregion/Window/Window.h"

using namespace eregion;

namespace eregion {
Window* Window::create(WindowConfig config) {

    Window* window = new Window();

    window->config = config;

    return window;
}

Result<void> Window::run() {

    // Error callback to recieve error information
    glfwSetErrorCallback(errorCallback);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* glWindow = glfwCreateWindow(config.width, config.height, config.title.c_str(), NULL, NULL);
    if (!glWindow) {
        return Result<void>(Error{"Error creating window"});
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(glWindow);

    // vsync
    glfwSwapInterval(1);

    this->glWindow = glWindow;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(glWindow)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(glWindow);
        /* Poll for and process events */
        glfwPollEvents();
    }

    return Result<void>();
}

Window::Window() {}

Window::~Window() {
    if (glWindow) {
        glfwDestroyWindow(glWindow);
        printf("Destroyed instance of window.\n");
    }
}

void Window::errorCallback(int error, const char* description) { fprintf(stderr, "Error: %s\n", description); }

void Window::setGlWindow(GLFWwindow* glWindow) { this->glWindow = glWindow; }

GLFWwindow* Window::getGlWindow() { return glWindow; }
} // namespace eregion
