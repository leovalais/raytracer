#pragma once

/**
 * RGB Color with channels of type Trait::type within range [0, Trait::max].
 */
template <typename Trait>
struct Color {
    static constexpr typename Trait::type MAX = Trait::max;
    const typename Trait::type r, g, b;

    Color() = delete;
    Color(typename Trait::type r_, typename Trait::type g_, typename Trait::type b_)
        : r(r_), g(g_), b(b_) {}
    Color(const Color&)  = default;
    Color(const Color&&) = delete;
    Color& operator=(const Color&) = default;
    Color& operator=(const Color&&) = delete;

    template <typename OtherTrait>
    Color(const Color<OtherTrait>& other)
        : r(Trait::max * static_cast<typename Trait::type>(other.r / OtherTrait::max))
        , g(Trait::max * static_cast<typename Trait::type>(other.g / OtherTrait::max))
        , b(Trait::max * static_cast<typename Trait::type>(other.b / OtherTrait::max)){};
};

struct RGB_trait {
    using type                = float;
    static constexpr type max = 1.0f;
};
using RGB = Color<RGB_trait>;

struct ByteRGB_trait {
    using type                = unsigned;
    static constexpr type max = 255;
};
using ByteRGB = Color<ByteRGB_trait>;
