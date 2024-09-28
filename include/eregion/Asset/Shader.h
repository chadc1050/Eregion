#ifndef EREGION_SHADER_H
#define EREGION_SHADER_H

#include "eregion/Core/Result.h"
#include <string>

namespace eregion {

enum ShaderType { VERTEX, FRAGMENT, GEOMETRY };

struct Shader {
    std::string name;
    std::string src;
    ShaderType type;
};

Result<ShaderType> getShaderType(std::string ext);
} // namespace eregion

#endif