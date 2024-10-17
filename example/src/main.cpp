#include "eregion/Core/Game.hpp"
#include "eregion/Logger/Logger.hpp"
#include "eregion/Window/Window.hpp"

int main() {
    using namespace eregion;

    // TODO: This needs to be significantly improved in configuring but for now it is convenient.
    setLogLevel(DEBUG);

    Game::create(WindowConfig{640, 480, "Celebrimbor"})->run();

    return 0;
}