#pragma once

#include "eregion/Asset/AssetPool.h"
#include "eregion/Asset/Shader.h"
#include "eregion/Asset/Texture.h"
#include "eregion/Entity/SpriteRenderer.h"
#include "eregion/Entity/Transform.h"
#include "eregion/Render/ShaderProgram.h"
#include "eregion/Render/TextureProgram.h"

#include <array>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <vector>

namespace eregion {

static const int MAX_BATCH_SIZE = 100;

class BatchRenderer {
  public:
    BatchRenderer();
    void render();
    void start();
    Result<void> add(SpriteRenderer* sprite, Transform* transform);
    bool hasRoom();

  private:
    std::vector<float> vertices;
    std::vector<SpriteRenderer*> sprites;
    std::unordered_map<std::string, TextureProgram*> textures;

    unsigned int vboId;
    unsigned int vaoId;
    unsigned int eboId;
    ShaderProgram* shader;

    void loadVertexProps(SpriteRenderer* sprite, Transform* transform);
    std::vector<int> genIndices();
    void loadElementIndices(std::vector<int>& elements, int index);
};

void checkOpenGLError(const char* function, const char* file, int line);
} // namespace eregion