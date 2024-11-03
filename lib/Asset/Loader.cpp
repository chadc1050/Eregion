#include "eregion/Asset/Loader.hpp"

using namespace eregion;

namespace eregion {
Loader::Loader() {
    // Initialize FreeType to load fonts
    if (FT_Init_FreeType(&ft)) {
        throw std::runtime_error("Could not init FreeType Library");
    }
}

Result<Shader> Loader::loadShader(std::string path) {
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

Result<Texture*> Loader::loadTexture(std::string path) {

    std::filesystem::path pathObj(path);

    std::string name = pathObj.stem().string();
    std::string extension = pathObj.extension().string();

    int width, height, channels;

    // stbi image load for gl binding compatibility
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (pixels == nullptr) {
        return Result<Texture*>(Error{"Could not read texture file!"});
    }

    std::string id = name + extension;

    auto res = Texture::compile(id, pixels, width, height, channels);

    if (res.isError()) {
        return Result<Texture*>(Error{"Error compiling texture file!"});
    }

    stbi_image_free(pixels);

    return Result<Texture*>(Success<Texture*>(res.getValue()));
}

Result<Font*> Loader::loadFont(std::string path, unsigned int fontSize) {
    std::filesystem::path pathObj(path);

    std::string name = pathObj.stem().string();
    std::string extension = pathObj.extension().string();

    FT_Face face;
    if (FT_New_Face(ft, path.c_str(), 0, &face)) {
        return Result<Font*>(Error{"Failed to load font!"});
    }

    std::string id = name + extension;

    auto res = Font::compile(face, id, fontSize);

    FT_Done_Face(face);

    if (res.isError()) {
        return Result<Font*>(Error{"Failed to load font! " + res.getError()});
    }

    return Result<Font*>(Success<Font*>(res.getValue()));
}

Loader::~Loader() { FT_Done_FreeType(ft); }

} // namespace eregion