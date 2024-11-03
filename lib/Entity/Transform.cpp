#include "eregion/Entity/Transform.hpp"

using namespace eregion;

namespace eregion {

Transform::Transform() {
    this->pos = glm::vec2(0.0f, 0.0f);
    this->scale = glm::vec2(1.0f, 1.0f);
}

Transform::Transform(glm::vec2 pos) {
    this->pos = pos;
    this->scale = glm::vec2(1.0f, 1.0f);
}

Transform::Transform(glm::vec2 pos, glm::vec2 scale) {
    this->pos = pos;
    this->scale = scale;
}

glm::vec2 Transform::getPos() { return pos; }

glm::vec2 Transform::getScale() { return scale; }
} // namespace eregion