#pragma once

#include "eregion/Entity/Entity.h"
#include "eregion/Entity/SpriteRenderer.h"
#include "eregion/Render/BatchRenderer.h"
#include <vector>

namespace eregion {

class Renderer {
  public:
    void render();
    void insertEntity(Entity entity);
    void insertSpriteRenderer(SpriteRenderer* spriteRenderer);

  private:
    std::vector<BatchRenderer> batchRenderers;
};
} // namespace eregion