#pragma once

#include <concepts>

namespace eregion {

#define RENDERABLE(Type)                                                                                               \
    template <> struct RenderableTrait<Type> {                                                                         \
        static constexpr bool is_renderable = true;                                                                    \
    };

template <typename R> struct RenderableTrait {
    static constexpr bool is_renderable = false;
};

template <typename R>
concept Renderable = RenderableTrait<R>::is_renderable && requires(R r) {
    { r.getZIndex } -> std::convertible_to<int>;
};

} // namespace eregion