#pragma once

#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include <optional>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <FreeImage.h>
#include <json.hpp>
#include "triangle.hh"
#include "image.hh"
#include "camera.hh"
#include "ray.hh"

class Scene {
public:
    Scene();
    Scene(const std::string& filename_);
    void load(const std::filesystem::path& directory = "");
    Image render() const;
    Image render(const Camera& camera) const;
    const Node& get_root_node() const { return root_node; }

    std::optional<RGB> cast(const Ray& ray) const;

private:
    Node load_node(const aiNode* node,
                   const aiScene* scene,
                   const std::vector<std::shared_ptr<Material>>& materials);
    friend void from_json(const nlohmann::json& j, Scene& scene);

private:
    std::filesystem::path filename;
    Node root_node;
    Camera camera;
    unsigned image_width, image_height;
};
