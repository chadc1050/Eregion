#include "eregion/Core/Game.hpp"
#include "eregion/Window/Window.hpp"

int main() {
    using namespace eregion;

    // TODO: This needs to be significantly improved in configuring but for now it is convenient.

    Game::create(WindowConfig{640, 480, "Celebrimbor", true})->scene(new Scene())->run();

    return 0;
}