#include "eregion/Core/Scene.hpp"

using namespace eregion;

namespace eregion {

/// @brief Creates a scene abstraction from which all renderering and entity data is based from.
/// @param camera The camera to observe the scene with
/// @return The constructed scene
Scene* Scene::create(Camera camera) { return new Scene(camera); }

/// @brief Add mechanism to scene.
/// @param lifeCycle Lifecycle where the mechanism should be run at
/// @param mechanism The mechanism function
/// @return The scene
Scene* Scene::mechanism(LifeCycle lifeCycle, Mechanism mechanism) {
    switch (lifeCycle) {
    case INIT:
        initMechanisms.push_back(mechanism);
        break;
    case UPDATE:
        updateMechanisms.push_back(mechanism);
        break;
    }

    return this;
}

/// @brief Initialize scene.
void Scene::init() {
    for (Mechanism mechanism : initMechanisms) {
        mechanism(this, entities, -1.0f);
    }
}

/// @brief Update scene state.
/// @param dt Time delta
void Scene::update(float dt) {

    for (Mechanism mechanism : updateMechanisms) {
        mechanism(this, entities, dt);
    }

    // Update entities, and by extension, their components.
    for (Entity entity : entities) {
        entity.update(dt);
    }
}

/// @brief Draw scene state
void Scene::draw() { renderer->render(); }

void Scene::insertEntity(Entity entity) {
    entities.push_back(entity);
    renderer->insertEntity(entity);
}

Scene::Scene(Camera camera) {
    this->camera = std::make_shared<Camera>(std::move(camera));
    this->renderer = new Renderer(this->camera);
};

Scene::~Scene() { delete renderer; }

void Scene::viewportUpdate(unsigned int width, unsigned int height) { camera->updateViewport(width, height); }

} // namespace eregion