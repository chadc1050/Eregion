#ifndef EREGION_ENTITY_H
#define EREGION_ENTITY_H

#include "eregion/Entity/Component.h"

#include <string>
#include <vector>

namespace eregion {
class Entity {
  public:
    Entity(std::string name);
    void addComponent(Component comp);
    void update(float dt);

  private:
    std::string name;
    std::vector<Component> comps;
};
} // namespace eregion

#endif