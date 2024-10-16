#include "eregion/Core/Scene.hpp"

using namespace eregion;

namespace eregion {

Scene::Scene() : Scene(Camera(glm::vec3(0.0f, 0.0f, 5.0f))) {};

Scene::Scene(Camera camera) {
    this->camera = std::make_shared<Camera>(std::move(camera));
    this->renderer = new Renderer(this->camera);
};

Scene::~Scene() { delete renderer; }

Result<void> Scene::init() {

    // This would be the override for setting up the scene (add resources, entities etc..)
    // This is just test code and needs to be set up in the example.

    // SPRITE 1
    auto marbleRes = AssetPool::getTexture("../assets/textures/marble.jpg");
    if (marbleRes.isError()) {
        return Result<void>(Error{"Error loading texture."});
    }

    Texture* marbleTexture = marbleRes.getValue();

    auto marbleSprite = std::make_shared<Sprite>(marbleTexture);

    Entity marble = Entity("marble");
    marble.addComponent(new SpriteRenderer(marbleSprite));
    marble.addComponent(new Transform(glm::vec2(-2.0f, 0.0f)));
    entities.push_back(marble);
    renderer->insertEntity(marble);

    // SPRITE 2
    auto wallRes = AssetPool::getTexture("../assets/textures/wall.jpg");
    if (wallRes.isError()) {
        return Result<void>(Error{"Error loading texture."});
    }

    Texture* bricksTexture = wallRes.getValue();

    auto bricksSprite = std::make_shared<Sprite>(bricksTexture);

    Entity bricks = Entity("bricks");
    bricks.addComponent(new SpriteRenderer(bricksSprite));
    bricks.addComponent(new Transform());
    entities.push_back(bricks);
    renderer->insertEntity(bricks);

    // SPRITE 3
    auto uiRes = AssetPool::getTexture("../assets/textures/crafting.png");
    if (uiRes.isError()) {
        return Result<void>(Error{"Error loading texture."});
    }

    Texture* uiTexture = uiRes.getValue();

    auto uiSprite = std::make_shared<Sprite>(uiTexture);

    Entity ui = Entity("ui");
    ui.addComponent(new SpriteRenderer(uiSprite, 999));
    ui.addComponent(new Transform(glm::vec2(0.5f, 0.5f)));
    entities.push_back(ui);
    renderer->insertEntity(ui);

    auto terrainRes = AssetPool::getTexture("../assets/textures/terrain.png");
    if (terrainRes.isError()) {
        return Result<void>(Error{"Error loading texture."});
    }

    // SPRITESHEET
    Texture* terrainTexture = terrainRes.getValue();

    SpriteSheet terrainSheet = SpriteSheet(terrainTexture);

    // SPRITE 4
    auto cornerPathSprite = std::make_shared<Sprite>(terrainSheet.getSprite(0, 480, 32, 32));

    Entity cornerPath = Entity("cornerPath");
    cornerPath.addComponent(new SpriteRenderer(cornerPathSprite));
    cornerPath.addComponent(new Transform(glm::vec2(1.5f, -1.5f)));
    entities.push_back(cornerPath);
    renderer->insertEntity(cornerPath);

    // SPRITE 5
    auto topPathSprite = std::make_shared<Sprite>(terrainSheet.getSprite(32, 480, 32, 32));

    Entity topPath = Entity("topPath");
    topPath.addComponent(new SpriteRenderer(topPathSprite));
    topPath.addComponent(new Transform(glm::vec2(2.5f, -1.5f)));
    entities.push_back(topPath);
    renderer->insertEntity(topPath);

    return Result<void>();
}

void Scene::update(float dt) {

    // Update entities, and by extension, their components.
    for (Entity entity : entities) {
        entity.update(dt);
    }

    // Render
    renderer->render();
}

void Scene::insertEntity(Entity entity) { entities.push_back(entity); }

void Scene::save() {
    // TODO: Save Scene current state
}

void Scene::viewportUpdate(unsigned int width, unsigned int height) {
    debug("Sending viewport resize to scene.");
    camera->updateViewport(width, height);
}

} // namespace eregion