#pragma once

#include "eregion/Asset/AssetPool.hpp"
#include "eregion/Core/Result.hpp"
#include "eregion/Logger/Logger.hpp"
#include "eregion/Window/Window.hpp"

#include <GLFW/glfw3.h>
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
