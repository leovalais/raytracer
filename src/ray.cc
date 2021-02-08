#include "ray.hh"

std::optional<vec3f> Ray::intersection(const triangle& triangle) const {
    static constexpr auto epsilon           = 0.0000001;
    const auto& [vertex0, vertex1, vertex2] = triangle;
    const auto edge1                        = vertex1 - vertex0;
    const auto edge2                        = vertex2 - vertex0;
    const auto h                            = direction ^ edge2;
    const auto a                            = edge1 | h;
    if (a > -epsilon and a < epsilon)
        return std::nullopt; // This ray is parallel to this triangle.

    const auto f = 1.0 / a;
    const auto s = origin - vertex0;
    const auto u = f * (s | h);
    if (u < 0.0 or u > 1.0)
        return std::nullopt;

    const auto q = s ^ edge1;
    const auto v = f * (direction | q);
    if (v < 0.0 or u + v > 1.0)
        return std::nullopt;

    // At this stage we can compute t to find out where the intersection point is on the
    // line.
    const auto t            = f * (edge2 | q);
    const auto intersection = origin + direction * t;
    if (t > epsilon) // ray intersection
        return intersection;
    return std::nullopt;
}
