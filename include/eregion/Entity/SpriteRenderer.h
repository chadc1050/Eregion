#pragma once

#include "eregion/Entity/Component.h"
#include "eregion/Entity/Sprite.h"

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