#include "eregion/Render/BatchRenderer.h"

using namespace eregion;

namespace eregion {

BatchRenderer::BatchRenderer() {

    Shader vert = AssetPool::getShader("../assets/shaders/texture.vert").getValue();

    Shader frag = AssetPool::getShader("../assets/shaders/texture.frag").getValue();

    shader = ShaderProgram::compile(vert, frag).getValue();
}

void BatchRenderer::render() {

    TextureProgram* texture = textures["wall.jpg"];

    glBindTexture(GL_TEXTURE_2D, texture->getTextureId());

    // render container
    shader->bind();
    glBindVertexArray(vaoId);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void BatchRenderer::start() {

    debug("Starting batch renderer.");

    glGenVertexArrays(1, &vaoId);
    glGenBuffers(1, &vboId);
    glGenBuffers(1, &eboId);

    glBindVertexArray(vaoId);

    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

Result<void> BatchRenderer::add(SpriteRenderer* sprite, Transform* transform) {

    int index = nSprites;
    sprites[nSprites] = sprite;
    nSprites++;

    // Compile texture if needed
    Texture* texture = sprite->getSprite().texture;
    if (!textures.contains(texture->name)) {
        auto res = TextureProgram::compile(texture);

        if (res.isError()) {
            return Result<void>(Error{"Error compiling texture."});
        }

        textures[texture->name] = res.getValue();
    }

    // loadVertexProps(index, sprite, transform);

    return Result<void>();
}

BatchRenderer::~BatchRenderer() {
    warn("Destroying batch renderer.");
    glDeleteVertexArrays(1, &vaoId);
    glDeleteBuffers(1, &vboId);
    glDeleteBuffers(1, &eboId);
}

void BatchRenderer::loadVertexProps(int index, SpriteRenderer* sprite, Transform* transform) {

    // TODO: Offset will increase based on index of sprite if more are added.
    int offset = index * VERTEX_SIZE;

    // TODO: May want this to be configurable
    glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};

    glm::vec2* texCoords = sprite->getSprite().getTextureCoords();

    // TODO: As more than one textures are added this will need to be incremented and stored.
    int texId = textures["wall.jpg"]->getTextureId();

    // Add vertices with the appropriate properties
    float xAdd = 0.5f;
    float yAdd = 0.5f;

    glm::vec2 pos = *transform->getPos();
    glm::vec2 scale = *transform->getScale();

    for (int i = 0; i < 4; i++) {
        if (i == 1) {
            yAdd = -0.5f;
        } else if (i == 2) {
            xAdd = -0.5f;
        } else if (i == 3) {
            yAdd = 0.5f;
        }

        // Load position
        vertices[offset] = pos.x + (xAdd * scale.y);
        vertices[offset + 1] = pos.y + (yAdd * scale.y);

        // Load Color
        vertices[offset + 2] = color.x;
        vertices[offset + 3] = color.y;
        vertices[offset + 4] = color.z;
        vertices[offset + 5] = color.w;

        // Load Texture Coordinates
        vertices[offset + 6] = texCoords[i].x;
        vertices[offset + 7] = texCoords[i].y;

        // Load Texture ID
        // vertices[offset + 8] = texId;

        offset += VERTEX_SIZE;
    }
}

int* BatchRenderer::genIndices() {
    // Six indices per quad, three per triangle
    int elements[6 * MAX_BATCH_SIZE];
    for (int i = 0; i < MAX_BATCH_SIZE; i++) {
        loadElementIndices(elements, i);
    }

    return new int[]{3, 2, 0, 0, 2, 1};
}

void BatchRenderer::loadElementIndices(int* elements, int index) {
    int offsetArrayIndex = 6 * index;
    int offset = 4 * index;

    // Triangle 1
    elements[offsetArrayIndex] = offset + 3;
    elements[offsetArrayIndex + 1] = offset + 2;
    elements[offsetArrayIndex + 2] = offset;

    // Triangle 2
    elements[offsetArrayIndex + 3] = offset;
    elements[offsetArrayIndex + 4] = offset + 2;
    elements[offsetArrayIndex + 5] = offset + 1;
}

bool BatchRenderer::hasRoom() { return nSprites <= MAX_BATCH_SIZE; }
} // namespace eregion