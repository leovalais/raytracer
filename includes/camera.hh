#pragma once

#include <fstream>
#include "vec.hh"

struct Camera {
    vec3f position;
    vec3f rotation;
    double fov;
    unsigned image_width, image_height;

    static Camera from_json(std::istream& stream);
};
