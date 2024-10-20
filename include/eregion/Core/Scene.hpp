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

#include <functional>
#include <memory>

namespace eregion {

enum LifeCycle {
    INIT,
    UPDATE,
};

class Scene {

  public:
    static Scene* create(Camera camera);

    /// @brief Function pointer to be used by Mechanism extensions
    using Mechanism = std::function<void(Scene*, const std::vector<Entity>&, float)>;

    Scene* mechanism(LifeCycle lifeCycle, Mechanism mechanism);

    void insertEntity(Entity entity);

    ~Scene();

  private:
    // Camera
    std::shared_ptr<Camera> camera;

    // Render
    Renderer* renderer;

    // ECS
    std::vector<Entity> entities;

    // Mechanisms
    std::vector<Mechanism> initMechanisms;
    std::vector<Mechanism> updateMechanisms;

    Scene(Camera camera);

    void init();
    void update(float dt);
    void draw();
    void viewportUpdate(unsigned int width, unsigned int height);

    friend class Window;
};

} // namespace eregion