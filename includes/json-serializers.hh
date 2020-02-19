#pragma once

#include <json.hpp>
#include "camera.hh"
#include "vec.hh"
#include "scene.hh"

void from_json(const nlohmann::json& j, vec3f& vec);
void from_json(const nlohmann::json& j, Camera& cam);
void from_json(const nlohmann::json& j, Scene& scene);
