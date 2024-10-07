#pragma once

#include "eregion/Asset/Texture.h"

#include "linmath.h"

// TODO: Switch the roles of Sprite and SpriteRenderer so that we can more easily extend renderering bucket types.
// Essentially it would be preferable for the developer to interact with a sprite construct.
namespace eregion {
struct Sprite {
    Texture* texture;
    float width;
    float height;

    vec2* getTextureCoords();
};
} // namespace eregion