#include <iostream>
#include <fstream>
#include <string>
#include "vec.hh"
#include "printers.hh"
#include "color.hh"
#include "triangle.hh"
#include "ray.hh"
#include "scene.hh"
#include "json-serializers.hh"

void cli_help(char* argv0) {
    std::cerr << "Usage: " << argv0 << " SCENE [OUT_IMAGE]\n"
              << "\tSCENE: a JSON file describing the scene to render (defaults to stdin"
                 "when equals '-')\n"
              << "\tOUT_IMAGE: the name of the image to render (defaults to out.png)"
              << std::endl;
}

int main(int argc, char** argv) {
    if (argc == 1 or argc > 3) {
        cli_help(argv[0]);
        return 1;
    }
    const auto scene_file = std::filesystem::path{argv[1]};
    nlohmann::json j;
    if (scene_file != "-")
        std::ifstream{scene_file} >> j;
    else
        std::cin >> j;
    auto scene          = j.get<Scene>();
    const auto out_file = argc == 3 ? argv[2] : "out.png";
    std::cout << "Loading scene: " << scene_file << std::endl;
    scene.load(scene_file.parent_path());
    std::cout << "... contains " << scene.get_triangles().size() << " triangles"
              << std::endl;
    std::cout << "Rendering scene..." << std::endl;
    const auto image = scene.render();
    std::cout << "Saving it into '" << out_file << "'..." << std::endl;
    image.save(out_file);
    return 0;
}
