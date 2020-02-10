#include <iostream>
#include "vec.hh"
#include "printers.hh"

int main(int, char**) {
    auto a = vec3f{0, 2, 3};
    auto b = vec3f{1, 8, 7};
    std::cout << a + b + 5.f << ' ' << (a ^ b) << ' ' << (a | b) << std::endl;
    if (vec3f{2} - 2 == 0)
        std::cout << "ok" << std::endl;
}
