#pragma once

#include <string>
#include <vector>
#include <memory>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <FreeImage.h>
#include <json.hpp>
#include "triangle.hh"
#include "image.hh"
#include "camera.hh"

class Scene {
public:
    Scene(const std::string& filename_);
    Image render(const Camera& camera) const;
    const std::vector<triangle>& get_triangles() const { return triangles; }

private:
    void process_node(const aiNode* node, const aiScene* scene);

private:
    std::string filename;
    std::vector<triangle> triangles;
};
