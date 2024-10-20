#include "eregion/Asset/Texture.hpp"

using namespace eregion;

namespace eregion {

Result<Texture*> Texture::compile(std::string name, unsigned char* src, int width, int height, int channels) {

    debug("Compiling texture: " + name);

    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Set Texture Params
    // Repeat image in both directions
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Pixelation (Should be configurable)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Check color channel compatibility
    switch (channels) {
    case 3:
        debug("Texture is using 3 color channel.");

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, src);

        break;
    case 4:
        debug("Texture is using 4 color channel.");

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, src);

        break;
    default:
        return Result<Texture*>(Error{"Texture channels: " + std::to_string(channels) + " is not supported!"});
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    return Result<Texture*>(Success<Texture*>{new Texture(name, textureId, width, height, channels)});
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, id);
    active = true;
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
    active = false;
}

bool Texture::isActive() { return active; }

int Texture::getTextureId() { return id; }

std::string Texture::getName() { return name; }

unsigned int Texture::getWidth() { return width; }

unsigned int Texture::getHeight() { return height; }

Texture::Texture(std::string name, unsigned int textureId, int width, int height, int channels) {
    this->name = name;
    this->id = textureId;
    this->width = width;
    this->height = height;
    this->channels = channels;
}

Texture::~Texture() {
    warn("Deleting texture program");
    glDeleteTextures(1, &id);
}
} // namespace eregion