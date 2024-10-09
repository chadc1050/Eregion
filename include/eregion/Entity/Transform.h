#pragma once

#include "eregion/Entity/Component.h"

#include <glm/glm.hpp>

namespace eregion {
class Transform : public Component {
  public:
    Transform(glm::vec2* pos);
    Transform(glm::vec2* pos, glm::vec2* scale);
    void update(float dt) override;

    glm::vec2* getPos();
    glm::vec2* getScale();

  private:
    glm::vec2* pos;
    glm::vec2* scale;
};
} // namespace eregion