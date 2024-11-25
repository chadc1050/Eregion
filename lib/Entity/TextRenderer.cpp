#include "eregion/Entity/TextRenderer.hpp"

using namespace eregion;

namespace eregion {

TextRenderer::TextRenderer(std::string content, std::shared_ptr<Font> font, int zIndex) {
    this->content = content;
    this->font = font;
    this->zIndex = zIndex;
}

TextRenderer::TextRenderer(std::string content, std::shared_ptr<Font> font) {
    this->content = content;
    this->font = font;
    this->zIndex = 0;
}

int TextRenderer::getZIndex() { return zIndex; }
} // namespace eregion