#include "camera.hh"

void from_json(const nlohmann::json& j, vec3f& vec) {
    j[0].get_to(vec.x);
    j[1].get_to(vec.y);
    j[2].get_to(vec.z);
}

void from_json(const nlohmann::json& j, Camera& cam) {
    j.at("position").get_to(cam.position);
    j.at("orientation").get_to(cam.orientation);
    j.at("fov").get_to(cam.fov);
    j.at("width").get_to(cam.image_width);
    j.at("height").get_to(cam.image_height);
}
