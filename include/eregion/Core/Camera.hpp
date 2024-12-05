#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <array>

namespace eregion {

class Camera {
  public:
    Camera(glm::vec3 pos, float fov = 45.0f);
    void updatePos(glm::vec3 pos);
    void updateViewport(unsigned int width, unsigned int height);
    glm::mat4 getProj();
    glm::mat4 getView();
    glm::mat4 getCam();

  private:
    static constexpr glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
    static constexpr glm::vec3 DOWN = glm::vec3(0.0f, -1.0f, 0.0f);
    static constexpr glm::vec3 RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);
    static constexpr glm::vec3 LEFT = glm::vec3(-1.0f, 0.0f, 0.0f);

    glm::vec3 pos;
    glm::mat4 proj;
    glm::mat4 inverseProj;
    glm::mat4 view;
    glm::mat4 inverseView;
    float aspect;
    float fov;

    void updateView();
    void updateProj();
};
} // namespace eregion