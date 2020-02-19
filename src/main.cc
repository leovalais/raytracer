#include <iostream>
#include <fstream>
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
    std::cerr << "Usage: " << argv0 << " SCENE [CAM [OUT_IMAGE]]\n"
              << "\tSCENE: a 3D object that Assimp supports\n"
              << "\tCAM: a .cam file containing all camera-related info (defaults to "
                 "stdin when omitted or equals to -)\n"
              << "\tOUT_IMAGE: the name of the image to render (defaults to out.png)"
              << std::endl;
}

int main(int argc, char** argv) {
    if (argc == 1 or argc > 4) {
        cli_help(argv[0]);
        return 1;
    }
    const auto scene_file = argv[1];
    nlohmann::json j;
    if (argc >= 3 and std::string{argv[2]} != "-")
        std::ifstream{argv[2]} >> j;
    else
        std::cin >> j;
    const auto camera   = j.get<Camera>();
    const auto out_file = argc == 4 ? argv[3] : "out.png";
    std::cout << "Loading scene: " << scene_file << std::endl;
    auto scene = Scene{scene_file};
    std::cout << "... contains " << scene.get_triangles().size() << " triangles"
              << std::endl;
    std::cout << "Rendering scene..." << std::endl;
    const auto image = scene.render(camera);
    std::cout << "Saving it into '" << out_file << "'..." << std::endl;
    image.save(out_file);
    return 0;
}
