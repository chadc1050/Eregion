#include "eregion/Core/Camera.hpp"

using namespace eregion;

namespace eregion {

/// @brief 2D Camera
/// @param pos Position of camera.
/// @param fov Field of view (in degrees).
Camera::Camera(glm::vec3 pos, float fov) {
    this->pos = pos;
    this->fov = fov;
    updateView();
    updateProj();
}

/// @brief Update camera position.
/// @param pos Position of camera.
void Camera::updatePos(glm::vec3 pos) {
    this->pos = pos;
    updateView();
}

void Camera::updateViewport(unsigned int width, unsigned int height) {
    aspect = (float)width / (float)height;
    updateProj();
}

void Camera::updateView() {
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    view = glm::lookAt(pos, pos + cameraFront, UP);

    inverseView = glm::inverse(view);
}

void Camera::updateProj() {
    proj = glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
    inverseProj = glm::inverse(proj);
}

glm::mat4 Camera::getProj() { return proj; }

glm::mat4 Camera::getView() { return view; }

glm::mat4 Camera::getCam() { return proj * view; }
} // namespace eregion