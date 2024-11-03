#include "eregion/Asset/Sprite.hpp"

using namespace eregion;

namespace eregion {

Sprite::Sprite(Texture* texture) {
    this->texture = texture;
    this->textureCoords = {glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 1.0f)};
}

Sprite::Sprite(Texture* texture, std::array<glm::vec2, 4> textureCoords) {
    this->texture = texture;
    this->textureCoords = textureCoords;
}

Texture* Sprite::getTexture() { return texture; }

std::array<glm::vec2, 4> Sprite::getTextureCoords() { return textureCoords; }

} // namespace eregion