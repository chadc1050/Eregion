#include "eregion/Render/Renderer.hpp"

using namespace eregion;

namespace eregion {

Renderer::Renderer(std::shared_ptr<Camera> camera) { this->camera = camera; }

void Renderer::render() {
    for (auto batch : spriteBatchRenderers) {
        batch->render();
    }
}

void Renderer::insertEntity(Entity entity) {
    debug("Adding entity to renderer.");

    // Get renderable component of entity
    std::optional<SpriteRenderer*> renderable = entity.getComponent<SpriteRenderer>();

    if (!renderable.has_value()) {
        debug("Entity is not renderable.");
        return;
    }

    // Get it's locale component
    std::optional<Transform*> transform = entity.getComponent<Transform>();

    insert(renderable.value(), transform.value());
}

void Renderer::insert(SpriteRenderer* spriteRenderer, Transform* transform) {
    bool added = false;
    for (auto batch : spriteBatchRenderers) {
        // TODO: And is correct batchrenderer
        if (batch->hasRoom() && batch->getZIndex() == spriteRenderer->getZIndex()) {
            batch->add(spriteRenderer, transform);
            added = true;
            break;
        }
    }

    if (!added) {
        debug("Creating a new batch renderer.");

        // TODO: And creates correct type based on renderable
        SpriteBatchRenderer* batchRenderer = new SpriteBatchRenderer(camera, spriteRenderer->getZIndex());
        batchRenderer->start();
        auto res = batchRenderer->add(spriteRenderer, transform);

        if (res.isError()) {
            error("Error");
        }

        // Insert the batch renderer such that it is sorted by it's z-index ascending
        auto idx = spriteBatchRenderers.begin();
        for (; idx != spriteBatchRenderers.end(); ++idx) {
            if ((*idx)->getZIndex() >= batchRenderer->getZIndex()) {
                break;
            }
        }

        spriteBatchRenderers.insert(idx, batchRenderer);
    }
}

Renderer::~Renderer() { warn("Terminated Renderer."); }

} // namespace eregion