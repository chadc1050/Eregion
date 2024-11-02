#include "eregion/Entity/TextRenderer.hpp"

using namespace eregion;

namespace eregion {

TextRenderer::TextRenderer(std::string content, std::shared_ptr<Font> font) {
    this->content = content;
    this->font = font;
}

void TextRenderer::update(float dt) {}
} // namespace eregion