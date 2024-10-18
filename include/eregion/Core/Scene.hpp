#pragma once

#include "eregion/Asset/AssetPool.hpp"
#include "eregion/Asset/SpriteSheet.hpp"
#include "eregion/Core/Camera.hpp"
#include "eregion/Core/Result.hpp"
#include "eregion/Entity/Entity.hpp"
#include "eregion/Render/Renderer.hpp"
#include "eregion/Render/ShaderProgram.hpp"

#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <memory>

namespace eregion {

class Scene {

  public:
    Scene(Camera camera);

    // Virtual methods to customize scene behavior
    virtual void init() = 0;

    void update(float dt);
    void draw();

    void insertEntity(Entity entity);
    void save();
    void viewportUpdate(unsigned int width, unsigned int height);

    virtual ~Scene();

  private:
    std::shared_ptr<Camera> camera;
    Renderer* renderer;
    std::vector<Entity> entities;
};
} // namespace eregion