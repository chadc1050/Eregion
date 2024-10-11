#include "eregion/Render/TextureProgram.h"

using namespace eregion;

namespace eregion {

Result<TextureProgram*> TextureProgram::compile(Texture* texture) {

    debug("Compiling texture: " + texture->name);

    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Set Texture Params
    // Repeat image in both directions
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Pixelation
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Check color channel compatibility
    switch (texture->channels) {
    case 3:
        debug("Texture is using 3 color channel.");

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                     texture->src);

        break;
    case 4:
        debug("Texture is using 4 color channel.");

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     texture->src);

        break;
    default:
        return Result<TextureProgram*>(
            Error{"Texture channels: " + std::to_string(texture->channels) + " is not supported!"});
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(texture->src);

    return Result<TextureProgram*>(
        Success<TextureProgram*>{new TextureProgram(textureId, texture->width, texture->height)});
}

void TextureProgram::bind() {
    glBindTexture(GL_TEXTURE_2D, textureId);
    active = true;
}

void TextureProgram::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
    active = false;
}

bool TextureProgram::isActive() { return active; }

int TextureProgram::getTextureId() { return textureId; }

TextureProgram::TextureProgram(unsigned int textureId, int width, int height) {
    this->textureId = textureId;
    this->width = width;
    this->height = height;
}

TextureProgram::~TextureProgram() {
    warn("Deleting texture program");
    glDeleteTextures(1, &textureId);
}

} // namespace eregion