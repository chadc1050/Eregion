#pragma once

namespace eregion {
class Component {
  public:
    virtual void update(float dt) = 0;

    virtual ~Component() = default;

  protected:
    Component() = default;
};
} // namespace eregion