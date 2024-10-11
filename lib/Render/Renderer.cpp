#include "eregion/Render/Renderer.hpp"

using namespace eregion;

namespace eregion {

Renderer::Renderer() {}

void Renderer::render() {
    for (BatchRenderer* batch : batchRenderers) {
        batch->render();
    }
}

void Renderer::insertEntity(Entity entity) {
    debug("Adding entity to renderer.");

    // TODO: Handle bad entity case.
    std::optional<SpriteRenderer*> spriteRenderer = entity.getComponent<SpriteRenderer>();
    std::optional<Transform*> transform = entity.getComponent<Transform>();

    insertSpriteRenderer(spriteRenderer.value(), transform.value());
}

void Renderer::insertSpriteRenderer(SpriteRenderer* spriteRenderer, Transform* transform) {
    bool added = false;
    for (BatchRenderer* batch : batchRenderers) {
        if (batch->hasRoom()) {
            batch->add(spriteRenderer, transform);
        }
    }

    if (!added) {
        debug("Creating a new batch renderer.");
        BatchRenderer* batchRenderer = new BatchRenderer();
        batchRenderer->start();
        auto res = batchRenderer->add(spriteRenderer, transform);

        if (res.isError()) {
            error("Error");
        }

        batchRenderers.push_back(batchRenderer);
    }
}

Renderer::~Renderer() {

    for (BatchRenderer* batchRenderer : batchRenderers) {
        delete batchRenderer;
    }

    warn("Terminated Renderer.");
}

} // namespace eregion