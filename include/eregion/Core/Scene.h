#pragma once

#include "eregion/Core/Camera.h"
#include "eregion/Entity/Entity.h"

#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "linmath.h"

namespace eregion {

class Scene {

  public:
    Scene();
    Scene(Camera* camera);
    ~Scene();

    void init();
    void update(float dt);

  protected:
    Camera* camera;
    std::vector<Entity> entities;
};
} // namespace eregion