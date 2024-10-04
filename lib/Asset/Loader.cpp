#include "eregion/Asset/Loader.h"

using namespace eregion;

namespace eregion {
Result<Shader> loadShader(std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return Result<Shader>(Error{"Could not open shader file!"});
    }

    std::filesystem::path pathObj(path);

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

    std::string id = name + extension;

    return Result<Shader>(Success<Shader>(Shader{id, fileContents, typeRes.getValue()}));
}

Result<Texture> loadTexture(std::string path) {

    std::filesystem::path pathObj(path);

    std::string name = pathObj.stem().string();
    std::string extension = pathObj.extension().string();

    int width, height, channels;

    // stbi image load for gl binding compatibility
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (pixels == nullptr) {
        return Result<Texture>(Error{"Could not read texture file!"});
    }

    std::string id = name + extension;

    return Result<Texture>(Success<Texture>(Texture{id, pixels, width, height, channels}));
}
} // namespace eregion