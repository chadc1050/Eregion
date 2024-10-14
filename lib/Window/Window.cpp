#include "eregion/Window/Window.hpp"

using namespace eregion;

namespace eregion {

Window* Window::create(WindowConfig config) { return new Window(config, new Scene()); }

Result<void> Window::run() {

    // Error callback to recieve error information
    glfwSetErrorCallback(errorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* glWindow = glfwCreateWindow(config.width, config.height, config.title.c_str(), NULL, NULL);
    if (!glWindow) {
        return Result<void>(Error{"Error creating window"});
    }

    setGlWindow(glWindow);

    glfwSetWindowUserPointer(glWindow, this);

    info("Setting window context to current.");

    // Set callbacks
    glfwSetKeyCallback(this->glWindow, KeyListener::keyCallback);
    glfwSetCursorPosCallback(this->glWindow, MouseListener::posCallback);
    glfwSetMouseButtonCallback(this->glWindow, MouseListener::buttonCallback);
    glfwSetScrollCallback(this->glWindow, MouseListener::scrollCallback);
    glfwSetFramebufferSizeCallback(this->glWindow, frameSizeCallback);

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

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debugCallback, 0);

    // V-Sync
    glfwSwapInterval(GL_TRUE);

    // Config blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    // TODO: This is needed to initialize the camera aspect ratio.
    frameSizeCallback(this->glWindow, config.width, config.height);

    currentScene->init();

    loop();

    return Result<void>();
}

Window::Window(WindowConfig config, Scene* currentScene) {
    this->config = config;
    this->currentScene = currentScene;
}

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

        // Set the clear color for the window
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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
        glfwPollEvents();
    }

    return Result<void>();
}

void Window::frameSizeCallback(GLFWwindow* window, int width, int height) {
    debug("Viewport resized.");
    glViewport(0, 0, width, height);

    // This is some GLFW magic to aquire the window pointer through prior coupling.
    Window* inst = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (inst && inst->currentScene) {
        debug("Window instance located.");
        inst->currentScene->viewportUpdate(width, height);
    }
}

void Window::setGlWindow(GLFWwindow* glWindow) { this->glWindow = glWindow; }

GLFWwindow* Window::getGlWindow() { return glWindow; }
} // namespace eregion
