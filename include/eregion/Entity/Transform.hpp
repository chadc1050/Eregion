#pragma once

#include "eregion/Entity/Component.hpp"

#include <glm/glm.hpp>

namespace eregion {

class Transform {
  public:
    Transform();
    Transform(glm::vec2 pos);
    Transform(glm::vec2 pos, glm::vec2 scale);

    glm::vec2 getPos();
    glm::vec2 getScale();

  private:
    glm::vec2 pos;
    glm::vec2 scale;
};

COMPONENT(Transform)
} // namespace eregion