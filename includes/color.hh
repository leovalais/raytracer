#pragma once

#include <iostream>

/**
 * RGB Color with channels of type Trait::type within range [0, Trait::max].
 */
template <typename Trait>
struct Color {
    static constexpr typename Trait::type MAX = Trait::max;
    typename Trait::type r, g, b;

    Color() : r{}, g{}, b{} { }
    Color(typename Trait::type r_, typename Trait::type g_, typename Trait::type b_)
        : r(r_), g(g_), b(b_) { }
    // Color(const Color&) = default;
    // Color(Color&&)      = delete;
    // Color& operator=(const Color&) = default;
    // Color& operator=(Color&&) = delete;

    template <typename OtherTrait>
    Color(Color<OtherTrait>& other)
        : r{static_cast<typename Trait::type>(Trait::max * static_cast<double>(other.r)
                                              / OtherTrait::max)}
        , g{static_cast<typename Trait::type>(Trait::max * static_cast<double>(other.g)
                                              / OtherTrait::max)}
        , b{static_cast<typename Trait::type>(Trait::max * static_cast<double>(other.b)
                                              / OtherTrait::max)} { }

    template <typename OtherTrait>
    Color(const Color<OtherTrait>& other)
        : r{static_cast<typename Trait::type>(Trait::max * static_cast<double>(other.r)
                                              / OtherTrait::max)}
        , g{static_cast<typename Trait::type>(Trait::max * static_cast<double>(other.g)
                                              / OtherTrait::max)}
        , b{static_cast<typename Trait::type>(Trait::max * static_cast<double>(other.b)
                                              / OtherTrait::max)} { }
};

template <typename T>
Color<T> operator+(const Color<T>& a, const Color<T>& b) {
    return {a.r + b.r, a.g + b.g, a.b + b.b};
}

template <typename T>
Color<T> operator-(const Color<T>& a, const Color<T>& b) {
    return {a.r - b.r, a.g - b.g, a.b - b.b};
}

template <typename T>
Color<T> operator*(const typename T::type f, const Color<T>& c) {
    return {f * c.r, f * c.g, f * c.b};
}
template <typename T>
Color<T> operator*(const Color<T>& c, const typename T::type f) {
    return f * c;
}
template <typename T>
Color<T> operator*(const Color<T>& a, const Color<T>& b) {
    return {a.r * b.r, a.g * b.g, a.b * b.b};
}

template <typename T>
Color<T> operator/(const Color<T>& c, const typename T::type f) {
    return {c.r / f, c.g / f, c.b / f};
}

struct RGB_trait {
    using type                = double;
    static constexpr type max = 1.0;
};
using RGB = Color<RGB_trait>;

struct ByteRGB_trait {
    using type                = unsigned char; // same as FreeImage's BYTE typedef
    static constexpr type max = 255;
};
using ByteRGB = Color<ByteRGB_trait>;
