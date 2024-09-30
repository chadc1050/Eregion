#include "eregion/Core/Game.h"

int main() {
    auto res = eregion::Game::create();
    if (res.isSuccess()) {
        eregion::Game* game = res.getValue();
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