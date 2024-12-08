#pragma once

#include "eregion/Asset/Font.hpp"
#include "eregion/Entity/Component.hpp"
#include "eregion/Render/Renderable.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace eregion {
class TextRenderer {
  public:
    TextRenderer(std::string content, std::shared_ptr<Font> font, glm::vec4 color, int zIndex);
    TextRenderer(std::string content, std::shared_ptr<Font> font, int zIndex);
    TextRenderer(std::string content, std::shared_ptr<Font> font);

    std::string getContent();
    std::shared_ptr<Font> getFont();
    glm::vec4 getColor();
    int getZIndex();

  private:
    std::string content;
    std::shared_ptr<Font> font;
    glm::vec4 color;
    int zIndex;
};

COMPONENT(TextRenderer)
RENDERABLE(TextRenderer)

} // namespace eregion