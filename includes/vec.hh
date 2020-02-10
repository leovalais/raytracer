#pragma once

#include <stdexcept>
#include <compare>

template <typename T>
struct Vec {
    const T x, y, z;

    Vec() = delete;
    Vec(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}
    Vec(T value) : Vec(value, value, value) {}
    Vec(const Vec&)  = default;
    Vec(const Vec&&) = delete;
    Vec& operator=(const Vec&) = default;
    Vec& operator=(const Vec&&) = delete;

    Vec operator+(const Vec& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }
    Vec operator-(const Vec& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }
    Vec operator*(const Vec& other) const {
        return {x * other.x, y * other.y, z * other.z};
    }
    Vec operator/(const Vec& other) const {
        return {x / other.x, y / other.y, z / other.z};
    }
    Vec operator%(const Vec& other) const {
        return {x % other.x, y % other.y, z % other.z};
    }

    bool operator==(const Vec& other) const {
        const auto [xx, yy, zz] = other;
        return x == xx && y == yy && z == zz;
    }
    bool operator!=(const Vec& rhs) const { return !(*this == rhs); }

    /**
     * Cross product.
     */
    Vec operator^(const Vec& other) const {
        const auto [xx, yy, zz] = other;
        return {y * zz - z * yy, z * xx - x * zz, x * yy - y * xx};
    }

    /**
     * Dot product.
     */
    T operator|(const Vec& other) const {
        const auto [xx, yy, zz] = other;
        return x * xx + y * yy + z * zz;
    }

    template <unsigned N>
    T get() const {
        throw std::out_of_range("out of range index in Vec::get");
    }
    template <>
    T get<0>() const {
        return x;
    }
    template <>
    T get<1>() const {
        return y;
    }
    template <>
    T get<2>() const {
        return z;
    }

    T operator[](std::size_t pos) const {
        switch (pos) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::out_of_range("out of range index in Vec::operator[]");
        }
    }
};

using vec3f = Vec<float>;
