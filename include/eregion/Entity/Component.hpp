#pragma once

#include <concepts>

namespace eregion {

#define COMPONENT(Type)                                                                                                \
    template <> struct ComponentTrait<Type> {                                                                          \
        static constexpr bool is_component = true;                                                                     \
    };

template <typename C> struct ComponentTrait {
    static constexpr bool is_component = false;
};

template <typename C>
concept Component = ComponentTrait<C>::is_component;

} // namespace eregion