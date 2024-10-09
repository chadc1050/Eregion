#include "eregion/Render/ShaderProgram.h"

using namespace eregion;

namespace eregion {

Result<ShaderProgram*> ShaderProgram::compile(Shader vert, Shader frag) {

    ShaderProgram* shaderProgram = new ShaderProgram();

    // Compile vertex shader
    Result<unsigned int> vertCompRes = createShader(vert);

    if (vertCompRes.isError()) {
        return Result<ShaderProgram*>(Error{"Error compiling vertex shader!"});
    }

    shaderProgram->vertId = vertCompRes.getValue();

    // Compile fragment shader
    Result<unsigned int> fragCompRes = createShader(frag);

    if (fragCompRes.isError()) {
        glDeleteShader(shaderProgram->vertId);
        return Result<ShaderProgram*>(Error{"Error compiling fragment shader!"});
    }

    shaderProgram->fragId = fragCompRes.getValue();

    // Create program
    shaderProgram->programId = glCreateProgram();

    // Link shaders to program
    glAttachShader(shaderProgram->programId, shaderProgram->vertId);
    glAttachShader(shaderProgram->programId, shaderProgram->fragId);
    glLinkProgram(shaderProgram->programId);

    // Check for errors
    GLint program_ok;
    glGetProgramiv(shaderProgram->programId, GL_LINK_STATUS, &program_ok);

    if (program_ok != GL_TRUE) {
        GLsizei log_length;
        char info_log[8192];

        error("Failed to link shader program");
        glGetProgramInfoLog(shaderProgram->programId, 8192, &log_length, info_log);
        error(info_log);

        // Cleanup
        delete shaderProgram;

        return Result<ShaderProgram*>(Error{"Error compiling fragment shader!"});
    }

    return Result<ShaderProgram*>(Success<ShaderProgram*>{shaderProgram});
}

void ShaderProgram::bind() {
    if (!active) {
        trace("Binding shader program: " + std::to_string(programId));
        glUseProgram(programId);
        active = true;
    }
}

void ShaderProgram::detach() {
    trace("Detaching shader from program: " + std::to_string(programId));
    glDetachShader(programId, vertId);
    glDetachShader(programId, fragId);
}

void ShaderProgram::unbind() {
    if (active) {
        trace("Unbinding shader program: " + std::to_string(programId));
        glUseProgram(0);
        active = false;
    }
}

bool ShaderProgram::isActive() { return active; }

unsigned int ShaderProgram::getProgramId() { return programId; }

void ShaderProgram::uploadIntArray(const char* var, int* arr, size_t size) {
    const int loc = glGetUniformLocation(programId, var);
    glUniform1iv(loc, size, arr);
}

void ShaderProgram::uploadMat4(const char* var, glm::mat4 mat) {

    const int loc = glGetUniformLocation(programId, var);

    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::uploadVec4(const char* var, glm::vec4 vec) {

    const int loc = glGetUniformLocation(programId, var);

    glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
}

void ShaderProgram::uploadVec3(const char* var, glm::vec3 vec) {

    const int loc = glGetUniformLocation(programId, var);

    glUniform3f(loc, vec.x, vec.y, vec.z);
}

void ShaderProgram::uploadVec2(const char* var, glm::vec2 vec) {

    const int loc = glGetUniformLocation(programId, var);

    glUniform2f(loc, vec.x, vec.y);
}

void ShaderProgram::uploadFloat(const char* var, float val) {

    const int loc = glGetUniformLocation(programId, var);

    glUniform1f(loc, val);
}

void ShaderProgram::uploadInt(const char* var, int val) {

    const int loc = glGetUniformLocation(programId, var);

    glUniform1i(loc, val);
}

ShaderProgram::~ShaderProgram() {
    glDeleteShader(vertId);
    glDeleteShader(fragId);
    glDeleteProgram(programId);
}

ShaderProgram::ShaderProgram() { active = false; }

Result<unsigned int> ShaderProgram::createShader(Shader shader) {

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
        error(info_log);

        return Result<unsigned int>(Error{"Error compiling shader!"});
    }

    return Result<unsigned int>(Success<unsigned int>{glShader});
}

Result<unsigned int> ShaderProgram::getShaderRef(ShaderType type) {
    if (type == VERTEX) {
        return Result<GLuint>(Success<GLuint>{GL_VERTEX_SHADER});
    }

    if (type == FRAGMENT) {
        return Result<GLuint>(Success<GLuint>{GL_FRAGMENT_SHADER});
    }

    if (type == GEOMETRY) {
        return Result<GLuint>(Success<GLuint>{GL_GEOMETRY_SHADER});
    }

    return Result<unsigned int>(Error{"Error determining reference for shader!"});
}

} // namespace eregion