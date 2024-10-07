#include "eregion/Entity/Sprite.h"

using namespace eregion;

namespace eregion {
vec2* Sprite::getTextureCoords() {
    static vec2 texCoords[4] = {vec2{1.0f, 1.0f}, vec2{1.0f, 0.0f}, vec2{0.0f, 0.0f}, vec2{0.0f, 1.0f}};

    return texCoords;
}
} // namespace eregion