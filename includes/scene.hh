#pragma once

#include <string>
#include <vector>
#include <memory>
#include <filesystem>
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
    Scene();
    Scene(const std::string& filename_);
    void load(const std::filesystem::path& directory = "");
    Image render() const;
    Image render(const Camera& camera) const;
    const std::vector<triangle>& get_triangles() const { return triangles; }

private:
    void process_node(const aiNode* node, const aiScene* scene);
    friend void from_json(const nlohmann::json& j, Scene& scene);

private:
    std::filesystem::path filename;
    std::vector<triangle> triangles;
    Camera camera;
    unsigned image_width, image_height;
};
