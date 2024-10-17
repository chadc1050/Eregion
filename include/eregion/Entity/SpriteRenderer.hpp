#pragma once

#include "eregion/Entity/Component.hpp"
#include "eregion/Entity/Sprite.hpp"

#include <glm/glm.hpp>
#include <memory>

namespace eregion {
class SpriteRenderer : public Component {
  public:
    SpriteRenderer(std::shared_ptr<Sprite> sprite);
    SpriteRenderer(std::shared_ptr<Sprite> sprite, glm::vec4 color);
    SpriteRenderer(std::shared_ptr<Sprite> sprite, int zIndex);
    SpriteRenderer(std::shared_ptr<Sprite> sprite, glm::vec4 color, int zIndex);

    void update(float dt) override;

    Sprite getSprite();
    glm::vec4 getColor();
    int getZIndex();

  private:
    std::shared_ptr<Sprite> sprite;
    glm::vec4 color;
    int zIndex;
};
} // namespace eregion