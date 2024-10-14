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
    auto res = AssetPool::getTexture("../assets/textures/wall.jpg");
    if (res.isError()) {
        return Result<void>(Error{"Error loading texture."});
    }
    Texture texture = res.getValue();

    Sprite sprite = {&texture, texture.width, texture.height};

    Entity wall1 = Entity("wall");
    wall1.addComponent(new SpriteRenderer(&sprite));
    wall1.addComponent(new Transform());
    entities.push_back(wall1);
    renderer->insertEntity(wall1);

    Entity wall2 = Entity("wall2");
    wall2.addComponent(new SpriteRenderer(&sprite));
    wall2.addComponent(new Transform(glm::vec2(-1.0f, 0.0f)));
    entities.push_back(wall2);
    renderer->insertEntity(wall2);

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