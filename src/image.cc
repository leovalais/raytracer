#include "image.hh"

#include <stdexcept>
#include <cmath>

Image::Image(unsigned width, unsigned height)
    : bitmap{FreeImage_Allocate(width, height, 24)} { }

/**
 * See https://stackoverflow.com/a/61138576
 */
static inline RGB_trait::type linear_rgb_to_sRGB(const RGB_trait::type value) {
    // if (value <= 0.0031308)
    //     return value * 12.92;
    // else
    //     return std::pow(value, 1.0 / 2.4) * 1.055 - 0.055;
    return std::pow(value, 1.0 / 2.2);
}

void Image::gamma_correct() {
    for (unsigned y = 0; y < height(); y++) {
        for (unsigned x = 0; x < width(); x++) {
            const auto p         = point_t{x, y};
            const auto [r, g, b] = RGB{operator[](p)};
            set_pixel(
                p,
                RGB{linear_rgb_to_sRGB(r), linear_rgb_to_sRGB(g), linear_rgb_to_sRGB(b)});
        }
    }
}

void Image::set_pixel(const point_t& coords, const ByteRGB& pixel) const {
    const auto [x, y]    = coords;
    const auto [r, g, b] = pixel;
    auto color           = RGBQUAD{b, g, r, 0};
    if (not FreeImage_SetPixelColor(bitmap.get(), x, y, &color))
        throw std::out_of_range{"Out of range pixel coords"};
}

ByteRGB Image::operator[](const point_t& coords) const {
    const auto [x, y] = coords;
    RGBQUAD color;
    if (not FreeImage_GetPixelColor(bitmap.get(), x, y, &color))
        throw std::out_of_range{"Out of range pixel coords"};
    const auto [b, g, r, _] = color;
    return {r, g, b};
}

static bool ends_with(const std::string& str, const std::string& suffix) {
    return str.size() >= suffix.size()
           and 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

static auto get_fif(const std::string& filename) {
    if (ends_with(filename, "png"))
        return FIF_PNG;
    if (ends_with(filename, "jpg") or ends_with(filename, "jpeg"))
        return FIF_JPEG;
    if (ends_with(filename, "gif"))
        return FIF_GIF;
    throw std::runtime_error("unknown image format (supported: png, jpeg & gif)");
}

void Image::save(const std::string& filename) const {
    if (not FreeImage_Save(get_fif(filename), bitmap.get(), filename.c_str()))
        throw std::runtime_error{"could not save image (FreeImage_Save error)"};
}
