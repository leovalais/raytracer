#include "scene.hh"

#include <cassert>
#include <sstream>
#include <stdexcept>
#include "ray.hh"

Scene::Scene() : filename{}, triangles{}, camera{}, image_width{640}, image_height{480} {}

Scene::Scene(const std::string& filename_) : filename(filename_) {
    load();
}

void Scene::load(const std::filesystem::path& directory) {
    Assimp::Importer import;
    const auto scene = import.ReadFile(directory / filename,
                                       aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        auto msg = std::ostringstream{};
        msg << "[ASSIMP ERROR](" << filename << ") " << import.GetErrorString();
        throw std::runtime_error{msg.str()};
    }
    process_node(scene->mRootNode, scene);
}

Image Scene::render() const {
    return render(camera);
}

Image Scene::render(const Camera& camera) const {
    auto img                       = Image{image_width, image_height};
    const auto camera_plane_size   = std::tan(camera.fov / 2);
    const int iw2                  = image_width / 2;
    const int ih2                  = image_height / 2;
    const double cam_plane_x_units = camera_plane_size / iw2;
    const double cam_plane_y_units = camera_plane_size / ih2;
    for (int y = -ih2; y < ih2; ++y)
        for (int x = -iw2; x < iw2; ++x) {
            const auto xy_on_camera_plane = vec3f{
                x * cam_plane_x_units, y * cam_plane_y_units, camera.position.z + 1};
            const auto dir = (xy_on_camera_plane - camera.position).normalized();
            const auto ray = Ray{camera.position, dir};
            for (const auto& triangle : triangles)
                if (auto pt = ray.intersection(triangle)) {
                    img.set_pixel({x + iw2, y + ih2}, RGB{1, 1, 1});
                    break;
                }
        }
    return img;
}

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
