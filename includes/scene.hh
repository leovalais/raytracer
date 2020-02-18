#pragma once

#include <string>
#include <vector>
#include <memory>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <FreeImage.h>
#include "triangle.hh"
#include "image.hh"

class Scene {
public:
    Scene(const std::string& filename);
    Image render() const;

private:
    void process_node(const aiNode* node, const aiScene* scene);

private:
    std::string filename_;
    std::vector<triangle> triangles_;
};
