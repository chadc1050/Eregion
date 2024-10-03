#pragma once

#include "eregion/Asset/AssetPool.h"
#include "eregion/Core/Result.h"
#include "eregion/Logger/Logger.h"
#include "eregion/Window/Window.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <variant>

namespace eregion {
class Game {
  public:
    static Result<Game*> create();
    static Result<Game*> create(WindowConfig windowConfig);
    Result<void> run();
    ~Game();

  private:
    Window* window;

    Game();
};
} // namespace eregion
