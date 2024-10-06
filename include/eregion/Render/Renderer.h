#pragma once

#include "eregion/Entity/Entity.h"
#include "eregion/Entity/SpriteRenderer.h"
#include "eregion/Entity/Transform.h"
#include "eregion/Render/BatchRenderer.h"

#include <optional>
#include <vector>

namespace eregion {

class Renderer {
  public:
    Renderer();

    void render();
    void insertEntity(Entity entity);

  private:
    std::vector<BatchRenderer> batchRenderers;

    void insertSpriteRenderer(SpriteRenderer* spriteRenderer, Transform* transform);
};
} // namespace eregion