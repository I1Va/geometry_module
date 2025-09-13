#include "geometry.hpp"
#include <cfloat>
#include <cmath>
#include <algorithm>
#include <cassert>



// geom_vector3
geom_vector3::geom_vector3(const double x, const double y, const double z): x(x), y(y), z(z), len2(NAN) {};    
geom_vector3::geom_vector3(const double val): x(val), y(val), z(val), len2(NAN) {};

double geom_vector3::get_x() const { return x; };
double geom_vector3::get_y() const { return y; };
double geom_vector3::get_z() const { return z; };
double geom_vector3::get_len2() {
    if (std::isnan(len2))
        len2 = x * x + y * y + z * z;

    return len2;
};

geom_vector3 geom_vector3::operator-(const geom_vector3 &other) {
    len2 = NAN;
    return geom_vector3(x - other.x, y - other.y, z - other.z);
}

geom_vector3 geom_vector3::operator*(const geom_vector3& other) {
    len2 = NAN;
    return geom_vector3(y * other.z - z * other.y,
                        z * other.x - x * other.z,
                        x * other.y - y * other.x);
}

geom_vector3 geom_vector3::operator*(const double scalar) {
    if (len2 != NAN) len2 *= scalar * scalar;

    return geom_vector3(x * scalar, y * scalar, z * scalar);
}

geom_vector3 geom_vector3::operator+(const geom_vector3 &other) {
    len2 = NAN;
    return geom_vector3(x + other.x, y + other.y, z + other.z);
}

geom_vector3 geom_vector3::operator!() {
    double len = std::sqrt(get_len2());
    len2 = NAN;

    return geom_vector3(x / len, y / len, z / len);
}

geom_vector3 geom_vector3::operator+=(const geom_vector3 &other) {
    len2 = NAN;
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

geom_vector3 geom_vector3::operator-=(const geom_vector3 &other) {
    len2 = NAN;
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

geom_vector3 geom_vector3::operator*=(const double scalar) {
    len2 = NAN;
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

double geom_vector3::operator^(const geom_vector3& other) {
    len2 = NAN;
    return x * other.x + y * other.y + z * other.z;
}

geom_vector3 geom_vector3::clamp(const double min, const double max) {
    len2 = NAN;
    return geom_vector3
    (
        std::clamp(x, min, max),
        std::clamp(y, min, max),
        std::clamp(z, min, max)
    );
}

std::ostream& operator<<(std::ostream& stream, const geom_vector3 &vector) {
    stream << "geom_vector3 {" << vector.x << ", " << vector.y << ", " << vector.z << "}\n";
    return stream;
}

geom_vector3 cord_mul(const geom_vector3 &a, const geom_vector3 &b) {
    return geom_vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

geom_vector3 cord_pow(const geom_vector3 &a, const double pow_val) {
    return geom_vector3
    (
        std::pow(a.x, pow_val),
        std::pow(a.y, pow_val),
        std::pow(a.z, pow_val)
    );
}

// geom_sphere3
geom_sphere3::geom_sphere3(const geom_vector3 &center, const double radius): center(center), radius(radius) {}
geom_vector3 geom_sphere3::get_center() const { return center; }
double geom_sphere3::get_radius() const { return radius; }

// general functions:
geom_vector3 get_ortogonal(geom_vector3 &a, geom_vector3 &b) {
    double b_len = std::sqrt(b.get_len2());
    double c = (a ^ b) / (b_len * b_len);
    return a - b * c;
}

// geom_line
geom_line::geom_line(const geom_vector3 &start, const geom_vector3 &direction): start(start), direction(direction) {};
geom_vector3 geom_line::get_start() const { return start; }
geom_vector3 geom_line::get_direction() const { return direction; }



double get_dot_line_distance(geom_line line, geom_vector3 dot) {
    geom_vector3 line_direction = line.get_direction();

    geom_vector3 start_to_dot = dot - line.get_start();
    geom_vector3 cross_product = start_to_dot * line_direction;

    return cross_product.get_len2() / line_direction.get_len2();
}

