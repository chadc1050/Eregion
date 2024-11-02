#pragma once

#include "eregion/Asset/Font.hpp"
#include "eregion/Entity/Component.hpp"

#include <memory>

namespace eregion {
class TextRenderer : public Component {
  public:
    TextRenderer(std::string content, std::shared_ptr<Font> font);

    void update(float dt) override;

  private:
    std::string content;
    std::shared_ptr<Font> font;
};
} // namespace eregion