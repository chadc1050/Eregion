#pragma once

#include "eregion/Entity/Component.hpp"
#include "eregion/Entity/Sprite.hpp"

#include <glm/glm.hpp>

namespace eregion {
class SpriteRenderer : public Component {
  public:
    SpriteRenderer(Sprite* sprite);
    SpriteRenderer(Sprite* sprite, glm::vec4 color);
    SpriteRenderer(Sprite* sprite, int zIndex);
    SpriteRenderer(Sprite* sprite, glm::vec4 color, int zIndex);

    void update(float dt) override;

    Sprite* getSprite();
    glm::vec4 getColor();
    int getZIndex();

  private:
    Sprite* sprite;
    glm::vec4 color;
    int zIndex;
};
} // namespace eregion