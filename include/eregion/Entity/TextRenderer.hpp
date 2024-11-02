#pragma once

#include "eregion/Asset/Font.hpp"

namespace eregion {
class TextRenderer : public Component {
  public:
    TextRenderer(std::string content, std::shared_ptr<Font> font);
}
} // namespace eregion