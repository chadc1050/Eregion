#pragma once

#include "eregion/Entity/Component.hpp"
#include "eregion/Render/Renderable.hpp"

#include <any>
#include <optional>
#include <string>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>

namespace eregion {
class Entity {
  public:
    static Entity* create(std::string name) { return new Entity(name); }

    template <Component C> void addComponent(C* comp) { comps[typeid(C)] = comp; }

    template <Component C> Entity* component(C* comp) {
        addComponent(comp);
        return this;
    }

    template <Component C> std::optional<C*> getComponent() {
        auto it = comps.find(typeid(C));
        if (it != comps.end()) {
            // Cast std::any back to the appropriate pointer type
            return std::any_cast<C*>(it->second);
        }
        return std::nullopt;
    }

    template <Component C> std::vector<C*> getComponents() {
        std::vector<C*> result;
        auto it = comps.find(typeid(C));
        if (it != comps.end()) {
            result.push_back(std::any_cast<C*>(it->second));
        }
        return result;
    }

  private:
    std::string name;

    // TODO: See if we can make this bounded to component
    std::unordered_map<std::type_index, std::any> comps;

    Entity(std::string name) : name(std::move(name)) {}
};
} // namespace eregion