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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* glWindow = glfwCreateWindow(config.width, config.height, config.title.c_str(), NULL, NULL);
    if (!glWindow) {
        return Result<void>(Error{"Error creating window"});
    }

    setGlWindow(glWindow);

    printf("Setting window context to current.\n");

    glfwSetKeyCallback(this->glWindow, keyCallback);

    // Make the window's context current
    glfwMakeContextCurrent(this->glWindow);
    int version = gladLoadGL(glfwGetProcAddress);

    if (version == 0) {
        return Result<void>(Error{"Failed to instantiate GLAD context."});
    }

    printf("OpenGL Version: %s\nGLAD Version: %d\n", glGetString(GL_VERSION), version);

    // V-Sync
    glfwSwapInterval(1);

    AssetPool& pool = AssetPool::getInstance();

    auto vertRes = pool.getShader("../assets/shaders/example.vert");

    if (vertRes.isError()) {
        return Result<void>(Error{"Error loading vertice shader!"});
    }

    auto fragRes = pool.getShader("../assets/shaders/example.frag");

    if (fragRes.isError()) {
        return Result<void>(Error{"Error loading fragment shader!"});
    }

    // NOTE: OpenGL error checks have been omitted for brevity
    printf("Creating vertex buffer.\n");
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // compile vertex shader
    auto vert = vertRes.getValue().src;

    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, (const GLchar**)&vert, NULL);
    glCompileShader(vertex_shader);

    GLint shaderOk;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &shaderOk);
    if (shaderOk != GL_TRUE) {
        GLsizei log_length;
        char info_log[8192];
        glGetShaderInfoLog(vertex_shader, 8192, &log_length, info_log);
        fprintf(stderr, "ERROR: %s", info_log);

        return Result<void>(Error{"Error compiling shader!"});
    }

    // compile fragment shader
    auto frag = fragRes.getValue().src;

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, (const GLchar**)&frag, NULL);
    glCompileShader(fragment_shader);

    const GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    const GLint mvp_location = glGetUniformLocation(program, "MVP");
    const GLint vpos_location = glGetAttribLocation(program, "vPos");
    const GLint vcol_location = glGetAttribLocation(program, "vCol");

    printf("Creating vertex array.\n");
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

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp);
        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap front and back buffers and poll for and process events
        glfwSwapBuffers(this->glWindow);
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

void Window::keyCallback(GLFWwindow* glWindow, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        printf("Pressed key: %d\n", key);
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(glWindow, GLFW_TRUE);
    }
}

void Window::setGlWindow(GLFWwindow* glWindow) { this->glWindow = glWindow; }

GLFWwindow* Window::getGlWindow() { return glWindow; }
} // namespace eregion
