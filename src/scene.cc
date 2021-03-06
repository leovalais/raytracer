#include "scene.hh"

#include <cassert>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <limits>
#include <random>
#include "utils.hh"

Scene::Scene()
    : filename{}, root_node{}, camera{}, image_width{640}, image_height{480} { }

Scene::Scene(const std::string& filename_) : filename(filename_) {
    load();
}

Image Scene::render() const {
    return render(camera);
}

Image Scene::render(const Camera& camera) const {
    auto img                     = Image{image_width, image_height};
    const int iw2                = image_width / 2;
    const int ih2                = image_height / 2;
    const double aspect_ratio    = static_cast<double>(image_width) / image_height;
    const auto camera_fov        = std::tan(camera.fov / 2);
    const double viewport_width  = camera_fov;
    const double viewport_height = viewport_width / aspect_ratio;
    const auto viewport_origin
        = camera.position - camera.orientation * camera.focal_length;
    for (int y = -ih2; y < ih2; ++y) {
        const double vp_y = static_cast<double>(y) / (image_height - 1);
        for (int x = -iw2; x < iw2; ++x) {
            const double vp_x = static_cast<double>(x) / (image_width - 1);
            const auto vp_xy  = vec3f{vp_x * viewport_width, vp_y * viewport_height, 0};
            const auto dir = (camera.position - (viewport_origin + vp_xy)).normalized();
            const auto ray = Ray{camera.position, dir};
            if (const auto hit = cast<3>(ray))
                img.set_pixel({image_width - (x + iw2), image_height - (y + ih2)},
                              hit->color);
        }
    }
    return img;
}

template <unsigned N>
std::optional<hit> Scene::cast(const Ray& ray) const {
    // static auto rd          = std::random_device{};
    static auto gen         = std::mt19937{42};
    static auto random_unit = std::uniform_real_distribution<double>(0.0, 1.0);
    const auto& hit         = cast<0>(ray);
    if (not hit)
        return std::nullopt;
    const auto pt     = hit->point();
    const auto normal = hit->triangle.normal_at(pt);
    auto bounce_dir   = vec3f{random_unit(gen), random_unit(gen), random_unit(gen)};
    if ((normal | bounce_dir) < 0.0) // dot product
        bounce_dir = -1.0 * bounce_dir;
    const auto bounce = Ray{pt, bounce_dir};
    if (auto bounce_hit = cast<N - 1>(bounce)) {
        bounce_hit->color = (hit->material->diffuse + bounce_hit->color) / 4;
        return bounce_hit;
    } else
        return hit;
}

template <>
std::optional<hit> Scene::cast<0>(const Ray& ray) const {
    const auto find_intersection = make_y_combinator(
        [&ray](const auto& recurse, const Node& node) -> hit {
            auto h = hit{std::numeric_limits<double>::infinity(), ray};
            std::for_each(node.meshes.begin(), node.meshes.end(), [&](const Mesh& m) {
                std::for_each(m.triangles.begin(), m.triangles.end(), [&](const auto& t) {
                    if (const auto i = ray.intersection(t)) {
                        const auto d = (*i - ray.origin).norm();
                        if (epsilon < d and d < h.distance) {
                            h.distance = d;
                            h.material = m.material;
                            h.triangle = t;
                            h.mesh     = m;
                            h.node     = node;
                        }
                    }
                });
            });
            std::for_each(node.children.begin(), node.children.end(), [&](const auto& n) {
                hit hh = recurse(n);
                if (epsilon < hh.distance and hh.distance < h.distance)
                    h = hh;
            });
            return h;
        });
    auto hit = find_intersection(root_node);
    if (std::numeric_limits<double>::max() < hit.distance) // no hit
        return std::nullopt;
    hit.color = hit.material->diffuse;
    return hit;
}

Node Scene::load_node(const aiNode* ainode,
                      const aiScene* scene,
                      const std::vector<std::shared_ptr<Material>>& materials) {
    auto node = Node{ainode->mName.C_Str()};
    for (unsigned i = 0; i < ainode->mNumMeshes; ++i) {
        auto mesh         = Mesh{};
        const auto aimesh = scene->mMeshes[ainode->mMeshes[i]];
        mesh.material     = materials[aimesh->mMaterialIndex];
        auto vertices     = std::vector<vec3f>{};
        for (unsigned j = 0; j < aimesh->mNumVertices; ++j) {
            const auto& v  = aimesh->mVertices[j];
            const auto vec = vec3f{v.x, v.y, v.z};
            vertices.push_back(vec);
        }
        auto normals = std::vector<vec3f>{};
        if (aimesh->mNormals)
            for (unsigned j = 0; j < aimesh->mNumVertices; j++) {
                const auto& v = aimesh->mNormals[j];
                normals.push_back(vec3f{v.x, v.y, v.z}.normalized());
            }

        for (unsigned j = 0; j < aimesh->mNumFaces; ++j) {
            const auto& face    = aimesh->mFaces[j];
            auto vertex_indices = std::vector<unsigned>{};
            assert(face.mNumIndices == 3); // aiProcess_Triangulate
            for (unsigned k = 0; k < face.mNumIndices; ++k)
                vertex_indices.push_back(face.mIndices[k]);
            auto t = triangle{vertices[vertex_indices[0]],
                              vertices[vertex_indices[1]],
                              vertices[vertex_indices[2]]};
            if (normals.size() > 0)
                t.normals = {normals[vertex_indices[0]],
                             normals[vertex_indices[1]],
                             normals[vertex_indices[2]]};
            mesh.triangles.push_back(t);
        }
        node.meshes.push_back(mesh);
    }
    for (unsigned i = 0; i < ainode->mNumChildren; ++i) {
        auto child = load_node(ainode->mChildren[i], scene, materials);
        node.children.push_back(child);
    }
    return node;
}

static std::vector<std::shared_ptr<Material>>
load_assimp_materials(const aiScene* scene) {
    auto materials = std::vector<std::shared_ptr<Material>>{};
    for (size_t i = 0; i < scene->mNumMaterials; i++) {
        const auto mat = scene->mMaterials[i];
        auto name      = aiString{};
        auto diffuse   = aiColor3D{};
        mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
        mat->Get(AI_MATKEY_NAME, name);
        auto material     = std::make_shared<Material>();
        material->name    = name.C_Str();
        material->diffuse = RGB{diffuse.r, diffuse.g, diffuse.b};
        materials.push_back(material);
    }
    return materials;
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
    const auto materials = load_assimp_materials(scene);
    root_node            = load_node(scene->mRootNode, scene, materials);
}
