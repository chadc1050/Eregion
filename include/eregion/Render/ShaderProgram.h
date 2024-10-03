#pragma once

#include "eregion/Asset/Shader.h"
#include "eregion/Core/Result.h"
#include "eregion/Logger/Logger.h"

#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "linmath.h"

namespace eregion {
class ShaderProgram {
  public:
    static Result<ShaderProgram*> compile(Shader vert, Shader fragment);
    void use();
    void detach();
    void unbind();
    bool isActive();
    unsigned int getProgramId();

    void uploadMat4(const char* var, mat4x4* mat);

    ~ShaderProgram();

  private:
    bool active;
    unsigned int programId;
    unsigned int vertId;
    unsigned int fragId;

    ShaderProgram();

    static Result<unsigned int> createShader(Shader shader);
    static Result<unsigned int> getShaderRef(ShaderType type);
};
} // namespace eregion