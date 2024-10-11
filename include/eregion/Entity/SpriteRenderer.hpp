#pragma once

#include "eregion/Entity/Component.hpp"
#include "eregion/Entity/Sprite.hpp"

namespace eregion {
class SpriteRenderer : public Component {
  public:
    SpriteRenderer(Sprite sprite);

    void update(float dt) override;

    Sprite getSprite();

  private:
    Sprite sprite;
};
} // namespace eregion