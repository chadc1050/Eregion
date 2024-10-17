#include "eregion/Render/BatchRenderer.hpp"

using namespace eregion;

namespace eregion {

BatchRenderer::BatchRenderer(std::shared_ptr<Camera> camera, int zIndex) {

    this->camera = camera;

    this->zIndex = zIndex;

    Shader vert = AssetPool::getShader("../assets/shaders/texture.vert").getValue();

    Shader frag = AssetPool::getShader("../assets/shaders/texture.frag").getValue();

    shader = ShaderProgram::compile(vert, frag).getValue();
}

void BatchRenderer::render() {

    // FIXME: This is causing a null pointer issue with the texture, will need to fix that before rebuffering can
    // happen.
    // TODO: This is where we could check to see if the sprite has been declared dirty, or if transform has changed
    // for (int i = 0; i < nSprites; i++) {
    //     loadVertexProps(i);
    // }

    // // Always rebuffering until deltas are available!
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_DYNAMIC_DRAW);

    shader->bind();

    // Upload texture slots
    int textureSlots[8] = {0, 1, 2, 3, 4, 5, 6, 7};

    size_t size = sizeof(textures.size()) / sizeof(int);

    auto samplerRes = shader->uploadIntArray("uTextures", textureSlots, size);

    if (samplerRes.isError()) {
        error("Error uploading texture slots to shader.");
    }

    // Upload textures to texture slots
    int count = 0;
    for (const auto& texture : textures) {

        glActiveTexture(GL_TEXTURE0 + count);

        texture.second->bind();

        auto idxRes = shader->uploadInt(("uTextures[" + std::to_string(count) + "]").c_str(), count);

        if (idxRes.isError()) {
            error("Error uploading index to texture slots.");
        }

        count = count + 1;
    }

    // Upload camera matrix
    glm::mat4 cam = camera->getCam();

    auto camRes = shader->uploadMat4("uCam", cam);

    if (camRes.isError()) {
        error("Error uploading camera to shader.");
    }

    glBindVertexArray(vaoId);

    // Draw
    glDrawElements(GL_TRIANGLES, nSprites * N_INDICES, GL_UNSIGNED_INT, 0);

    // Clean up
    glBindVertexArray(0);

    for (const auto& texture : textures) {
        texture.second->unbind();
    }

    shader->unbind();
}

void BatchRenderer::start() {

    debug("Starting batch renderer.");

    // VAO
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    // VBO
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_DYNAMIC_DRAW);

    // EBO
    genIndices();
    glGenBuffers(1, &eboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, POS_SIZE, GL_FLOAT, false, VERTEX_SIZE_BYTES, (void*)POS_OFFSET);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, COLOR_SIZE, GL_FLOAT, false, VERTEX_SIZE_BYTES, (void*)COLOR_OFFSET);
    glEnableVertexAttribArray(1);

    // Texture Coord
    glVertexAttribPointer(2, TEXTURE_COORDINATES_SIZE, GL_FLOAT, false, VERTEX_SIZE_BYTES,
                          (void*)TEXTURE_COORDINATES_OFFSET);
    glEnableVertexAttribArray(2);

    // Texture ID
    glVertexAttribPointer(3, TEXTURE_ID_SIZE, GL_FLOAT, false, VERTEX_SIZE_BYTES, (void*)TEXTURE_ID_OFFSET);
    glEnableVertexAttribArray(3);
}

Result<void> BatchRenderer::add(SpriteRenderer* sprite, Transform* transform) {

    int index = nSprites;
    sprites[nSprites] = std::make_pair(sprite, transform);
    nSprites++;

    // Compile texture if needed
    Texture* texture = sprite->getSprite()->getTexture();
    std::string name = texture->getName();
    if (!textures.contains(name)) {
        textures[name] = texture;
    }

    loadVertexProps(index);

    return Result<void>();
}

BatchRenderer::~BatchRenderer() {
    warn("Destroying batch renderer.");
    glDeleteVertexArrays(1, &vaoId);
    glDeleteBuffers(1, &vboId);
    glDeleteBuffers(1, &eboId);

    delete shader;
}

void BatchRenderer::loadVertexProps(int index) {

    int offset = index * VERTEX_SIZE * N_VERTICES;

    std::pair<SpriteRenderer*, Transform*> entity = sprites.at(index);

    SpriteRenderer* spriteRenderer = entity.first;

    Sprite* sprite = spriteRenderer->getSprite();

    std::array<glm::vec2, 4> texCoords = sprite->getTextureCoords();

    glm::vec4 color = spriteRenderer->getColor();

    Texture* texture = sprite->getTexture();

    int texId = texture->getTextureId();

    // Add vertices with the appropriate properties
    float xAdd = 0.5f;
    float yAdd = 0.5f;

    Transform* transform = entity.second;
    glm::vec2 pos = transform->getPos();
    glm::vec2 scale = transform->getScale();

    for (unsigned int i = 0; i < N_VERTICES; i++) {

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
        vertices[offset + 8] = texId;

        offset += VERTEX_SIZE;
    }
}

void BatchRenderer::genIndices() {
    // Six indices per quad, three per triangle
    for (int i = 0; i < MAX_BATCH_SIZE; i++) {

        int offsetArrayIndex = N_INDICES * i;
        int offset = N_VERTICES * i;

        // Triangle 1
        indices[offsetArrayIndex] = offset;
        indices[offsetArrayIndex + 1] = offset + 1;
        indices[offsetArrayIndex + 2] = offset + 3;

        // Triangle 2
        indices[offsetArrayIndex + 3] = offset + 1;
        indices[offsetArrayIndex + 4] = offset + 2;
        indices[offsetArrayIndex + 5] = offset + 3;
    }
}

bool BatchRenderer::hasRoom() { return nSprites < MAX_BATCH_SIZE; }

int BatchRenderer::getZIndex() { return zIndex; }
} // namespace eregion