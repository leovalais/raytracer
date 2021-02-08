#pragma once

#include <iostream>
#include "vec.hh"
#include "color.hh"

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vec<T>& vec) {
    return out << '(' << vec.x << ' ' << vec.y << ' ' << vec.z << ')';
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Color<T>& col) {
    return out << "rgb(" << +col.r << ", " << +col.g << ", " << +col.b << ')';
}
