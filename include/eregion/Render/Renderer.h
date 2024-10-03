#pragma once

#include "eregion/Render/BatchRenderer.h"
#include <vector>

namespace eregion {

class Renderer {
  public:
    void render();

  private:
    static const int MAX_BATCH_SIZE = 100;
    std::vector<BatchRenderer> batchRenderers;
};
} // namespace eregion