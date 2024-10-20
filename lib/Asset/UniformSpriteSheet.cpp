#include "eregion/Asset/UniformSpriteSheet.hpp"

using namespace eregion;

namespace eregion {

UniformSpriteSheet::UniformSpriteSheet(Texture* texture, unsigned int spriteWidth, unsigned int spriteHeight) {
    this->texture = texture;
    this->spriteWidth = spriteWidth;
    this->spriteHeight = spriteHeight;

    // Get dim
    dimX = texture->getWidth() / spriteWidth;

    // Get the relative strides for x and y
    relWidth = static_cast<float>(spriteWidth) / static_cast<float>(texture->getWidth());
    relHeight = static_cast<float>(spriteHeight) / static_cast<float>(texture->getHeight());
}

/// @brief Generates sprite from provide zero-based index.
/// @param idx Index of sprite
/// @return The generated sprite
Sprite UniformSpriteSheet::getSprite(unsigned int idx) {

    // Get bottom left relative position
    unsigned int yOffset = idx / dimX;
    unsigned int xOffset = idx - (yOffset * dimX);

    float relX = static_cast<float>(xOffset * spriteWidth) / static_cast<float>(texture->getWidth());
    float relY = static_cast<float>(texture->getHeight() - ((yOffset + 1) * spriteHeight)) /
                 static_cast<float>(texture->getHeight());

    std::array<glm::vec2, 4> coords;

    // Top right
    coords[0] = glm::vec2(relX + relWidth, relY + relHeight);

    // Bottom right
    coords[1] = glm::vec2(relX + relWidth, relY);

    // Bottom Left
    coords[2] = glm::vec2(relX, relY);

    // Top Left
    coords[3] = glm::vec2(relX, relY + relHeight);

    return Sprite(texture, coords);
}

} // namespace eregion