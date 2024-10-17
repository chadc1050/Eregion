#pragma once

#include "eregion/Asset/Texture.hpp"
#include "eregion/Entity/Sprite.hpp"

namespace eregion {
class SpriteSheet {

  public:
    SpriteSheet(Texture* texture);
    Sprite getSprite(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

  private:
    Texture* texture;
};
} // namespace eregion