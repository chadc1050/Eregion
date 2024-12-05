#include "eregion/Window/Window.hpp"

using namespace eregion;

namespace eregion {

Result<Window*> Window::create(WindowConfig config) {

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
        return Result<Window*>(Error{"Error creating window"});
    }

    Window* window = new Window(glWindow, config);

    glfwSetWindowUserPointer(glWindow, window);

    info("Setting window context to current.");

    // Set callbacks
    glfwSetKeyCallback(glWindow, KeyListener::keyCallback);
    glfwSetCursorPosCallback(glWindow, MouseListener::posCallback);
    glfwSetMouseButtonCallback(glWindow, MouseListener::buttonCallback);
    glfwSetScrollCallback(glWindow, MouseListener::scrollCallback);
    glfwSetFramebufferSizeCallback(glWindow, frameSizeCallback);

    info("Linked peripheral callbacks.");

    // Make the window's context current
    glfwMakeContextCurrent(glWindow);

    int version = gladLoadGL(glfwGetProcAddress);

    if (version == 0) {
        return Result<Window*>(Error{"Failed to instantiate GLAD context."});
    }

    std::string versionStr(reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    info("OpenGL Version: " + versionStr);
    info("GLAD Version: " + std::to_string(version));

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debugCallback, 0);

    // V-Sync
    glfwSwapInterval(config.vSync);

    // Config pixel store
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Trigger initial callback to send initial window data to consumers
    frameSizeCallback(glWindow, config.width, config.height);

    return Result<Window*>(Success<Window*>{window});
}

Result<void> Window::run() {

    loop();

    return Result<void>();
}

Window::Window(GLFWwindow* glWindow, WindowConfig config) {
    this->glWindow = glWindow;
    this->config = config;
    this->currentScene = nullptr;
}

Window::~Window() {

    if (currentScene) {
        delete currentScene;
        warn("Deleted scene.");
    }

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

        // Set the black color for the window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (dt > 0.0) {
            if (currentScene) {
                currentScene->update(dt);
                currentScene->draw();
            }
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

void Window::changeScene(Scene* next) {
    // Potentially may want to consider not deleting the scene
    if (currentScene) {
        delete currentScene;
    }

    currentScene = next;
    currentScene->init();
    // TODO: This should be removed.
    frameSizeCallback(glWindow, config.width, config.height);
}
} // namespace eregion
