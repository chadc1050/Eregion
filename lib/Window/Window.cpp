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

    info("Setting window context to current.");

    glfwSetKeyCallback(this->glWindow, keyCallback);

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

    // Create vertex buffer
    info("Creating vertex buffer.");
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Load assets
    AssetPool& pool = AssetPool::getInstance();

    auto vertRes = pool.getShader("../assets/shaders/example.vert");

    if (vertRes.isError()) {
        return Result<void>(Error{"Error loading vertex shader!"});
    }

    auto fragRes = pool.getShader("../assets/shaders/example.frag");

    if (fragRes.isError()) {
        return Result<void>(Error{"Error loading fragment shader!"});
    }

    // Create Program
    auto progRes = createProgram(vertRes.getValue(), fragRes.getValue());

    if (progRes.isError()) {
        return Result<void>(Error{"Error creating GL Program!"});
    }

    GLuint program = progRes.getValue();

    const GLint mvp_location = glGetUniformLocation(program, "MVP");
    const GLint vpos_location = glGetAttribLocation(program, "vPos");
    const GLint vcol_location = glGetAttribLocation(program, "vCol");

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
        warn("Destroyed instance of window.");
    }
}

Result<GLuint> Window::createProgram(Shader vertex, Shader fragment) {

    // Compile vertex shader
    auto vertCompRes = createShader(vertex);

    if (vertCompRes.isError()) {
        return Result<GLuint>(Error{"Error compiling vertex shader!"});
    }

    GLuint vertex_shader = vertCompRes.getValue();

    // Compile fragment shader
    auto fragCompRes = createShader(fragment);

    if (fragCompRes.isError()) {
        glDeleteShader(vertex_shader);
        return Result<GLuint>(Error{"Error compiling fragment shader!"});
    }

    GLuint fragment_shader = fragCompRes.getValue();

    // Create program
    GLuint program = glCreateProgram();

    // Link shaders to program
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    // Check for errors
    GLint program_ok;
    glGetProgramiv(program, GL_LINK_STATUS, &program_ok);

    if (program_ok != GL_TRUE) {
        GLsizei log_length;
        char info_log[8192];

        fprintf(stderr, "ERROR: Failed to link shader program\n");
        glGetProgramInfoLog(program, 8192, &log_length, info_log);
        fprintf(stderr, "ERROR: %s", info_log);

        // Cleanup
        glDeleteProgram(program);
        glDeleteShader(fragment_shader);
        glDeleteShader(vertex_shader);

        return Result<GLuint>(Error{"Error compiling fragment shader!"});
    }

    return Result<GLuint>(Success<GLuint>{program});
}

Result<GLuint> Window::createShader(Shader shader) {

    auto res = getShaderRef(shader.type);

    if (res.isError()) {
        return Result<GLuint>(Error{"Error determining shader type ref!"});
    }

    const GLuint glShader = glCreateShader(res.getValue());
    glShaderSource(glShader, 1, (const GLchar**)&shader.src, NULL);
    glCompileShader(glShader);

    GLint shaderOk;
    glGetShaderiv(glShader, GL_COMPILE_STATUS, &shaderOk);
    if (shaderOk != GL_TRUE) {
        GLsizei log_length;
        char info_log[8192];
        glGetShaderInfoLog(glShader, 8192, &log_length, info_log);
        fprintf(stderr, "ERROR: %s", info_log);

        return Result<GLuint>(Error{"Error compiling shader!"});
    }

    return Result<GLuint>(Success<GLuint>{glShader});
}

Result<GLuint> Window::getShaderRef(ShaderType type) {
    if (type == VERTEX) {
        return Result<GLuint>(Success<GLuint>{GL_VERTEX_SHADER});
    }

    if (type == FRAGMENT) {
        return Result<GLuint>(Success<GLuint>{GL_FRAGMENT_SHADER});
    }

    if (type == GEOMETRY) {
        return Result<GLuint>(Success<GLuint>{GL_GEOMETRY_SHADER});
    }

    return Result<GLuint>(Error{"Error determining reference for shader!"});
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
