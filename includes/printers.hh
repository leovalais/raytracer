#pragma once

#include <iostream>

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vec<T>& vec) {
    return out << '(' << vec.x << ' ' << vec.y << ' ' << vec.z << ')';
}
