#pragma once

#include "vec.hh"

struct Camera {
    vec3f position;
    vec3f orientation;
    double fov;

    Camera() : position{0}, orientation{0, 0, 1}, fov(M_PI / 4) {}
};
