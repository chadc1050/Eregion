#pragma once

#include "eregion/Entity/Entity.hpp"
#include "eregion/Entity/SpriteRenderer.hpp"
#include "eregion/Entity/Transform.hpp"
#include "eregion/Render/BatchRenderer.hpp"

#include <optional>
#include <vector>

namespace eregion {

class Renderer {
  public:
    Renderer();
    void render();
    void insertEntity(Entity entity);
    ~Renderer();

  private:
    std::vector<BatchRenderer*> batchRenderers = {};

    void insertSpriteRenderer(SpriteRenderer* spriteRenderer, Transform* transform);
};
} // namespace eregion