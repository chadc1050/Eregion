#include "eregion/Core/Game.h"

int main() {
    printf("Starting...\n");
    auto res = eregion::Game::create();
    if (res.isSuccess()) {
        eregion::Game* game = res.getValue();
        game->run();
        delete game;
    } else {
        return 1;
    }

    return 0;
}