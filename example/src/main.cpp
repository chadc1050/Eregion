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

static void createWorld(Scene* commands, const std::vector<Entity*>& entities, float dt) {

    // TEXT
    auto fontRes = AssetPool::getFont("../assets/fonts/Roboto.ttf", 24);

    if (fontRes.isError()) {
        throw std::runtime_error(fontRes.getError());
    }

    Font* font = fontRes.getValue();

    Entity* text = Entity::create("text")
                       ->component(new TextRenderer("Celebrimbor", std::shared_ptr<Font>(std::move(font))))
                       ->component(new Transform(glm::vec2(-10.0f, 6.0f), 0.05f));

    commands->insertEntity(text);

    // SPRITESHEET
    auto terrainRes = AssetPool::getTexture("../assets/textures/terrain.png");
    if (terrainRes.isError()) {
        throw std::runtime_error(terrainRes.getError());
    }

    UniformSpriteSheet terrainSheet = UniformSpriteSheet(terrainRes.getValue(), 32, 32);

    // SPRITE 1
    Entity* cornerPath = Entity::create("cornerPath")
                             ->component(new SpriteRenderer(std::make_shared<Sprite>(terrainSheet.getSprite(0))))
                             ->component(new Transform(glm::vec2(1.5f, -0.5f)));

    commands->insertEntity(cornerPath);

    // SPRITE 2
    Entity* topPath = Entity::create("topPath")
                          ->component(new SpriteRenderer(std::make_shared<Sprite>(terrainSheet.getSprite(1))))
                          ->component(new Transform(glm::vec2(2.5f, -0.5f)));
    commands->insertEntity(topPath);

    // SPRITE 3
    Entity* leftPath = Entity::create("leftPath")
                           ->component(new SpriteRenderer(std::make_shared<Sprite>(terrainSheet.getSprite(10))))
                           ->component(new Transform(glm::vec2(1.5f, -1.5f)));
    commands->insertEntity(leftPath);

    // SPRITE 4
    Entity* middlePath = Entity::create("middlePath")
                             ->component(new SpriteRenderer(std::make_shared<Sprite>(terrainSheet.getSprite(11))))
                             ->component(new Transform(glm::vec2(2.5f, -1.5f)));
    commands->insertEntity(middlePath);

    // SPRITE 6
    Entity* water = Entity::create("water")
                        ->component(new SpriteRenderer(std::make_shared<Sprite>(terrainSheet.getSprite(153))))
                        ->component(new Transform(glm::vec2(-2.5f, -1.5f)));
    commands->insertEntity(water);
}

static void cameraMove(Scene* commands, const std::vector<Entity*>& entities, float dt) {
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
