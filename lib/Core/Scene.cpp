#include "eregion/Core/Scene.hpp"

using namespace eregion;

namespace eregion {

Scene::Scene(Camera camera) {
    this->camera = std::make_shared<Camera>(std::move(camera));
    this->renderer = new Renderer(this->camera);
};

Scene::~Scene() { delete renderer; }

/// @brief Update scene state
/// @param dt Time delta
void Scene::update(float dt) {

    // Update entities, and by extension, their components.
    for (Entity entity : entities) {
        entity.update(dt);
    }
}

/// @brief Draw scene state
void Scene::draw() {
    // Render
    renderer->render();
}

void Scene::insertEntity(Entity entity) {
    entities.push_back(entity);
    renderer->insertEntity(entity);
}

void Scene::save() {
    // TODO: Save Scene current state
}

void Scene::viewportUpdate(unsigned int width, unsigned int height) {
    debug("Sending viewport resize to scene.");
    camera->updateViewport(width, height);
}

} // namespace eregion