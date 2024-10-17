#include "eregion/Render/Renderer.hpp"

using namespace eregion;

namespace eregion {

Renderer::Renderer(std::shared_ptr<Camera> camera) { this->camera = camera; }

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
        if (batch->hasRoom() && batch->getZIndex() == spriteRenderer->getZIndex()) {
            batch->add(spriteRenderer, transform);
            added = true;
            break;
        }
    }

    if (!added) {
        debug("Creating a new batch renderer.");
        BatchRenderer* batchRenderer = new BatchRenderer(camera, spriteRenderer->getZIndex());
        batchRenderer->start();
        auto res = batchRenderer->add(spriteRenderer, transform);

        if (res.isError()) {
            error("Error");
        }

        // Insert the batch renderer such that it is sorted by it's z-index ascending
        auto idx = std::lower_bound(batchRenderers.begin(), batchRenderers.end(), batchRenderer,
                                    [](BatchRenderer* a, BatchRenderer* b) { return *a < *b; });

        batchRenderers.insert(idx, batchRenderer);
    }
}

Renderer::~Renderer() {

    for (BatchRenderer* batchRenderer : batchRenderers) {
        delete batchRenderer;
    }

    batchRenderers.clear();

    warn("Terminated Renderer.");
}

} // namespace eregion