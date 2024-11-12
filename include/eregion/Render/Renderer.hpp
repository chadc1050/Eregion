#pragma once

#include "eregion/Core/Camera.hpp"
#include "eregion/Core/Result.hpp"
#include "eregion/Entity/Entity.hpp"
#include "eregion/Entity/SpriteRenderer.hpp"
#include "eregion/Entity/Transform.hpp"
#include "eregion/Render/BatchRenderer.hpp"
#include "eregion/Render/Renderable.hpp"
#include "eregion/Render/SpriteBatchRenderer.hpp"

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

    std::vector<std::shared_ptr<BatchRenderer<Renderable>>> batchRenderers = {};

    void insert(std::shared_ptr<Renderable> renderable, Transform* transform);
};
} // namespace eregion