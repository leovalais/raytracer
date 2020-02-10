#include <iostream>
#include "vec.hh"
#include "printers.hh"
#include "color.hh"

int main(int, char**) {
    auto a = vec3f{0, 2, 3};
    auto b = vec3f{1, 8, 7};
    std::cout << a + b + 5.f << ' ' << (a ^ b) << ' ' << (a | b) << std::endl;
    if (vec3f{2} - 2 == 0)
        std::cout << "ok" << std::endl;
    auto x    = RGB{1.f, 1.f, 0.f};
    ByteRGB y = x;
    std::cout << x << "  " << y << std::endl;
}
