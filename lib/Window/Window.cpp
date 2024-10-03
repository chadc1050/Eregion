#include "eregion/Window/Window.h"

using namespace eregion;

namespace eregion {

// TODO: Temporary setup, this needs to be abstracted
typedef struct Vertex {
    vec2 pos;
    vec3 col;
} Vertex;

static const Vertex vertices[3] = {
    {{-0.6f, -0.4f}, {1.f, 0.f, 0.f}}, {{0.6f, -0.4f}, {0.f, 1.f, 0.f}}, {{0.f, 0.6f}, {0.f, 0.f, 1.f}}};

Window* Window::create(WindowConfig config) {

    Window* window = new Window();

    window->config = config;

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
    glfwSwapInterval(1);

    // Config blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    loop();

    return Result<void>();
}

Window::Window() {}

Window::~Window() {
    if (glWindow) {
        glfwDestroyWindow(glWindow);
        warn("Destroyed instance of window.");
    }
}

Result<void> Window::loop() {

    // Create vertex buffer
    info("Creating vertex buffer.");
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Load assets
    auto vertRes = AssetPool::getShader("../assets/shaders/example.vert");

    if (vertRes.isError()) {
        return Result<void>(Error{"Error loading vertex shader!"});
    }

    auto fragRes = AssetPool::getShader("../assets/shaders/example.frag");

    if (fragRes.isError()) {
        return Result<void>(Error{"Error loading fragment shader!"});
    }

    // Create Program
    auto progRes = ShaderProgram::compile(vertRes.getValue(), fragRes.getValue());

    if (progRes.isError()) {
        return Result<void>(Error{"Error creating GL Program!"});
    }

    ShaderProgram* shaderProgram = progRes.getValue();

    shaderProgram->use();

    GLuint programId = shaderProgram->getProgramId();

    const GLint mvp_location = glGetUniformLocation(programId, "MVP");
    const GLint vpos_location = glGetAttribLocation(programId, "vPos");
    const GLint vcol_location = glGetAttribLocation(programId, "vCol");

    info("Creating vertex array.");
    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(this->glWindow)) {
        // Render
        int width, height;
        glfwGetFramebufferSize(this->glWindow, &width, &height);
        const float ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        mat4x4 m, p, mvp;
        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float)glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp);
        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap front and back buffers and poll for and process events
        glfwSwapBuffers(this->glWindow);
        glfwPollEvents();
    }

    delete shaderProgram;

    return Result<void>();
}

void Window::errorCallback(int errCode, const char* desc) {
    error("GL ERROR [" + std::to_string(errCode) + "] - " + desc);
}

void Window::setGlWindow(GLFWwindow* glWindow) { this->glWindow = glWindow; }

GLFWwindow* Window::getGlWindow() { return glWindow; }
} // namespace eregion
