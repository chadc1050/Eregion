#include "eregion/Entity/SpriteRenderer.hpp"

using namespace eregion;

namespace eregion {

SpriteRenderer::SpriteRenderer(std::shared_ptr<Sprite> sprite) {
    this->sprite = sprite;
    this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    this->zIndex = 0;
}

SpriteRenderer::SpriteRenderer(std::shared_ptr<Sprite> sprite, glm::vec4 color) {
    this->sprite = sprite;
    this->color = color;
    this->zIndex = 0;
}

SpriteRenderer::SpriteRenderer(std::shared_ptr<Sprite> sprite, int zIndex) {
    this->sprite = sprite;
    this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    this->zIndex = zIndex;
}

SpriteRenderer::SpriteRenderer(std::shared_ptr<Sprite> sprite, glm::vec4 color, int zIndex) {
    this->sprite = sprite;
    this->color = color;
    this->zIndex = zIndex;
}

void SpriteRenderer::update(float dt) {}

Sprite SpriteRenderer::getSprite() { return *sprite; }

glm::vec4 SpriteRenderer::getColor() { return color; }

int SpriteRenderer::getZIndex() { return zIndex; }
} // namespace eregion