#include "eregion/Entity/Entity.hpp"

using namespace eregion;

namespace eregion {
Entity::Entity(std::string name) { this->name = name; }

void Entity::addComponent(Component* comp) { comps.push_back(comp); }

void Entity::update(float dt) {
    for (Component* comp : comps) {
        comp->update(dt);
    }
}

std::vector<Component*> Entity::getComponents() { return comps; }
} // namespace eregion