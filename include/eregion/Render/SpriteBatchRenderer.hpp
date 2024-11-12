#pragma once

#include "eregion/Asset/AssetPool.hpp"
#include "eregion/Asset/Shader.hpp"
#include "eregion/Asset/Texture.hpp"
#include "eregion/Core/Camera.hpp"
#include "eregion/Entity/SpriteRenderer.hpp"
#include "eregion/Entity/Transform.hpp"
#include "eregion/Render/BatchRenderer.hpp"
#include "eregion/Render/ShaderProgram.hpp"

#include <array>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace eregion {

class SpriteBatchRenderer : public BatchRenderer<SpriteRenderer> {
  public:
    SpriteBatchRenderer(std::shared_ptr<Camera> camera, int zIndex);

    void start() override;

    void render() override;

    Result<void> add(std::shared_ptr<SpriteRenderer> sprite, Transform* transform);

    bool hasRoom() override;

    ~SpriteBatchRenderer();

  private:
    // Maxiumum number of sprites in the pipeline
    static const int MAX_BATCH_SIZE = 5;

    // Attrib Size Consts
    static const unsigned int POS_SIZE = 2;
    static const unsigned int POS_SIZE_BYTES = POS_SIZE * sizeof(float);

    static const unsigned int COLOR_SIZE = 4;
    static const unsigned int COLOR_SIZE_BYTES = COLOR_SIZE * sizeof(float);

    static const unsigned int TEXTURE_COORDINATES_SIZE = 2;
    static const unsigned int TEXTURE_COORDINATES_SIZE_BYTES = TEXTURE_COORDINATES_SIZE * sizeof(float);

    static const unsigned int TEXTURE_ID_SIZE = 1;
    static const unsigned int TEXTURE_ID_SIZE_BYTES = TEXTURE_ID_SIZE * sizeof(float);

    // Vertex Size Consts
    static const unsigned int N_VERTICES = 4;
    static const unsigned int VERTEX_SIZE = POS_SIZE + COLOR_SIZE + TEXTURE_COORDINATES_SIZE + TEXTURE_ID_SIZE;
    static const unsigned int VERTEX_SIZE_BYTES = VERTEX_SIZE * sizeof(float);

    // Offset Consts
    static const unsigned int POS_OFFSET = 0;
    static const unsigned int COLOR_OFFSET = POS_OFFSET + POS_SIZE_BYTES;
    static const unsigned int TEXTURE_COORDINATES_OFFSET = COLOR_OFFSET + COLOR_SIZE_BYTES;
    static const unsigned int TEXTURE_ID_OFFSET = TEXTURE_COORDINATES_OFFSET + TEXTURE_COORDINATES_SIZE_BYTES;

    static const unsigned int N_INDICES = 6;

    std::shared_ptr<Camera> camera;

    // Vertices
    std::array<float, N_VERTICES * VERTEX_SIZE * MAX_BATCH_SIZE> vertices = {};

    std::array<int, N_INDICES * MAX_BATCH_SIZE> indices = {};

    // Sprites + Transform
    std::array<std::pair<std::shared_ptr<SpriteRenderer>, Transform*>, MAX_BATCH_SIZE> sprites = {};
    int nSprites = 0;

    // Textures
    int textureSlots[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    std::vector<Texture*> textures = {};

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