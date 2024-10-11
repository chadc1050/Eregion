#pragma once

#include "eregion/Entity/Component.hpp"
#include "eregion/Entity/Sprite.hpp"

#include <glm/glm.hpp>

namespace eregion {
class SpriteRenderer : public Component {
  public:
    SpriteRenderer(Sprite sprite);
    SpriteRenderer(Sprite sprite, glm::vec4 color);

    void update(float dt) override;

    Sprite getSprite();
    glm::vec4 getColor();

  private:
    Sprite sprite;
    glm::vec4 color;
};
} // namespace eregion