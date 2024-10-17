#include "eregion/Core/Game.hpp"

// This has to be here, or included in a seperate impl file that does not use any of the functionality.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace eregion;

namespace eregion {

Game* Game::create() { return create(WindowConfig{640, 480, "Eregion"}); }

Game* Game::create(WindowConfig windowConfig) {

    Game* game = new Game();

    // Initialize graphical library
    if (!glfwInit()) {
        throw std::runtime_error("Could not intialize low level graphics library!");
    }

    info("Initialized OpenGL.");

    // Initialize asset pool
    AssetPool::getInstance();
    info("Initialized Asset Pool.");

    // Create window instance
    game->window = Window::create(windowConfig);

    return game;
}

void Game::run() {
    info("Starting game...");
    auto res = window->run();

    if (res.isError()) {
        throw std::runtime_error(res.getError());
    }
}

Game::Game() {}

Game::~Game() {
    delete window;
    glfwTerminate();
    warn("Terminated graphics library.");
}
} // namespace eregion