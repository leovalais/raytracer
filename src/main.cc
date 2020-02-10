#include <iostream>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "vec.hh"
#include "printers.hh"
#include "color.hh"
#include "triangle.hh"
#include "ray.hh"

void cli_help(char* argv0) {
    std::cerr << "Usage: " << argv0 << " SCENE" << std::endl;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cli_help(argv[0]);
        return 1;
    }
    const auto scene_file = std::string{argv[1]};
    auto a                = vec3f{0, 2, 3};
    auto b                = vec3f{1, 8, 7};
    std::cout << a + b + 5.f << ' ' << (a ^ b) << ' ' << (a | b) << std::endl;
    if (vec3f{2} - 2 == 0)
        std::cout << "ok" << std::endl;
    auto x    = RGB{1.f, 1.f, 0.f};
    ByteRGB y = x;
    std::cout << x << "  " << y << std::endl;
    auto tri       = triangle{{0, {1, 0, 0}, {0.5, 1, 0}}};
    auto [p, q, v] = tri;
    std::cout << p << q << v << std::endl;

    auto ray = Ray<5>{{0.2, 0.2, 1}, {0, 0, -1}};
    auto res = ray.intersection(tri);
    if (res.has_value())
        std::cout << *res << std::endl;
    else
        std::cout << "sad";
    Assimp::Importer import;
    const auto scene
        = import.ReadFile(scene_file, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return 1;
    }
    std::cout << "okay :)" << std::endl;
    std::cout << "#meshes = " << scene->mNumMeshes << std::endl;
    std::cout << "#materials = " << scene->mNumMaterials << std::endl;
}
