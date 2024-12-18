#pragma once

#include "eregion/Asset/Sprite.hpp"
#include "eregion/Asset/Texture.hpp"

namespace eregion {
class UniformSpriteSheet {

  public:
    UniformSpriteSheet(Texture* texture, unsigned int width, unsigned int height);
    Sprite getSprite(unsigned int idx);

  private:
    Texture* texture;
    unsigned int spriteWidth;
    unsigned int spriteHeight;

    unsigned int dimX;

    float relWidth;
    float relHeight;
};
} // namespace eregion