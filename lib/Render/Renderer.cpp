#include "eregion/Render/Renderer.hpp"

using namespace eregion;

namespace eregion {

Renderer::Renderer(std::shared_ptr<Camera> camera) { this->camera = camera; }

void Renderer::render() {
    for (auto batch : batchRenderers) {
        batch->render();
    }
}

void Renderer::insertEntity(Entity entity) {
    debug("Adding entity to renderer.");

    // Get renderable component of entity
    std::optional<Renderable*> renderable = entity.getRenderComponent();

    if (!renderable.has_value()) {
        debug("Entity is not renderable.");
        return;
    }

    // Get it's locale component
    std::optional<Transform*> transform = entity.getComponent<Transform>();

    insert(std::shared_ptr<Renderable>(renderable.value()), transform.value());
}

void Renderer::insert(std::shared_ptr<Renderable> renderable, Transform* transform) {
    bool added = false;
    for (auto batch : batchRenderers) {
        // TODO: And is correct batchrenderer
        if (batch->hasRoom() && batch->getZIndex() == renderable->getZIndex()) {
            batch->add(renderable, transform);
            added = true;
            break;
        }
    }

    if (!added) {
        debug("Creating a new batch renderer.");

        // TODO: And creates correct type based on renderable
        auto batchRenderer = std::make_shared<SpriteBatchRenderer>(camera, renderable->getZIndex());
        batchRenderer->start();
        auto res = batchRenderer->add(std::static_pointer_cast<SpriteRenderer>(renderable), transform);

        if (res.isError()) {
            error("Error");
        }

        // Insert the batch renderer such that it is sorted by it's z-index ascending
        auto idx = batchRenderers.begin();
        for (; idx != batchRenderers.end(); ++idx) {
            if ((*idx)->getZIndex() >= batchRenderer->getZIndex()) {
                break;
            }
        }

        batchRenderers.insert(idx, std::dynamic_pointer_cast<BatchRenderer<Renderable>>(batchRenderer));
    }
}

Renderer::~Renderer() { warn("Terminated Renderer."); }

} // namespace eregion