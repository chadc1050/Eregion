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
    Entity(std::string name) : name(std::move(name)) {}

    template <Component C> void addComponent(C* comp) { comps[typeid(C)] = comp; }

    template <Component C> std::optional<C*> getComponent() {
        auto it = comps.find(typeid(C));
        if (it != comps.end()) {
            // Cast std::any back to the appropriate pointer type
            return std::any_cast<C*>(it->second);
        }
        return std::nullopt;
    }

    // std::optional<Renderable*> getRenderComponent() {
    //     for (const auto& [_, component] : comps) {
    //         // Check if the component is Renderable
    //         if (auto* renderable = std::any_cast<Renderable*>(&component)) {
    //             return *renderable;
    //         }
    //     }
    //     return std::nullopt;
    // }

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
};
} // namespace eregion