#include "eregion/Entity/SpriteRenderer.hpp"

using namespace eregion;

namespace eregion {

SpriteRenderer::SpriteRenderer(Sprite sprite) {
    this->sprite = sprite;
    this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

SpriteRenderer::SpriteRenderer(Sprite sprite, glm::vec4 color) {
    this->sprite = sprite;
    this->color = color;
}

void SpriteRenderer::update(float dt) {}

Sprite SpriteRenderer::getSprite() { return sprite; }

glm::vec4 SpriteRenderer::getColor() { return color; }
} // namespace eregion