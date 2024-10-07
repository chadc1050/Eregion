#include "eregion/Core/Camera.h"

using namespace eregion;

namespace eregion {

Camera::Camera(std::array<float, 2> pos) {
    this->pos = pos;

    // Create identity matrices
    mat4x4_identity(proj);
    mat4x4_identity(inverseProj);
    mat4x4_identity(view);
    mat4x4_identity(inverseView);

    // Normalize projection matrix
    // TODO: Should be configurable
    mat4x4_ortho(proj, 0.0f, 32.0f * 40.0f, 0.0f, 32.0f * 21.0f, 0.0f, 100.0f);

    mat4x4_invert(inverseProj, proj);
}
} // namespace eregion