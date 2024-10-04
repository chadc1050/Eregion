#include "eregion/Entity/SpriteRenderer.h"

using namespace eregion;

namespace eregion {
SpriteRenderer::SpriteRenderer(Sprite sprite) : sprite(sprite) {}
void SpriteRenderer::update(float dt) {}
Sprite SpriteRenderer::getSprite() { return sprite; }
} // namespace eregion