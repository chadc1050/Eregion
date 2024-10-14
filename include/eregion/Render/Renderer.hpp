#pragma once

#include "eregion/Core/Camera.hpp"
#include "eregion/Entity/Entity.hpp"
#include "eregion/Entity/SpriteRenderer.hpp"
#include "eregion/Entity/Transform.hpp"
#include "eregion/Render/BatchRenderer.hpp"

#include <memory>
#include <optional>
#include <vector>

namespace eregion {

class Renderer {
  public:
    Renderer(std::shared_ptr<Camera> camera);
    void render();
    void insertEntity(Entity entity);
    ~Renderer();

  private:
    std::shared_ptr<Camera> camera;
    std::vector<BatchRenderer*> batchRenderers = {};

    void insertSpriteRenderer(SpriteRenderer* spriteRenderer, Transform* transform);
};
} // namespace eregion