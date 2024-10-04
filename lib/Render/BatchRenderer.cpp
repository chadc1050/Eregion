#include "eregion/Render/BatchRenderer.h"

using namespace eregion;

namespace eregion {
BatchRenderer::BatchRenderer() {}
void BatchRenderer::render() {}
void BatchRenderer::init() {}
Result<void> BatchRenderer::add(SpriteRenderer* sprite) {

    Texture* texture = sprite->getSprite().texture;

    int idx = sprites.size() - 1;

    sprites[idx] = sprite;

    // Compile texture if needed
    if (!textures.contains(texture->name)) {
        auto res = TextureProgram::compile(texture);

        if (res.isError()) {
            return Result<void>(Error{"Error compiling texture."});
        }

        textures[texture->name] = res.getValue();
    }

    return Result<void>();
}
bool BatchRenderer::hasRoom() { return sprites.size() < MAX_BATCH_SIZE; }
} // namespace eregion