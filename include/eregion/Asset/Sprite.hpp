#pragma once

#include "eregion/Asset/Texture.hpp"

#include <glm/glm.hpp>

#include <array>

namespace eregion {
class Sprite {

  public:
    Sprite(Texture* texture);
    Sprite(Texture* texture, std::array<glm::vec2, 4> textureCoords);

    Texture* getTexture();
    std::array<glm::vec2, 4> getTextureCoords();

  private:
    Texture* texture;
    std::array<glm::vec2, 4> textureCoords;
};
} // namespace eregion