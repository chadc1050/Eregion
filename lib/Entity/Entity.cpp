#include "eregion/Entity/Entity.h"

using namespace eregion;

namespace eregion {
Entity::Entity(std::string name) { this->name = name; }

void Entity::addComponent(Component comp) { comps.push_back(comp); }

void Entity::update(float dt) {
    for (Component comp : comps) {
        comp.update(dt);
    }
}
} // namespace eregion