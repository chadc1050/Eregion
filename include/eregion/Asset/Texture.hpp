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
class Texture {
  public:
    static Result<Texture*> compile(std::string name, unsigned char* src, int width, int height, int channels);
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
    unsigned char* src;
    int width;
    int height;
    int channels;
    bool active;

    Texture(std::string name, unsigned int textureId, int width, int height, int channels);
};
} // namespace eregion