#pragma once

#include <type_traits>
#include <cmath>
#include "printers.hh"

template <class F>
struct y_combinator {
    F f; // the lambda will be stored here

    // a forwarding operator():
    template <class... Args>
    decltype(auto) operator()(Args&&... args) const {
        // we pass ourselves to f, then the arguments.
        return f(*this, std::forward<Args>(args)...);
    }
};

template <class F>
y_combinator(F) -> y_combinator<F>;

// helper function that deduces the type of the lambda:
template <class F>
y_combinator<std::decay_t<F>> make_y_combinator(F&& f) {
    return {std::forward<F>(f)};
}

template <typename T>
inline constexpr T deg_to_rad(const T deg) {
    return deg * M_PI / 180.0;
}

template <typename T>
inline constexpr T clamp(const T value, const T min, const T max) {
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}
