#include "eregion/Entity/Transform.h"

using namespace eregion;

namespace eregion {

Transform::Transform(vec2* pos) {
    this->pos = pos;
    static vec2 defaultScale = {1.0f, 1.0f};
    this->scale = &defaultScale;
}

Transform::Transform(vec2* pos, vec2* scale) {
    this->pos = pos;
    this->scale = scale;
}

void Transform::update(float dt) {
    // TODO: This is the basis for a movement system, custom logic will go here.
}

vec2* Transform::getPos() { return pos; }

vec2* Transform::getScale() { return scale; }
} // namespace eregion