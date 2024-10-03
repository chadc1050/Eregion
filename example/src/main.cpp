#include "eregion/Core/Game.h"
#include "eregion/Window/Window.h"

int main() {
    using namespace eregion;
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