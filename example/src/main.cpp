#include "eregion/Core/Game.h"
#include "eregion/Logger/Logger.h"
#include "eregion/Window/Window.h"

int main() {
    using namespace eregion;

    // TODO: This needs to be significantly improved in configuring but for now it is convenient.
    setLogLevel(DEBUG);
    auto res = Game::create(WindowConfig{640, 480, "Celebrimbor"});
    if (res.isSuccess()) {
        Game* game = res.getValue();
        auto runRes = game->run();
        if (runRes.isError()) {
            printf("Error!");
        }
        delete game;
    } else {
        return 1;
    }

    return 0;
}