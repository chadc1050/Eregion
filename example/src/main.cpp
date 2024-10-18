#include "eregion/Asset/AssetPool.hpp"
#include "eregion/Asset/SpriteSheet.hpp"
#include "eregion/Core/Camera.hpp"
#include "eregion/Core/Game.hpp"
#include "eregion/Core/Result.hpp"
#include "eregion/Entity/Entity.hpp"
#include "eregion/Window/Window.hpp"

#include <stdexcept>

using namespace eregion;

class LevelScene : public Scene {

  public:
    LevelScene(Camera camera) : Scene(camera) {}

    void init() override {

        // SPRITE 1
        auto marbleRes = AssetPool::getTexture("../assets/textures/marble.jpg");
        if (marbleRes.isError()) {
            throw std::runtime_error(marbleRes.getError());
        }

        Entity marble = Entity("marble");
        marble.addComponent(new SpriteRenderer(std::make_shared<Sprite>(marbleRes.getValue())));
        marble.addComponent(new Transform(glm::vec2(-2.0f, 0.0f)));
        this->insertEntity(marble);

        // SPRITE 2
        auto bricksRes = AssetPool::getTexture("../assets/textures/wall.jpg");
        if (bricksRes.isError()) {
            throw std::runtime_error(bricksRes.getError());
        }

        Entity bricks = Entity("bricks");
        bricks.addComponent(new SpriteRenderer(std::make_shared<Sprite>(bricksRes.getValue())));
        bricks.addComponent(new Transform());
        this->insertEntity(bricks);

        // SPRITE 3
        auto uiRes = AssetPool::getTexture("../assets/textures/crafting.png");
        if (uiRes.isError()) {
            throw std::runtime_error(uiRes.getError());
        }

        Entity ui = Entity("ui");
        ui.addComponent(new SpriteRenderer(std::make_shared<Sprite>(uiRes.getValue()), 999));
        ui.addComponent(new Transform(glm::vec2(0.5f, 0.5f)));
        this->insertEntity(ui);

        // SPRITESHEET
        auto terrainRes = AssetPool::getTexture("../assets/textures/terrain.png");
        if (terrainRes.isError()) {
            throw std::runtime_error(terrainRes.getError());
        }

        SpriteSheet terrainSheet = SpriteSheet(terrainRes.getValue());

        // SPRITE 4
        Entity cornerPath = Entity("cornerPath");
        cornerPath.addComponent(new SpriteRenderer(std::make_shared<Sprite>(terrainSheet.getSprite(0, 480, 32, 32))));
        cornerPath.addComponent(new Transform(glm::vec2(1.5f, -1.5f)));
        this->insertEntity(cornerPath);

        // SPRITE 5
        Entity topPath = Entity("topPath");
        topPath.addComponent(new SpriteRenderer(std::make_shared<Sprite>(terrainSheet.getSprite(32, 480, 32, 32))));
        topPath.addComponent(new Transform(glm::vec2(2.5f, -1.5f)));
        this->insertEntity(topPath);
    }
};

int main() {

    Game::create(WindowConfig{640, 480, "Celebrimbor", true})
        ->scene(new LevelScene(Camera(glm::vec3(0.0f, 0.0f, 5.0f))))
        ->run();

    return 0;
}