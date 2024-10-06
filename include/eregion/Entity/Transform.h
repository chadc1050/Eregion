#pragma once

#include "eregion/Entity/Component.h"

#include "linmath.h"

namespace eregion {
class Transform : public Component {
  public:
    Transform(vec2* pos);
    Transform(vec2* pos, vec2* scale);
    void update(float dt) override;

    vec2* getPos();
    vec2* getScale();

  private:
    vec2* pos;
    vec2* scale;
};
} // namespace eregion