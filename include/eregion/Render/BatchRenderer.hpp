#pragma once

#include "eregion/Asset/AssetPool.hpp"
#include "eregion/Asset/Shader.hpp"
#include "eregion/Asset/Texture.hpp"
#include "eregion/Entity/SpriteRenderer.hpp"
#include "eregion/Entity/Transform.hpp"
#include "eregion/Render/ShaderProgram.hpp"
#include "eregion/Render/TextureProgram.hpp"

#include <array>
#include <unordered_map>
#include <utility>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace eregion {

class BatchRenderer {
  public:
    BatchRenderer();
    void render();
    void start();
    Result<void> add(SpriteRenderer* sprite, Transform* transform);
    bool hasRoom();
    ~BatchRenderer();

  private:
    // Maxiumum number of sprites in the pipeline
    static const int MAX_BATCH_SIZE = 1;

    // Attrib Size Consts
    static const unsigned int POS_SIZE = 2;
    static const unsigned int COLOR_SIZE = 4;
    static const unsigned int TEXTURE_COORDINATES_SIZE = 2;
    // TODO: Add this back later
    static const unsigned int TEXTURE_ID_SIZE = 0;

    // Vertex Size Consts
    static const unsigned int VERTEX_SIZE = POS_SIZE + COLOR_SIZE + TEXTURE_COORDINATES_SIZE + TEXTURE_ID_SIZE;
    static const unsigned int VERTEX_SIZE_BYTES = VERTEX_SIZE * sizeof(float);

    // Offset Consts
    static const unsigned int POS_OFFSET = 0;
    static const unsigned int COLOR_OFFSET = POS_OFFSET + POS_SIZE * sizeof(float);
    static const unsigned int TEXTURE_COORDINATES_OFFSET = COLOR_OFFSET + COLOR_SIZE * sizeof(float);
    // static const unsigned int TEXTURE_ID_OFFSET = TEXTURE_COORDINATES_OFFSET + TEXTURE_ID_SIZE * sizeof(float);

    // Vertices
    std::array<float, 4 * VERTEX_SIZE * MAX_BATCH_SIZE> vertices = {};

    std::array<int, 6 * MAX_BATCH_SIZE> indices = {};

    // Sprites + Transform
    std::array<std::pair<SpriteRenderer*, Transform*>, MAX_BATCH_SIZE> sprites = {};
    int nSprites = 0;

    // Textures
    std::unordered_map<std::string, TextureProgram*> textures;

    // IDs
    unsigned int vboId;
    unsigned int vaoId;
    unsigned int eboId;

    // Shader
    ShaderProgram* shader;

    void loadVertexProps(int index);
    void genIndices();
};
} // namespace eregion