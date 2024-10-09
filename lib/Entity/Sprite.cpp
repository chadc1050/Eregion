#include "eregion/Entity/Sprite.h"

using namespace eregion;

namespace eregion {
glm::vec2* Sprite::getTextureCoords() {
    static glm::vec2 texCoords[4] = {glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 0.0f),
                                     glm::vec2(0.0f, 1.0f)};

    return texCoords;
}
} // namespace eregion