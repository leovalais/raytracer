#pragma once

#include <array>
#include <vector>
#include <memory>
#include <initializer_list>
#include <type_traits>
#include <tuple>
#include "vec.hh"
#include "material.hh"

struct triangle {
    std::array<vec3f, 3> vertices;
    std::array<vec3f, 3> normals;

    triangle() { }
    triangle(vec3f& v1, vec3f& v2, vec3f& v3) : vertices{v1, v2, v3} { }
    triangle(vec3f& v1, vec3f& v2, vec3f& v3, vec3f& n1, vec3f& n2, vec3f& n3)
        : vertices{v1, v2, v3}, normals{n1, n2, n3} { }
    triangle(const std::array<vec3f, 3>& v) : vertices{v} { }
    triangle(const std::array<vec3f, 3>& v, const std::array<vec3f, 3> n)
        : vertices{v}, normals{n} { }
    triangle(std::array<vec3f, 3>&& v) : vertices{std::forward<decltype(v)>(v)} { }
    triangle(std::array<vec3f, 3>&& v, std::array<vec3f, 3>&& n)
        : vertices{std::forward<decltype(v)>(v)}
        , normals{std::forward<decltype(n)>(n)} { }

    template <size_t N>
    auto& get() & {
        return vertices[N];
    }
    template <size_t N>
    auto const& get() const& {
        return vertices[N];
    }
    template <size_t N>
    auto&& get() && {
        return std::move(vertices[N]);
    }

    vec3f normal_at(const vec3f& point) const {
        const auto& [v1, v2, v3] = vertices;
        const auto d1            = (v1 - point).norm();
        const auto d2            = (v2 - point).norm();
        const auto d3            = (v3 - point).norm();
        const auto& [n1, n2, n3] = normals;
        const auto n             = (d1 * n1 + d2 * n2 + d3 * n3).normalized();
        return n;
    }
};

// triangle structured bindings with triangle::get<N>
namespace std {
    template <>
    struct tuple_size<triangle> : integral_constant<size_t, 3> { };

    template <int N>
    struct tuple_element<N, triangle> {
        using type = vec3f;
    };
} // namespace std

struct Mesh {
    std::shared_ptr<Material> material;
    std::vector<triangle> triangles;
};

struct Node {
    std::string name;
    std::vector<Mesh> meshes;
    std::vector<Node> children;

    Node() = default;
    Node(const std::string& name_) : name{name_} {}
};
