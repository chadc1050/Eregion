#include "eregion/Render/Renderer.h"

using namespace eregion;

namespace eregion {
void Renderer::render() {
    for (BatchRenderer batch : batchRenderers) {
        batch.render();
    }
}

void Renderer::insertEntity(Entity entity) {
    for (Component* comp : entity.getComponents()) {
        if (SpriteRenderer* spriteRenderer = dynamic_cast<SpriteRenderer*>(comp)) {
            insertSpriteRenderer(spriteRenderer);
        }
    }
}

void Renderer::insertSpriteRenderer(SpriteRenderer* spriteRenderer) {
    bool added = false;
    for (BatchRenderer batch : batchRenderers) {
        if (batch.hasRoom()) {
            batch.add(spriteRenderer);
        }
    }

    if (!added) {
        debug("Creating a new batch renderer.");
        BatchRenderer batchRenderer = BatchRenderer();
        batchRenderer.init();
        batchRenderer.add(spriteRenderer);
        batchRenderers.push_back(batchRenderer);
    }
}
} // namespace eregion