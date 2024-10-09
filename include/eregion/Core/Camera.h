#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <array>

namespace eregion {

class Camera {
  public:
    Camera(glm::vec2 pos);

  private:
    glm::vec2 pos;
    glm::mat4 proj;
    glm::mat4 inverseProj;
    glm::mat4 view;
    glm::mat4 inverseView;
};
} // namespace eregion