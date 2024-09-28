#include "eregion/Asset/Loader.h"

using namespace eregion;

namespace eregion {
Result<Shader> loadShader(std::string absolutePath) {
    std::ifstream file(absolutePath);
    if (!file.is_open()) {
        return Result<Shader>(Error{"Could not open shader file!"});
    }

    std::filesystem::path pathObj(absolutePath);

    std::string name = pathObj.stem().string();
    std::string extension = pathObj.extension().string();

    // Get Shader Type
    auto typeRes = getShaderType(extension);
    if (typeRes.isError()) {
        return Result<Shader>(Error{"File extension of shader is invalid."});
    }

    // Determine file size
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string fileContents(size, '\0');
    file.read(&fileContents[0], size);

    return Result<Shader>(Success<Shader>(Shader{name, fileContents, typeRes.getValue()}));
}
} // namespace eregion