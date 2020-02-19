#pragma once

#include <json.hpp>
#include "vec.hh"

struct Camera {
    vec3f position;
    vec3f orientation;
    double fov;
    unsigned image_width, image_height;

    Camera()
        : position{0}
        , orientation{0, 0, 1}
        , fov(M_PI / 4)
        , image_width(640)
        , image_height(480) {}
};

void from_json(const nlohmann::json& j, vec3f& vec);
void from_json(const nlohmann::json& j, Camera& cam);
