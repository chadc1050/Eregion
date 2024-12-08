#include "eregion/Asset/Texture.hpp"

using namespace eregion;

namespace eregion {

Result<Texture*> Texture::compile(std::string name, unsigned char* buffer, int width, int height, int channels,
                                  TextureOptions options) {

    trace("Compiling texture: " + name);

    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Set Texture Parameters
    // Texture Wrap S Coordinate
    switch (options.wrapS) {
    case Wrap::CLAMP_TO_EDGE:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        break;
    case Wrap::CLAMP_TO_BORDER:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        break;
    case Wrap::MIRRORED_REPEAT:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        break;
    case Wrap::REPEAT:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        break;
    case Wrap::MIRRORED_CLAMP_TO_EDGE:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRROR_CLAMP_TO_EDGE);
        break;
    }

    // Texture Wrap T Coordinate
    switch (options.wrapT) {
    case Wrap::CLAMP_TO_EDGE:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        break;
    case Wrap::CLAMP_TO_BORDER:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        break;
    case Wrap::MIRRORED_REPEAT:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        break;
    case Wrap::REPEAT:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        break;
    case Wrap::MIRRORED_CLAMP_TO_EDGE:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRROR_CLAMP_TO_EDGE);
        break;
    }

    // Texture Minifying function
    switch (options.minFilter) {
    case MinFilter::NEAREST:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        break;
    case MinFilter::LINEAR:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        break;
    case MinFilter::NEAREST_MIPMAP_NEAREST:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        break;
    case MinFilter::LINEAR_MIPMAP_NEAREST:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        break;
    case MinFilter::NEAREST_MIPMAP_LINEAR:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        break;
    case MinFilter::LINEAR_MIPMAP_LINEAR:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        break;
    }

    // Texture Magnification Function
    switch (options.magFilter) {
    case MagFilter::NEAREST:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        break;
    case MagFilter::LINEAR:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
    }

    // Check color channel compatibility
    switch (channels) {
    case 1:
        trace("Texture is using single channel bitmap.");
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, buffer);
        break;
    case 3:
        trace("Texture is using 3 color channel.");
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
        break;
    case 4:
        trace("Texture is using 4 color channel.");
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        break;
    default:
        return Result<Texture*>(Error{"Texture channels: " + std::to_string(channels) + " is not supported!"});
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    // Clean up
    glBindTexture(GL_TEXTURE_2D, 0);

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