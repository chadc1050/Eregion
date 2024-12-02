#pragma once

#include <string>

#include "eregion/Asset/Texture.hpp"
#include "eregion/Core/Result.hpp"
#include "eregion/Logger/Logger.hpp"

#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "stb_image.h"

namespace eregion {

enum class Wrap { CLAMP_TO_EDGE, CLAMP_TO_BORDER, MIRRORED_REPEAT, REPEAT, MIRRORED_CLAMP_TO_EDGE };

enum class MagFilter { NEAREST, LINEAR };

enum class MinFilter {
    NEAREST,
    LINEAR,
    NEAREST_MIPMAP_NEAREST,
    LINEAR_MIPMAP_NEAREST,
    NEAREST_MIPMAP_LINEAR,
    LINEAR_MIPMAP_LINEAR,
};

struct TextureOptions {
    MinFilter minFilter;
    MagFilter magFilter;
    Wrap wrapS;
    Wrap wrapT;
};

class Texture {
  public:
    static Result<Texture*> compile(std::string name, unsigned char* buffer, int width, int height, int channels,
                                    TextureOptions options);
    void bind();
    void unbind();
    bool isActive();
    int getTextureId();
    std::string getName();
    unsigned int getWidth();
    unsigned int getHeight();

    ~Texture();

  private:
    std::string name;
    unsigned int id;
    int width;
    int height;
    int channels;
    bool active;

    Texture(std::string name, unsigned int textureId, int width, int height, int channels);
};
} // namespace eregion