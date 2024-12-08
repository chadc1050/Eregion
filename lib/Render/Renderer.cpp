#include "eregion/Render/Renderer.hpp"

using namespace eregion;

namespace eregion {

Renderer::Renderer(std::shared_ptr<Camera> camera) { this->camera = camera; }

void Renderer::render() {
    for (auto batch : spriteBatchRenderers) {
        batch->render();
    }

    for (auto batch : textBatchRenderers) {
        batch->render();
    }
}

void Renderer::insertEntity(Entity* entity) {
    debug("Adding entity to renderer.");

    // Get it's locale component
    std::optional<Transform*> transform = entity->getComponent<Transform>();

    if (!transform.has_value()) {
        debug("Entity does not have transform, thus it is not renderable.");
        return;
    }

    // Check for SpriteRenderer
    std::optional<SpriteRenderer*> spriteRenderer = entity->getComponent<SpriteRenderer>();

    if (spriteRenderer.has_value()) {
        insert(spriteRenderer.value(), transform.value());
        return;
    }

    // Check for TextRenderer
    std::optional<TextRenderer*> textRenderer = entity->getComponent<TextRenderer>();

    if (textRenderer.has_value()) {
        insert(textRenderer.value(), transform.value());
        return;
    }

    // No renderable component
    debug("Entity does not have a renderable component.");
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

void Renderer::insert(TextRenderer* textRenderer, Transform* transform) {
    bool added = false;
    for (auto batch : textBatchRenderers) {
        // TODO: And is correct batchrenderer
        if (batch->hasRoom() && batch->getZIndex() == textRenderer->getZIndex()) {
            batch->add(textRenderer, transform);
            added = true;
            break;
        }
    }

    if (!added) {
        debug("Creating a new batch renderer.");

        // TODO: And creates correct type based on renderable
        TextBatchRenderer* batchRenderer = new TextBatchRenderer(camera, textRenderer->getZIndex());
        batchRenderer->start();
        auto res = batchRenderer->add(textRenderer, transform);

        if (res.isError()) {
            error("Error");
        }

        // Insert the batch renderer such that it is sorted by it's z-index ascending
        auto idx = textBatchRenderers.begin();
        for (; idx != textBatchRenderers.end(); ++idx) {
            if ((*idx)->getZIndex() >= batchRenderer->getZIndex()) {
                break;
            }
        }

        textBatchRenderers.insert(idx, batchRenderer);
    }
}

Renderer::~Renderer() { warn("Terminated Renderer."); }

} // namespace eregion