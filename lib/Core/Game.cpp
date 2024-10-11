#include "eregion/Core/Game.hpp"

// This has to be here, or included in a seperate impl file that does not use any of the functionality.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace eregion;

namespace eregion {

Result<Game*> Game::create() { return create(WindowConfig{640, 480, "Eregion"}); }

Result<Game*> Game::create(WindowConfig windowConfig) {

    Game* game = new Game();

    // Initialize graphical library
    if (!glfwInit()) {
        return Result<Game*>(Error{"Could not intialize low level graphics library"});
    }
    info("Initialized OpenGL.");

    // Initialize asset pool
    AssetPool::getInstance();
    info("Initialized Asset Pool.");

    // Create window instance
    game->window = Window::create(windowConfig);

    return Result<Game*>(Success<Game*>{game});
}

Result<void> Game::run() {
    info("Starting game...");
    return window->run();
}

Game::Game() {}

Game::~Game() {
    delete window;
    glfwTerminate();
    warn("Terminated graphics library.");
}
} // namespace eregion