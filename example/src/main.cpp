#include "eregion/Asset/AssetPool.hpp"
#include "eregion/Asset/SpriteSheet.hpp"
#include "eregion/Core/Camera.hpp"
#include "eregion/Core/Game.hpp"
#include "eregion/Core/Result.hpp"
#include "eregion/Entity/Entity.hpp"
#include "eregion/Window/Window.hpp"

#include <stdexcept>

class LevelScene : public eregion::Scene {

  public:
    LevelScene(eregion::Camera camera) : eregion::Scene(camera) {}

    void init() override {

        using namespace eregion;

        // SPRITE 1
        auto marbleRes = AssetPool::getTexture("../assets/textures/marble.jpg");
        if (marbleRes.isError()) {
            throw std::runtime_error(marbleRes.getError());
        }

        Texture* marbleTexture = marbleRes.getValue();

        auto marbleSprite = std::make_shared<Sprite>(marbleTexture);

        Entity marble = Entity("marble");
        marble.addComponent(new SpriteRenderer(marbleSprite));
        marble.addComponent(new Transform(glm::vec2(-2.0f, 0.0f)));
        this->insertEntity(marble);

        // SPRITE 2
        auto wallRes = AssetPool::getTexture("../assets/textures/wall.jpg");
        if (wallRes.isError()) {
            throw std::runtime_error(wallRes.getError());
        }

        Texture* bricksTexture = wallRes.getValue();

        auto bricksSprite = std::make_shared<Sprite>(bricksTexture);

        Entity bricks = Entity("bricks");
        bricks.addComponent(new SpriteRenderer(bricksSprite));
        bricks.addComponent(new Transform());
        this->insertEntity(bricks);

        // SPRITE 3
        auto uiRes = AssetPool::getTexture("../assets/textures/crafting.png");
        if (uiRes.isError()) {
            throw std::runtime_error(uiRes.getError());
        }

        Texture* uiTexture = uiRes.getValue();

        auto uiSprite = std::make_shared<Sprite>(uiTexture);

        Entity ui = Entity("ui");
        ui.addComponent(new SpriteRenderer(uiSprite, 999));
        ui.addComponent(new Transform(glm::vec2(0.5f, 0.5f)));
        this->insertEntity(ui);

        auto terrainRes = AssetPool::getTexture("../assets/textures/terrain.png");
        if (terrainRes.isError()) {
            throw std::runtime_error(terrainRes.getError());
        }

        // SPRITESHEET
        Texture* terrainTexture = terrainRes.getValue();

        SpriteSheet terrainSheet = SpriteSheet(terrainTexture);

        // SPRITE 4
        auto cornerPathSprite = std::make_shared<Sprite>(terrainSheet.getSprite(0, 480, 32, 32));

        Entity cornerPath = Entity("cornerPath");
        cornerPath.addComponent(new SpriteRenderer(cornerPathSprite));
        cornerPath.addComponent(new Transform(glm::vec2(1.5f, -1.5f)));
        this->insertEntity(cornerPath);

        // SPRITE 5
        auto topPathSprite = std::make_shared<Sprite>(terrainSheet.getSprite(32, 480, 32, 32));

        Entity topPath = Entity("topPath");
        topPath.addComponent(new SpriteRenderer(topPathSprite));
        topPath.addComponent(new Transform(glm::vec2(2.5f, -1.5f)));
        this->insertEntity(topPath);
    }
};

int main() {
    using namespace eregion;

    Game::create(WindowConfig{640, 480, "Celebrimbor", true})
        ->scene(new LevelScene(Camera(glm::vec3(0.0f, 0.0f, 5.0f))))
        ->run();

    return 0;
}