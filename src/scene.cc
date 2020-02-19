#include "scene.hh"

#include <cassert>
#include <sstream>
#include <stdexcept>

Scene::Scene(const std::string& filename_) : filename(filename_) {
    Assimp::Importer import;
    const auto scene
        = import.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        auto msg = std::ostringstream{};
        msg << "[ASSIMP ERROR](" << filename << ") " << import.GetErrorString();
        throw std::runtime_error{msg.str()};
    }
    process_node(scene->mRootNode, scene);
}

Image Scene::render(const Camera& camera) const {
    auto img = Image{camera.image_width, camera.image_height};
    for (unsigned x = 0; x < camera.image_width; ++x)
        for (unsigned y = 0; y < camera.image_height; ++y)
            img.set_pixel({x, y}, RGB{0.f, 0.f, 1.f});
    return img;
};

void Scene::process_node(const aiNode* node, const aiScene* scene) {
    for (unsigned i = 0; i < node->mNumMeshes; ++i) {
        const auto mesh = scene->mMeshes[node->mMeshes[i]];
        auto vertices   = std::vector<vec3f>{};
        for (unsigned j = 0; j < mesh->mNumVertices; ++j) {
            const auto& v  = mesh->mVertices[j];
            const auto vec = vec3f{v.x, v.y, v.z};
            vertices.push_back(vec);
        }
        for (unsigned j = 0; j < mesh->mNumFaces; ++j) {
            const auto& face    = mesh->mFaces[j];
            auto vertex_indices = std::vector<unsigned>{};
            for (unsigned k = 0; k < face.mNumIndices; ++k)
                vertex_indices.push_back(face.mIndices[k]);
            assert(vertex_indices.size() == 3);
            triangles.push_back(triangle{vertices[vertex_indices[0]],
                                         vertices[vertex_indices[1]],
                                         vertices[vertex_indices[2]]});
        }
    }
    for (unsigned i = 0; i < node->mNumChildren; ++i)
        process_node(node->mChildren[i], scene);
}
