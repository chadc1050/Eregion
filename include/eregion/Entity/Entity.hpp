#pragma once

#include "eregion/Entity/Component.hpp"

#include <optional>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <vector>

namespace eregion {
class Entity {
  public:
    Entity(std::string name);
    void addComponent(Component* comp);
    void update(float dt);

    template <typename T> std::optional<T*> getComponent() {
        for (Component* comp : comps) {
            T* derived = dynamic_cast<T*>(comp);
            if (derived) {
                return derived;
            }
        }

        return std::nullopt;
    };

    std::vector<Component*> getComponents();

  private:
    std::string name;
    std::vector<Component*> comps;
};
} // namespace eregion