#pragma once

#include <array>
#include <vector>
#include <memory>
#include "vec.hh"
#include "material.hh"

using triangle = std::array<vec3f, 3>;

struct Mesh {
    std::shared_ptr<Material> material;
    std::vector<triangle> triangles;
};

struct Node {
    std::vector<Mesh> meshes;
    std::vector<Node> children;
};
