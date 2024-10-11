#include "eregion/Core/Scene.hpp"

using namespace eregion;

namespace eregion {

Scene::Scene() : Scene(new Camera({0.0f, 0.0f})) {};

Scene::Scene(Camera* camera) {
    this->camera = camera;
    this->renderer = new Renderer();
};

Scene::~Scene() {
    delete camera;
    delete renderer;
}

Result<void> Scene::init() {
    // This would be the override for setting up the scene (add resources, entities etc..)
    // This is just test code and needs to be set up in the example.
    auto res = AssetPool::getTexture("../assets/textures/wall.jpg");
    if (res.isError()) {
        return Result<void>(Error{"Error loading texture."});
    }
    Texture texture = res.getValue();
    Entity ui = Entity("wall");
    Sprite sprite = {&texture, texture.width, texture.height};
    SpriteRenderer* spriteRenderer = new SpriteRenderer(sprite);
    ui.addComponent(spriteRenderer);
    glm::vec2 pos = {0.0f, 0.0f};
    Transform* transform = new Transform(&pos);
    ui.addComponent(transform);
    entities.push_back(ui);
    renderer->insertEntity(ui);
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

} // namespace eregion