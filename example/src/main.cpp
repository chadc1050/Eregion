#include "eregion/Asset/AssetPool.hpp"
#include "eregion/Asset/UniformSpriteSheet.hpp"
#include "eregion/Core/Camera.hpp"
#include "eregion/Core/Game.hpp"
#include "eregion/Core/MouseListener.hpp"
#include "eregion/Core/Result.hpp"
#include "eregion/Entity/Entity.hpp"
#include "eregion/Logger/Logger.hpp"
#include "eregion/Window/Window.hpp"

#include <stdexcept>
#include <vector>

using namespace eregion;

static void createWorld(Scene* commands, const std::vector<Entity>& entities, float dt) {

    // SPRITE 1
    auto uiRes = AssetPool::getTexture("../assets/textures/crafting.png");
    if (uiRes.isError()) {
        throw std::runtime_error(uiRes.getError());
    }

    Entity ui = Entity("ui");
    ui.addComponent(new SpriteRenderer(std::make_shared<Sprite>(uiRes.getValue())));
    ui.addComponent(new Transform(glm::vec2(0.5f, 0.5f)));
    commands->insertEntity(ui);

    // SPRITESHEET
    auto terrainRes = AssetPool::getTexture("../assets/textures/terrain.png");
    if (terrainRes.isError()) {
        throw std::runtime_error(terrainRes.getError());
    }

    UniformSpriteSheet terrainSheet = UniformSpriteSheet(terrainRes.getValue(), 32, 32);

    // SPRITE 2
    Entity cornerPath = Entity("cornerPath");
    cornerPath.addComponent(new SpriteRenderer(std::make_shared<Sprite>(terrainSheet.getSprite(0))));
    cornerPath.addComponent(new Transform(glm::vec2(1.5f, -0.5f)));
    commands->insertEntity(cornerPath);

    // SPRITE 3
    Entity topPath = Entity("topPath");
    topPath.addComponent(new SpriteRenderer(std::make_shared<Sprite>(terrainSheet.getSprite(1))));
    topPath.addComponent(new Transform(glm::vec2(2.5f, -0.5f)));
    commands->insertEntity(topPath);

    // SPRITE 4
    Entity leftPath = Entity("leftPath");
    leftPath.addComponent(new SpriteRenderer(std::make_shared<Sprite>(terrainSheet.getSprite(10))));
    leftPath.addComponent(new Transform(glm::vec2(1.5f, -1.5f)));
    commands->insertEntity(leftPath);

    // SPRITE 5
    Entity middlePath = Entity("middlePath");
    middlePath.addComponent(new SpriteRenderer(std::make_shared<Sprite>(terrainSheet.getSprite(11))));
    middlePath.addComponent(new Transform(glm::vec2(2.5f, -1.5f)));
    commands->insertEntity(middlePath);

    // SPRITE 6
    Entity water = Entity("water");
    water.addComponent(new SpriteRenderer(std::make_shared<Sprite>(terrainSheet.getSprite(153))));
    water.addComponent(new Transform(glm::vec2(-2.5f, -1.5f)));
    commands->insertEntity(water);
}

static void cameraMove(Scene* commands, const std::vector<Entity>& entities, float dt) {
    glm::vec2 mouseDelta = MouseListener::getPosChange();
}

int main() {

    Game::create(WindowConfig{640, 480, "Celebrimbor", true})
        ->scene(Scene::create(Camera(glm::vec3(0.0f, 0.0f, 5.0f)))
                    ->mechanism(LifeCycle::INIT, createWorld)
                    ->mechanism(LifeCycle::UPDATE, cameraMove))
        ->run();

    return 0;
}
