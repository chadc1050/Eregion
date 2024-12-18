#pragma once

#include "eregion/Asset/Shader.hpp"
#include "eregion/Core/Result.hpp"
#include "eregion/Logger/Logger.hpp"

#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace eregion {
class ShaderProgram {
  public:
    static Result<ShaderProgram*> compile(Shader vert, Shader fragment);
    void bind();
    void detach();
    void unbind();
    bool isActive();
    unsigned int getProgramId();

    // Array uploads
    Result<void> uploadIntArray(const char* var, int* arr, size_t size);

    // Matrix uploads
    Result<void> uploadMat4(const char* var, glm::mat4 mat) const;

    // Vector uploads
    Result<void> uploadVec4(const char* var, glm::vec4 vec);
    Result<void> uploadVec3(const char* var, glm::vec3 vec);
    Result<void> uploadVec2(const char* var, glm::vec2 vec);

    // Primitive uploads
    Result<void> uploadInt(const char* var, int val);
    Result<void> uploadFloat(const char* var, float val);

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