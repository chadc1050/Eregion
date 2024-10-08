#include "eregion/Render/TextureProgram.h"

using namespace eregion;

namespace eregion {

Result<TextureProgram*> TextureProgram::compile(Texture* texture) {

    debug("Compiling texture: " + texture->name);

    unsigned int textureId;
    glGenTextures(1, &textureId);

    // TODO: May or may not be needed ideally we may want to pregenerate all the buffering and bind with a single step.
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Check color channel compatibility
    switch (texture->channels) {
    case 3:
        debug("Texture is using 3 color channel.");

        glTexStorage2D(GL_TEXTURE_2D, 2, GL_RGBA8, texture->width, texture->height);

        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture->width, texture->height, GL_RGB, GL_UNSIGNED_BYTE,
                        texture->src);

        break;
    case 4:
        debug("Texture is using 4 color channel.");

        glTexStorage2D(GL_TEXTURE_2D, 2, GL_RGBA8, texture->width, texture->height);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture->width, texture->height, GL_RGBA, GL_UNSIGNED_BYTE,
                        texture->src);

        break;
    default:
        return Result<TextureProgram*>(
            Error{"Texture channels: " + std::to_string(texture->channels) + " is not supported!"});
    }

    // Set Texture Params
    // Repeat image in both directions
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Pixelation
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

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

TextureProgram::~TextureProgram() { glDeleteTextures(1, &textureId); }

} // namespace eregion