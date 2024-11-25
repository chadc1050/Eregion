#pragma once

#include "eregion/Asset/Font.hpp"
#include "eregion/Entity/Component.hpp"
#include "eregion/Render/Renderable.hpp"

#include <memory>

namespace eregion {
class TextRenderer {
  public:
    TextRenderer(std::string content, std::shared_ptr<Font> font, int zIndex);
    TextRenderer(std::string content, std::shared_ptr<Font> font);
    int getZIndex();

  private:
    std::string content;
    std::shared_ptr<Font> font;
    int zIndex;
};

COMPONENT(TextRenderer)
RENDERABLE(TextRenderer)

} // namespace eregion