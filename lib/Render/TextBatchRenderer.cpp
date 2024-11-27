#include "eregion/Render/TextBatchRenderer.hpp"

using namespace eregion;

namespace eregion {

TextBatchRenderer::TextBatchRenderer(std::shared_ptr<Camera> camera, int zIndex) {

    this->camera = camera;
    this->zIndex = zIndex;

    Shader vert = AssetPool::getShader("../assets/shaders/texture.vert").getValue();

    Shader frag = AssetPool::getShader("../assets/shaders/texture.frag").getValue();

    shader = ShaderProgram::compile(vert, frag).getValue();
}

void TextBatchRenderer::render() {

    // TODO: This is where we could check to see if the text has been declared dirty, or if transform has changed
    for (int i = 0; i < nText; i++) {
        loadVertexProps(i, true);
    }

    // Always rebuffering until deltas are available!
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_DYNAMIC_DRAW);

    shader->bind();

    // Upload texture slots
    auto samplerRes = shader->uploadIntArray("uTextures", textureSlots, sizeof(textureSlots) / sizeof(int));

    if (samplerRes.isError()) {
        error("Error uploading texture slots to shader.");
    }

    // Upload textures to texture slots
    int count = 0;
    for (const auto& texture : textures) {

        glActiveTexture(GL_TEXTURE0 + count);

        texture->bind();

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
    glDrawElements(GL_TRIANGLES, nChars * N_INDICES, GL_UNSIGNED_INT, 0);

    // Clean up
    glBindVertexArray(0);

    for (const auto& texture : textures) {
        texture->unbind();
    }

    shader->unbind();
}

void TextBatchRenderer::start() {

    debug("Starting batch renderer.");

    // VAO
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    // VBO (Initially zero)
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, 0, vertices.data(), GL_DYNAMIC_DRAW);

    // EBO (Initially zero)
    genIndices();
    glGenBuffers(1, &eboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.data(), GL_STATIC_DRAW);

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

Result<void> TextBatchRenderer::add(TextRenderer* textRenderer, Transform* transform) {

    int index = nText;
    text[nText] = std::make_pair(textRenderer, transform);
    nText++;
    nChars += textRenderer->getContent().size();

    Texture* toAdd = textRenderer->getFont()->getTexture();

    bool present = false;
    for (const auto& texture : textures) {
        if (texture->getName() == toAdd->getName()) {
            present = true;
            break;
        }
    }

    if (!present) {
        textures.push_back(toAdd);
    }

    loadVertexProps(index, false);

    return Result<void>();
}

TextBatchRenderer::~TextBatchRenderer() {
    warn("Destroying batch renderer.");
    glDeleteVertexArrays(1, &vaoId);
    glDeleteBuffers(1, &vboId);
    glDeleteBuffers(1, &eboId);

    delete shader;
}

void TextBatchRenderer::loadVertexProps(int index, bool isRebuffer) {

    std::pair<TextRenderer*, Transform*> entity = text.at(index);

    if (!isRebuffer) {
        // Not yet indexed
        vertexIndices[index] = vertices.size() / VERTEX_SIZE / N_VERTICES;
    }

    int offset = vertexIndices[index] * VERTEX_SIZE * N_VERTICES;

    TextRenderer* textRenderer = entity.first;

    std::string content = textRenderer->getContent();

    // Check if rebuffer is needed
    rebuffer(content, offset);

    glm::vec4 color = textRenderer->getColor();

    // Get Font
    std::shared_ptr<Font> font = textRenderer->getFont();

    // Get Texture Id of Font
    int texId = 0;
    for (const auto& texture : textures) {
        if (texture->getName() == font->getTexture()->getName()) {
            break;
        }
        texId = texId + 1;
    }

    // Get transform
    Transform* transform = entity.second;
    glm::vec2 pos = transform->getPos();
    glm::vec2 scale = transform->getScale();

    int advance = 0;

    for (size_t i = 0; i < content.size(); i++) {
        char toLoad = content[i];

        Character character = font->getCharacter(toLoad);

        for (int vertex = 0; vertex < N_VERTICES; vertex++) {

            // Load position
            float xPos, yPos;

            // Calculate vertex positions
            if (vertex == 0) { // Bottom-left
                xPos = pos.x + advance + (character.bearing.x * scale.x);
                yPos = pos.y - (character.size.y - character.bearing.y) * scale.y;
            } else if (vertex == 1) { // Bottom-right
                xPos = pos.x + advance + (character.bearing.x + character.size.x) * scale.x;
                yPos = pos.y - (character.size.y - character.bearing.y) * scale.y;
            } else if (vertex == 2) { // Top-right
                xPos = pos.x + advance + (character.bearing.x + character.size.x) * scale.x;
                yPos = pos.y - (character.size.y - character.bearing.y - character.size.y) * scale.y;
            } else { // Top-left
                xPos = pos.x + advance + (character.bearing.x * scale.x);
                yPos = pos.y - (character.size.y - character.bearing.y - character.size.y) * scale.y;
            }

            // Load vertex position
            vertices[offset] = xPos;
            vertices[offset + 1] = yPos;

            // Load Color
            vertices[offset + 2] = color.x;
            vertices[offset + 3] = color.y;
            vertices[offset + 4] = color.z;
            vertices[offset + 5] = color.w;

            // Load texture cordinates
            if (vertex == 0) {
                vertices[offset + 6] = character.uvStart.x;
                vertices[offset + 7] = character.uvEnd.y;
            } else if (vertex == 1) {

                vertices[offset + 6] = character.uvEnd.x;
                vertices[offset + 7] = character.uvEnd.y;
            } else if (vertex == 2) {

                vertices[offset + 6] = character.uvEnd.x;
                vertices[offset + 7] = character.uvStart.y;
            } else {

                vertices[offset + 6] = character.uvStart.x;
                vertices[offset + 7] = character.uvStart.y;
            }

            // Load Texture ID
            vertices[offset + 8] = texId;

            offset += VERTEX_SIZE;
        }

        // Bitshift to get the pixel unit value of the advance
        advance += (character.advance >> 6) * scale.x;
    }
}

void TextBatchRenderer::genIndices() {
    // Six indices per quad, three per triangle
    for (int i = 0; i < nChars; i++) {

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

bool TextBatchRenderer::hasRoom() { return nText < MAX_BATCH_SIZE; }

int TextBatchRenderer::getZIndex() { return zIndex; }

void TextBatchRenderer::rebuffer(std::string content, int offset) {

    int requiredVertices = content.size() * VERTEX_SIZE * N_VERTICES;

    if (offset + requiredVertices <= vertices.size()) {
        // Rebuffer not needed
        return;
    }

    vertices.resize(offset + requiredVertices);

    // Rebuffer the VBO
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_DYNAMIC_DRAW);

    // Rebuffer indices
    int requiredIndices = content.size() * N_INDICES;
    indices.resize(offset + requiredIndices);

    genIndices();

    // Rebuffer the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
}
} // namespace eregion