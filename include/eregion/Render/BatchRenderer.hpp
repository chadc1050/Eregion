#pragma once

#include "eregion/Core/Result.hpp"
#include "eregion/Entity/Transform.hpp"
#include "eregion/Render/Renderable.hpp"

namespace eregion {

template <typename R> class BatchRenderer {
  public:
    BatchRenderer(int zIndex) { this->zIndex = zIndex; }

    virtual void start() = 0;
    virtual void render() = 0;
    virtual bool hasRoom() = 0;

    virtual Result<void> add(std::shared_ptr<R> renderable, Transform* transform) = 0;

    int getZIndex() { return zIndex; }

    // Comparision operators for determining draw order
    bool operator<(const BatchRenderer& other) const { return zIndex < other.zIndex; }
    bool operator>(const BatchRenderer& other) const { return zIndex > other.zIndex; }
    bool operator<=(const BatchRenderer& other) const { return zIndex <= other.zIndex; }
    bool operator>=(const BatchRenderer& other) const { return zIndex >= other.zIndex; }
    bool operator==(const BatchRenderer& other) const { return zIndex == other.zIndex; }

  private:
    // Z-Index
    int zIndex;
};
} // namespace eregion