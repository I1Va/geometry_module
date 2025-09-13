#include <iostream>
#include <cmath>
#include <algorithm>

#include "gm_vector.hpp"

template<typename T>
gm_vector<T, 3> cord_mul(const gm_vector<T, 3> &a, const gm_vector<T, 3> &b) {
    return geom_vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

gm_vector<double, 3> cord_pow(const gm_vector<double, 3> &a, const double pow_val) {
    return gm_vector<double, 3>
    (
        std::pow(a.x, pow_val),
        std::pow(a.y, pow_val),
        std::pow(a.z, pow_val)
    );
}

gm_vector<double, 3> get_ortogonal(gm_vector<double, 3> a, gm_vector<double, 3> b) {
    double b_len = std::sqrt(b.get_len2());
    double c = (a.dot(b)) / (b_len * b_len);
    return a - b * c;
}


template<typename T>
gm_vector<T, 2>::gm_vector(T x, T y) : x(x), y(y), len2(NAN) {}

template<typename T>
gm_vector<T, 2> gm_vector<T, 2>::operator+(const gm_vector<T, 2> &other) const {
    return gm_vector<T, 2>(x + other.x, y + other.y);
}
template<typename T>
gm_vector<T, 2> gm_vector<T, 2>::operator-(const gm_vector<T, 2> &other) const {
    return gm_vector<T, 2>(x - other.x, y - other.y);
}

template<typename T>
gm_vector<T, 2> gm_vector<T, 2>::operator*(const T scalar) const {
    return gm_vector<T, 2>(x * scalar, y * scalar);
}

template<typename T>
gm_vector<T, 2> gm_vector<T, 2>::operator+=(const gm_vector<T, 2> &other) {
    len2 = NAN;
    x += other.x;
    y += other.y;
    return *this;
}

template<typename T>
gm_vector<T, 2> gm_vector<T, 2>::operator-=(const gm_vector<T, 2> &other) {
    len2 = NAN;
    x -= other.x;
    y -= other.y;
    return *this;
}

template<typename T>
gm_vector<T, 2> gm_vector<T, 2>::operator*=(const T scalar) {
    len2 *= scalar; 
    x *= scalar;
    y *= scalar;
    return *this;
}  

template<typename T>
gm_vector<double, 2> gm_vector<T, 2>::rotate(const double radians) const {
    double x_new = x * std::cos(radians) - y * std::sin(radians);
    double y_new = x * std::sin(radians) + y * std::cos(radians);

    return gm_vector<double, 2>(x_new, y_new);
}

template<typename T>
T gm_vector<T, 2>::dot(const gm_vector<T, 2> &other) const {
    return x * other.x + y * other.y;
}

template<typename T>
T gm_vector<T, 2>::get_len2() {
    if (std::isnan(len2))
        len2 = x * x + y * y;
    return len2;
}

template<typename T>
T gm_vector<T, 2>::get_x() const {
    return x;
}

template<typename T>
T gm_vector<T, 2>::get_y() const {
    return y;
}



template<typename T>
gm_vector<T, 3>::gm_vector(T x, T y, T z) : x(x), y(y), z(z), len2(NAN) {}

template<typename T>
gm_vector<T, 3> gm_vector<T, 3>::operator+(const gm_vector<T, 3> &other) const {
    return gm_vector<T, 3>(x + other.x, y + other.y, z + other.z);
}

template<typename T>
gm_vector<T, 3> gm_vector<T, 3>::operator-(const gm_vector<T, 3> &other) const {
    return gm_vector<T, 3>(x - other.x, y - other.y, z - other.z);
}

template<typename T>
gm_vector<T, 3> gm_vector<T, 3>::operator*(const T scalar) const {
    return gm_vector<T, 3>(x * scalar, y * scalar, z * scalar);
}

template<typename T>
gm_vector<double, 3> gm_vector<T, 3>::operator!() {
    double len = std::sqrt(get_len2());
    len2 = 1.0;
    return geom_vector3(x / len, y / len, z / len);
}

template<typename T>
gm_vector<T, 3> gm_vector<T, 3>::operator+=(const gm_vector<T, 3> &other) {
    len2 = NAN;
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

template<typename T>
gm_vector<T, 3> gm_vector<T, 3>::operator-=(const gm_vector<T, 3> &other) {
    len2 = NAN;
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

template<typename T>
gm_vector<T, 3> gm_vector<T, 3>::operator*=(const T scalar) {
    len2 *= scalar; 
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}  

template<typename T>
T gm_vector<T, 3>::get_len2() {
    if (std::isnan(len2))
        len2 = x * x + y * y + z * z;
    return len2;
}

template<typename T>
T gm_vector<T, 3>::dot(const gm_vector<T, 3> &other) const {
    return x * other.x + y * other.y + z * other.z;
}

template<typename T>
T gm_vector<T, 3>::get_x() const {
        return x;
    }

template<typename T>
T gm_vector<T, 3>::get_y() const {
        return y;
    }   

template<typename T>
T gm_vector<T, 3>::get_z() const {
        return z;
    }

template<typename T>
gm_vector<T, 3> gm_vector<T, 3>::clamp(const T min, const T max) {
    len2 = NAN;
    return gm_vector<T, 3>
    (
        std::clamp(x, min, max),
        std::clamp(y, min, max),
        std::clamp(z, min, max)
    );
}

template<typename T>
std::ostream &operator<<(std::ostream &stream, const gm_vector<T, 3> &vector) {
    stream << "gm_vector3 {" << vector.x << ", " << vector.y << ", " << vector.z << "}\n";
    return stream;
}

