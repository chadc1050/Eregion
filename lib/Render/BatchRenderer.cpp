#include "eregion/Render/BatchRenderer.h"

using namespace eregion;

namespace eregion {

BatchRenderer::BatchRenderer() {

    Shader vert = AssetPool::getShader("../assets/shaders/texture.vert").getValue();

    Shader frag = AssetPool::getShader("../assets/shaders/texture.frag").getValue();

    shader = ShaderProgram::compile(vert, frag).getValue();
}

void BatchRenderer::render() {

    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferSubData(GL_ARRAY_BUFFER, 0, MAX_BATCH_SIZE * VERTEX_SIZE * sizeof(float), vertices);

    shader->bind();

    //////// This is all temportary until the Camera values can be properly passed.
    mat4x4 proj;
    mat4x4_identity(proj);

    // Create an identity matrix
    mat4x4_identity(proj);

    // Normalize projection matrix
    // TODO: Should be configurable
    mat4x4_ortho(proj, 0.0f, 32.0f * 40.0f, 0.0f, 32.0f * 21.0f, 0.0f, 100.0f);

    mat4x4 view;
    mat4x4_identity(view);
    vec3 camUp = {0.0f, 1.0f, 0.0f};

    vec3 eye = {0.0f, 0.0f, 20.0f};

    vec3 center = {0.0f, 0.0f, -1.0f};

    mat4x4_look_at(view, eye, center, camUp);

    mat4x4 inverseView;
    mat4x4_identity(inverseView);

    mat4x4_invert(view, inverseView);
    ////////////

    shader->uploadMat4("uProjection", &proj);
    shader->uploadMat4("uView", &view);

    glActiveTexture(GL_TEXTURE0);
    textures["crafting.png"]->bind();

    int textureSlots[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    size_t size = sizeof(textureSlots) / sizeof(textureSlots[0]);
    shader->uploadIntArray("uTextures", textureSlots, size);

    glBindVertexArray(vaoId);

    // TODO: Look these up first
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // std::this_thread::sleep_for(std::chrono::seconds(30));

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);

    textures["crafting.png"]->unbind();

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
    glBufferData(GL_ARRAY_BUFFER, MAX_BATCH_SIZE * VERTEX_SIZE * sizeof(float), vertices, GL_DYNAMIC_DRAW);

    // EBO
    glGenBuffers(1, &eboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);

    // Create and upload indices buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * MAX_BATCH_SIZE * sizeof(int), genIndices(), GL_STATIC_DRAW);

    // Enable Attributes
    // Position
    int aPosLocation = glGetAttribLocation(shader->getProgramId(), "aPos");
    glVertexAttribPointer(aPosLocation, POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (void*)POS_OFFSET);
    glEnableVertexAttribArray(aPosLocation);

    // Color
    int aColorLocation = glGetAttribLocation(shader->getProgramId(), "aColor");
    glVertexAttribPointer(aColorLocation, COLOR_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (void*)COLOR_OFFSET);
    glEnableVertexAttribArray(aColorLocation);

    // Texture Coords
    int aTexCoords = glGetAttribLocation(shader->getProgramId(), "aTexCoords");
    glVertexAttribPointer(aTexCoords, TEXTURE_COORDINATES_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES,
                          (void*)TEXTURE_COORDINATES_OFFSET);
    glEnableVertexAttribArray(aTexCoords);

    // Texture ID
    int aTexId = glGetAttribLocation(shader->getProgramId(), "aTexId");
    glVertexAttribPointer(aTexId, TEXTURE_ID_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (void*)TEXTURE_ID_OFFSET);
    glEnableVertexAttribArray(aTexId);
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

    loadVertexProps(index, sprite, transform);

    return Result<void>();
}

void BatchRenderer::loadVertexProps(int index, SpriteRenderer* sprite, Transform* transform) {

    // TODO: Offset will increase based on index of sprite if more are added.
    int offset = index * 4 * VERTEX_SIZE;

    // TODO: May want this to be configurable
    vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};

    vec2* texCoords = sprite->getSprite().getTextureCoords();

    // TODO: As more than one textures are added this will need to be incremented and stored.
    int texId = 1;

    // Add vertices with the appropriate properties
    float xAdd = 0.5f;
    float yAdd = 0.5f;

    vec2 pos;
    vec2 scale;

    memcpy(pos, transform->getPos(), sizeof(vec2));
    memcpy(scale, transform->getScale(), sizeof(vec2));

    for (int i = 0; i < 4; i++) {
        if (i == 1) {
            yAdd = -0.5f;
        } else if (i == 2) {
            xAdd = -0.5f;
        } else if (i == 3) {
            yAdd = 0.5f;
        }

        // Load position
        vertices[offset] = pos[0] + (xAdd * scale[0]);
        vertices[offset + 1] = pos[1] + (yAdd * scale[1]);

        // Load Color
        vertices[offset + 2] = color[0];
        vertices[offset + 3] = color[1];
        vertices[offset + 4] = color[2];
        vertices[offset + 5] = color[3];

        // Load Texture Coordinates
        // TODO: Lookup texture coords from list
        vertices[offset + 6] = texCoords[i][0];
        vertices[offset + 7] = texCoords[i][1];

        // Load Texture ID
        vertices[offset + 8] = texId;

        offset += VERTEX_SIZE;
    }
}

int* BatchRenderer::genIndices() {
    // Six indices per quad, three per triangle
    int elements[6 * MAX_BATCH_SIZE];
    for (int i = 0; i < MAX_BATCH_SIZE; i++) {
        loadElementIndices(elements, i);
    }

    return elements;
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