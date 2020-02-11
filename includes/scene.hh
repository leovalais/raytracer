#pragma once

#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "triangle.hh"

class Scene {
public:
    Scene(const std::string& filename);

private:
    void process_node(const aiNode* node, const aiScene* scene);

private:
    std::string filename_;
    std::vector<triangle> triangles_;
};
