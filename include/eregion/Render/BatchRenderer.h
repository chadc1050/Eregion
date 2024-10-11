#pragma once

#include "eregion/Asset/AssetPool.h"
#include "eregion/Asset/Shader.h"
#include "eregion/Asset/Texture.h"
#include "eregion/Entity/SpriteRenderer.h"
#include "eregion/Entity/Transform.h"
#include "eregion/Render/ShaderProgram.h"
#include "eregion/Render/TextureProgram.h"

#include <array>
#include <unordered_map>
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
    float vertices[4 * VERTEX_SIZE * MAX_BATCH_SIZE] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top right
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f  // top left
    };

    int indices[6 * MAX_BATCH_SIZE] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // Sprites
    SpriteRenderer* sprites[MAX_BATCH_SIZE] = {};
    int nSprites = 0;

    // Textures
    std::unordered_map<std::string, TextureProgram*> textures;

    // IDs
    unsigned int vboId;
    unsigned int vaoId;
    unsigned int eboId;

    // Shader
    ShaderProgram* shader;

    void loadVertexProps(int index, SpriteRenderer* sprite, Transform* transform);
    int* genIndices();
    void loadElementIndices(int* elements, int index);
};
} // namespace eregion