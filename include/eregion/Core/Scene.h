#pragma once

#include "eregion/Asset/AssetPool.h"
#include "eregion/Core/Camera.h"
#include "eregion/Core/Result.h"
#include "eregion/Entity/Entity.h"
#include "eregion/Render/ShaderProgram.h"

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

    Result<void> init();
    void update(float dt);

  protected:
    Camera* camera;
    ShaderProgram* shader;
    std::vector<Entity> entities;
};
} // namespace eregion