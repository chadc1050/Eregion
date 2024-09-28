#include "eregion/Core/Game.h"

using namespace eregion;

namespace eregion {

Result<Game> Game::create() {

    Game game = Game();

    // Initialize graphical library
    if (!glfwInit()) {
        return Result<Game>(Error{"Could not intialize low level graphics library"});
    }

    printf("Initialized OpenGL\n");

    if (auto windowRes = Window::create(); windowRes.isSuccess()) {
        std::cout << "Created window";
        eregion::Window window = windowRes.getValue();
    } else {
        std::cerr << "Could not create window";
        glfwTerminate();
        return Result<Game>(Error{"Could not create window"});
    }

    return Result<Game>(Success<Game>{game});
}

// void Game::end() { glfwTerminate(); }
} // namespace eregion