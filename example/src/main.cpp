#include "eregion/Asset/AssetPool.hpp"
#include "eregion/Asset/UniformSpriteSheet.hpp"
#include "eregion/Core/Camera.hpp"
#include "eregion/Core/Game.hpp"
#include "eregion/Core/MouseListener.hpp"
#include "eregion/Core/Result.hpp"
#include "eregion/Entity/Entity.hpp"
#include "eregion/Entity/TextRenderer.hpp"
#include "eregion/Logger/Logger.hpp"
#include "eregion/Window/Window.hpp"

#include <stdexcept>
#include <vector>

using namespace eregion;

static void createWorld(Scene* commands, const std::vector<Entity>& entities, float dt) {

    // TEXT
    auto fontRes = AssetPool::getFont("../assets/fonts/Roboto.ttf", 20);

    if (fontRes.isError()) {
        throw std::runtime_error(fontRes.getError());
    }

    Font* roboto = fontRes.getValue();

    Entity text = Entity("text");
    text.addComponent(new TextRenderer("Celebrimbor", std::shared_ptr<Font>(std::move(roboto))));
    text.addComponent(new Transform(glm::vec2(-1.0f, -1.0f)));
    commands->insertEntity(text);

    // SPRITESHEET
    auto terrainRes = AssetPool::getTexture("../assets/textures/terrain.png");
    if (terrainRes.isError()) {
        throw std::runtime_error(terrainRes.getError());
    }

    UniformSpriteSheet terrainSheet = UniformSpriteSheet(terrainRes.getValue(), 32, 32);

    // SPRITE 1
    Entity cornerPath = Entity("cornerPath");
    cornerPath.addComponent(new SpriteRenderer(std::make_shared<Sprite>(terrainSheet.getSprite(0))));
    cornerPath.addComponent(new Transform(glm::vec2(1.5f, -0.5f)));
    commands->insertEntity(cornerPath);

    // SPRITE 2
    Entity topPath = Entity("topPath");
    topPath.addComponent(new SpriteRenderer(std::make_shared<Sprite>(terrainSheet.getSprite(1))));
    topPath.addComponent(new Transform(glm::vec2(2.5f, -0.5f)));
    commands->insertEntity(topPath);

    // SPRITE 3
    Entity leftPath = Entity("leftPath");
    leftPath.addComponent(new SpriteRenderer(std::make_shared<Sprite>(terrainSheet.getSprite(10))));
    leftPath.addComponent(new Transform(glm::vec2(1.5f, -1.5f)));
    commands->insertEntity(leftPath);

    // SPRITE 4
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
        ->scene(Scene::create(Camera(glm::vec3(0.0f, 0.0f, 18.0f)))
                    ->mechanism(LifeCycle::INIT, createWorld)
                    ->mechanism(LifeCycle::UPDATE, cameraMove))
        ->run();

    return 0;
}
