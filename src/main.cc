#include <iostream>
#include <string>
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
    std::cout << "Loading scene: " << scene_file << std::endl;
    auto scene = Scene{scene_file};
    std::cout << "Rendering scene..." << std::endl;
}
