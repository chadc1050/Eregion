#include "eregion/Entity/TextRenderer.hpp"

using namespace eregion;

namespace eregion {

TextRenderer::TextRenderer(std::string content, std::shared_ptr<Font> font, glm::vec4 color, int zIndex) {
    this->content = content;
    this->font = font;
    this->color = color;
    this->zIndex = zIndex;
}

TextRenderer::TextRenderer(std::string content, std::shared_ptr<Font> font, int zIndex) {
    this->content = content;
    this->font = font;
    this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    this->zIndex = zIndex;
}

TextRenderer::TextRenderer(std::string content, std::shared_ptr<Font> font) {
    this->content = content;
    this->font = font;
    this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    this->zIndex = 0;
}

std::string TextRenderer::getContent() { return content; }

std::shared_ptr<Font> TextRenderer::getFont() { return font; }

glm::vec4 TextRenderer::getColor() { return color; }

int TextRenderer::getZIndex() { return zIndex; }
} // namespace eregion