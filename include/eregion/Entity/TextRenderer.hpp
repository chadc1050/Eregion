#pragma once

#include "eregion/Asset/Font.hpp"
#include "eregion/Entity/Component.hpp"

#include <memory>

namespace eregion {
class TextRenderer {
  public:
    TextRenderer(std::string content, std::shared_ptr<Font> font);

  private:
    std::string content;
    std::shared_ptr<Font> font;
};

COMPONENT(TextRenderer)

} // namespace eregion