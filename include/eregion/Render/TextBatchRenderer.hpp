#pragma once

#include "eregion/Asset/AssetPool.hpp"
#include "eregion/Asset/Shader.hpp"
#include "eregion/Asset/Texture.hpp"
#include "eregion/Core/Camera.hpp"
#include "eregion/Entity/TextRenderer.hpp"
#include "eregion/Entity/Transform.hpp"
#include "eregion/Render/ShaderProgram.hpp"

#include <array>
#include <memory>
#include <utility>

namespace eregion {

class TextBatchRenderer {
  public:
    TextBatchRenderer(std::shared_ptr<Camera> camera, int zIndex);

    void start();

    void render();

    Result<void> add(TextRenderer* renderable, Transform* transform);

    bool hasRoom();

    int getZIndex();

    // Comparision operators for determining draw order
    bool operator<(const TextBatchRenderer& other) const { return zIndex < other.zIndex; }
    bool operator>(const TextBatchRenderer& other) const { return zIndex > other.zIndex; }
    bool operator<=(const TextBatchRenderer& other) const { return zIndex <= other.zIndex; }
    bool operator>=(const TextBatchRenderer& other) const { return zIndex >= other.zIndex; }
    bool operator==(const TextBatchRenderer& other) const { return zIndex == other.zIndex; }

    ~TextBatchRenderer();

  private:
    // Maxiumum number of text strings in the pipeline
    static const int MAX_BATCH_SIZE = 1;

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

    // IDs
    unsigned int vboId;
    unsigned int vaoId;
    unsigned int eboId;

    // Shader
    ShaderProgram* shader;

    // Vertices
    std::vector<float> vertices = {};

    std::array<int, MAX_BATCH_SIZE> vertexIndices = {};

    std::vector<int> indices = {};

    // Text + Transform
    std::array<std::pair<TextRenderer*, Transform*>, MAX_BATCH_SIZE> text = {};
    int nText = 0;
    int nChars = 0;

    // Textures
    int textureSlots[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    std::vector<Texture*> textures = {};

    int zIndex;

    void loadVertexProps(int index, bool isRebuffer);
    void genIndices();
    void rebuffer(std::string content, int offset);
};
} // namespace eregion