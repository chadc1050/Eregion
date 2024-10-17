#include "eregion/Asset/SpriteSheet.hpp"

using namespace eregion;

namespace eregion {
SpriteSheet::SpriteSheet(Texture* texture) { this->texture = texture; }

/// @brief Generates sprite from given coordinates and size.
/// @param x Bottom left pixel x coordinate on texture
/// @param y Bottom left pixel y coordinate on texture
/// @param width Width of sprite
/// @param height Height of sprite
/// @return The sprite
Sprite SpriteSheet::getSprite(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    unsigned int texWidth = this->texture->getWidth();
    unsigned int texHeight = this->texture->getHeight();

    // Get the relative strides for x and y
    float relWidth = static_cast<float>(width) / static_cast<float>(texWidth);
    float relHeight = static_cast<float>(height) / static_cast<float>(texHeight);

    // Get bottom left relative position
    float relX = static_cast<float>(x) / static_cast<float>(texWidth);
    float relY = static_cast<float>(y) / static_cast<float>(texHeight);

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