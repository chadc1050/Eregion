#pragma once

#include "eregion/Core/Camera.hpp"
#include "eregion/Core/Result.hpp"
#include "eregion/Entity/Entity.hpp"
#include "eregion/Entity/SpriteRenderer.hpp"
#include "eregion/Entity/TextRenderer.hpp"
#include "eregion/Entity/Transform.hpp"
#include "eregion/Render/Renderable.hpp"
#include "eregion/Render/SpriteBatchRenderer.hpp"
#include "eregion/Render/TextBatchRenderer.hpp"

#include <algorithm>
#include <any>
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

    std::vector<SpriteBatchRenderer*> spriteBatchRenderers = {};
    std::vector<TextBatchRenderer*> textBatchRenderers = {};

    void insert(SpriteRenderer* spriteRenderer, Transform* transform);
    void insert(TextRenderer* textRenderer, Transform* transform);
};
} // namespace eregion