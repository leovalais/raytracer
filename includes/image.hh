#pragma once

#include <memory>
#include <utility>
#include <string>
#include <FreeImage.h>
#include "color.hh"

using point_t = std::pair<unsigned, unsigned>;

struct FIBITMAPDeleter {
    void operator()(FIBITMAP* bitmap) { FreeImage_Unload(bitmap); }
};

class Image {
public:
    Image(unsigned width, unsigned height);
    void set_pixel(const point_t& coords, const ByteRGB& pixel) const;

    ByteRGB operator[](const point_t& coords) const;
    void save(const std::string& filename) const;

private:
    std::unique_ptr<FIBITMAP, FIBITMAPDeleter> bitmap;
};
