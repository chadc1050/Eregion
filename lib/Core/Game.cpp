#include "eregion/Core/Game.h"

using namespace eregion;

namespace eregion {

Result<Game*> Game::create() {

    Game* game = new Game();

    // Initialize graphical library
    if (!glfwInit()) {
        return Result<Game*>(Error{"Could not intialize low level graphics library"});
    }
    printf("Initialized OpenGL\n");

    // Initialize asset pool
    AssetPool::getInstance();
    printf("Initialized Asset Pool\n");

    // Create window instance
    game->window = Window::create(WindowConfig{640, 480, "Celebrimbor"});

    return Result<Game*>(Success<Game*>{game});
}

Result<void> Game::run() {
    printf("Starting game...\n");
    return window->run();
}

Game::Game() {}

Game::~Game() {
    delete window;
    glfwTerminate();
    printf("Terminated graphics library.\n");
}
} // namespace eregion