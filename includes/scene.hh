#pragma once

#include <string>
#include <vector>
#include <memory>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <FreeImage.h>
#include "triangle.hh"

struct FIBITMAPDeleter {
    void operator()(FIBITMAP* bitmap) { FreeImage_Unload(bitmap); }
};

class Scene {
public:
    using image = std::unique_ptr<FIBITMAP, FIBITMAPDeleter>;
    Scene(const std::string& filename);
    image render() const;

private:
    void process_node(const aiNode* node, const aiScene* scene);

private:
    std::string filename_;
    std::vector<triangle> triangles_;
};
