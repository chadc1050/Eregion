#include "eregion/Entity/Transform.h"

using namespace eregion;

namespace eregion {

Transform::Transform(glm::vec2* pos) {
    this->pos = pos;
    static glm::vec2 defaultScale = glm::vec2(1.0f, 1.0f);
    this->scale = &defaultScale;
}

Transform::Transform(glm::vec2* pos, glm::vec2* scale) {
    this->pos = pos;
    this->scale = scale;
}

void Transform::update(float dt) {
    // TODO: This is the basis for a movement system, custom logic will go here.
}

glm::vec2* Transform::getPos() { return pos; }

glm::vec2* Transform::getScale() { return scale; }
} // namespace eregion