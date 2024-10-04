#pragma once

#include "eregion/Asset/Texture.h"
#include "eregion/Entity/SpriteRenderer.h"
#include "eregion/Render/TextureProgram.h"

#include <unordered_map>
#include <vector>

namespace eregion {

static const int MAX_BATCH_SIZE = 100;

class BatchRenderer {
  public:
    BatchRenderer();
    void render();
    void init();
    Result<void> add(SpriteRenderer* sprite);
    bool hasRoom();

  private:
    std::vector<SpriteRenderer*> sprites;
    std::unordered_map<std::string, TextureProgram*> textures;
};
} // namespace eregion