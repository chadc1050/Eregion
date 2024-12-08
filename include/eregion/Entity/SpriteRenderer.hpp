#pragma once

#include "eregion/Asset/Sprite.hpp"
#include "eregion/Entity/Component.hpp"
#include "eregion/Render/Renderable.hpp"

#include <glm/glm.hpp>
#include <memory>

namespace eregion {

class SpriteRenderer {
  public:
    SpriteRenderer(std::shared_ptr<Sprite> sprite);
    SpriteRenderer(std::shared_ptr<Sprite> sprite, glm::vec4 color);
    SpriteRenderer(std::shared_ptr<Sprite> sprite, int zIndex);
    SpriteRenderer(std::shared_ptr<Sprite> sprite, glm::vec4 color, int zIndex);

    Sprite getSprite();
    glm::vec4 getColor();
    int getZIndex();

  private:
    std::shared_ptr<Sprite> sprite;
    glm::vec4 color;
    int zIndex;
};

COMPONENT(SpriteRenderer)
RENDERABLE(SpriteRenderer)
} // namespace eregion