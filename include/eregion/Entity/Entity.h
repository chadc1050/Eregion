#pragma once

#include "eregion/Entity/Component.h"

#include <string>
#include <vector>

namespace eregion {
class Entity {
  public:
    Entity(std::string name);
    void addComponent(Component* comp);
    void update(float dt);
    std::vector<Component*> getComponents();

  private:
    std::string name;
    std::vector<Component*> comps;
};
} // namespace eregion