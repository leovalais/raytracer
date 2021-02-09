#pragma once

#include <optional>
#include "color.hh"
#include "vec.hh"
#include "triangle.hh"

struct Ray {
    vec3f origin;
    vec3f direction{0, 0, 1};

    Ray() = default;
    Ray(const vec3f& origin_, const vec3f& direction_)
        : origin(origin_), direction(direction_) { }

    /**
     * Returns the point in the given triangle where this ray intersects it, if any.
     * C.f. Möller–Trumbore algorithm:
     * https://en.wikipedia.org/wiki/Möller–Trumbore_intersection_algorithm
     */
    std::optional<vec3f> intersection(const triangle&) const;
};
