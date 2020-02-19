#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>
#include "vec.hh"
#include "printers.hh"
#include "color.hh"
#include "triangle.hh"
#include "ray.hh"
#include "scene.hh"

void cli_help(char* argv0) {
    std::cerr << "Usage: " << argv0 << " SCENE" << std::endl;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cli_help(argv[0]);
        return 1;
    }
    const auto scene_file = std::string{argv[1]};
    const auto out_file   = "out.png";
    std::cout << "Loading scene: " << scene_file << std::endl;
    auto scene = Scene{scene_file};
    std::cout << "... contains " << scene.get_triangles().size() << " triangles"
              << std::endl;
    std::cout << "Rendering scene..." << std::endl;
    const auto camera = Camera{{0, 0, -10}, {0, 0, 1}, M_PI / 4, 640, 480};
    const auto image  = scene.render(camera);
    std::cout << "Saving it into '" << out_file << "'..." << std::endl;
    image.save(out_file);
    return 0;
}
