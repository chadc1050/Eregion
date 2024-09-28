#ifndef EREGION_GAME_H
#define EREGION_GAME_H

#include "eregion/Asset/AssetPool.h"
#include "eregion/Core/Result.h"
#include "eregion/Window/Window.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <variant>

namespace eregion {
class Game {
  public:
    static Result<Game> create();

  private:
    AssetPool assets;
};
} // namespace eregion

#endif
