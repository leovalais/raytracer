#include <iostream>
#include "vec.hh"
#include "printers.hh"
#include "color.hh"
#include "triangle.hh"
#include "ray.hh"

int main(int, char**) {
    auto a = vec3f{0, 2, 3};
    auto b = vec3f{1, 8, 7};
    std::cout << a + b + 5.f << ' ' << (a ^ b) << ' ' << (a | b) << std::endl;
    if (vec3f{2} - 2 == 0)
        std::cout << "ok" << std::endl;
    auto x    = RGB{1.f, 1.f, 0.f};
    ByteRGB y = x;
    std::cout << x << "  " << y << std::endl;
    auto tri       = triangle{{0, {1, 0, 0}, {0.5, 1, 0}}};
    auto [p, q, v] = tri;
    std::cout << p << q << v << std::endl;

    auto ray = Ray<5>{{0.2, 0.2, 1}, {0, 0, -1}};
    auto res = ray.intersection(tri);
    if (res.has_value())
        std::cout << *res << std::endl;
    else
        std::cout << "sad";
}
