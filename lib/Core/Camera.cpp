#include "eregion/Core/Camera.hpp"

using namespace eregion;

namespace eregion {

Camera::Camera(glm::vec2 pos) {
    this->pos = pos;

    // Create identity matrices
    inverseProj = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    inverseView = glm::mat4(1.0f);

    // Normalize projection matrix
    // TODO: Should be configurable
    proj = glm::ortho(0.0f, 32.0f * 40.0f, 0.0f, 32.0f * 21.0f, 0.0f, 100.0f);
    inverseProj = glm::inverse(proj);
}
} // namespace eregion