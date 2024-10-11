#pragma once

#include "eregion/Asset/Texture.hpp"
#include "eregion/Core/Result.hpp"
#include "eregion/Logger/Logger.hpp"

#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "stb_image.h"

namespace eregion {
class TextureProgram {
  public:
    static Result<TextureProgram*> compile(Texture* texture);
    void bind();
    void unbind();
    bool isActive();
    int getTextureId();

    ~TextureProgram();

  private:
    unsigned int textureId;
    int width;
    int height;
    bool active;

    TextureProgram(unsigned int textureId, int width, int height);
};
} // namespace eregion