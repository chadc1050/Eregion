#pragma once

#include "eregion/Asset/Texture.hpp"

#include <glm/glm.hpp>

#include <array>

// TODO: Switch the roles of Sprite and SpriteRenderer so that we can more easily extend renderering bucket types.
// Essentially it would be preferable for the developer to interact with a sprite construct.
namespace eregion {
struct Sprite {
    Texture* texture;

    Texture* getTexture();
    std::array<glm::vec2, 4> getTextureCoords();
};
} // namespace eregion