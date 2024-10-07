#include "eregion/Window/Window.h"

using namespace eregion;

namespace eregion {

Window* Window::create(WindowConfig config) {

    Window* window = new Window();

    window->config = config;

    window->currentScene = new Scene();

    return window;
}

Result<void> Window::run() {

    // Error callback to recieve error information
    glfwSetErrorCallback(errorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* glWindow = glfwCreateWindow(config.width, config.height, config.title.c_str(), NULL, NULL);
    if (!glWindow) {
        return Result<void>(Error{"Error creating window"});
    }

    setGlWindow(glWindow);

    info("Setting window context to current.");

    // Set callbacks
    glfwSetKeyCallback(this->glWindow, KeyListener::keyCallback);
    glfwSetCursorPosCallback(this->glWindow, MouseListener::posCallback);
    glfwSetMouseButtonCallback(this->glWindow, MouseListener::buttonCallback);
    glfwSetScrollCallback(this->glWindow, MouseListener::scrollCallback);
    info("Linked peripheral callbacks.");

    // Make the window's context current
    glfwMakeContextCurrent(this->glWindow);
    int version = gladLoadGL(glfwGetProcAddress);

    if (version == 0) {
        return Result<void>(Error{"Failed to instantiate GLAD context."});
    }

    std::string versionStr(reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    info("OpenGL Version: " + versionStr);
    info("GLAD Version: " + std::to_string(version));

    // V-Sync
    glfwSwapInterval(GL_TRUE);

    // Config blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    currentScene->init();

    loop();

    return Result<void>();
}

Window::Window() {}

Window::~Window() {

    delete currentScene;

    if (glWindow) {
        glfwDestroyWindow(glWindow);
        warn("Destroyed instance of window.");
    }
}

Result<void> Window::loop() {

    double beginTime = getTime();
    double dt = 0.0;
    double endTime = 0.0;
    double fps = 0.0;

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(this->glWindow)) {

        glfwPollEvents();

        // Set the clear color for the window
        glClear(GL_COLOR_BUFFER_BIT);

        if (dt > 0.0) {
            currentScene->update(dt);
        }

        endTime = getTime();

        dt = endTime - beginTime;

        if (dt > 0.0) {
            fps = 1.0 / dt;
        }

        trace("FPS: " + std::to_string(fps));

        beginTime = endTime;

        // Swap front and back buffers and poll for and process events
        glfwSwapBuffers(this->glWindow);
    }

    return Result<void>();
}

void Window::errorCallback(int errCode, const char* desc) {
    error("GL ERROR [" + std::to_string(errCode) + "] - " + desc);
}

void Window::setGlWindow(GLFWwindow* glWindow) { this->glWindow = glWindow; }

GLFWwindow* Window::getGlWindow() { return glWindow; }
} // namespace eregion
