#include "json-serializers.hh"

void from_json(const nlohmann::json& j, vec3f& vec) {
    j[0].get_to(vec.x);
    j[1].get_to(vec.y);
    j[2].get_to(vec.z);
}

void from_json(const nlohmann::json& j, Camera& cam) {
    j.at("position").get_to(cam.position);
    j.at("orientation").get_to(cam.orientation);
    j.at("fov").get_to(cam.fov);
    if (j.contains("focal_length"))
        j.at("focal_length").get_to(cam.focal_length);
}

void from_json(const nlohmann::json& j, Scene& scene) {
    j.at("camera").get_to(scene.camera);
    j.at("width").get_to(scene.image_width);
    j.at("height").get_to(scene.image_height);
    j.at("scene").get_to(scene.filename);
}
