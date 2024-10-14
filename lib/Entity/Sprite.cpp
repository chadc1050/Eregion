#include "eregion/Entity/Sprite.hpp"

using namespace eregion;

namespace eregion {

Texture* Sprite::getTexture() { return texture; }

std::array<glm::vec2, 4> Sprite::getTextureCoords() {
    std::array<glm::vec2, 4> texCoords = {glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 0.0f),
                                          glm::vec2(0.0f, 1.0f)};

    return texCoords;
}
} // namespace eregion