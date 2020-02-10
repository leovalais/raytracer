#pragma once

#include <optional>
#include "color.hh"
#include "vec.hh"

template <unsigned N = 5>
struct Ray {
    const vec3f origin;
    const vec3f direction;

    /**
     * Returns the point in the given triangle where this ray intersects it, if any.
     * C.f. Möller–Trumbore algorithm:
     * https://en.wikipedia.org/wiki/Möller–Trumbore_intersection_algorithm
     */
    std::optional<vec3f> intersection(const triangle&) const;
};

#include "ray.hxx"
