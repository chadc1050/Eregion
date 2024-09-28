#include "eregion/Asset/Shader.h"

using namespace eregion;

namespace eregion {
Result<ShaderType> getShaderType(std::string ext) {
    if (ext == "vert") {
        return Result<ShaderType>(Success{ShaderType::VERTEX});
    }

    if (ext == "frag") {
        return Result<ShaderType>(Success{ShaderType::FRAGMENT});
    }
    return Result<ShaderType>(Success{ShaderType::FRAGMENT});
}
} // namespace eregion