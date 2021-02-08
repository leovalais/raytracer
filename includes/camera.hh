#pragma once

#include "vec.hh"
#include "utils.hh"

constexpr double eyes_fov = deg_to_rad(110);

struct Camera {
    vec3f position;
    vec3f orientation;
    double fov;
    double focal_length;

    Camera() : position{0}, orientation{0, 0, 1}, fov{eyes_fov}, focal_length{1.0} {}
};
