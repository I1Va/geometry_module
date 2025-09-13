#ifndef GM_VECTOR_HPP
#define GM_VECTOR_HPP

#include <cmath>
#include <algorithm>
#include <iostream>


// VECTOR
template<typename T, std::size_t N>
class gm_vector {};

template<typename T>
class gm_vector<T, 2> {
    T x, y;
    T len2;
public:
    gm_vector(T x = 0, T y = 0): x(x), y(y), len2(NAN) {}
    explicit gm_vector(T cord): x(cord), y(cord), len2(NAN) {}

    template<typename U, typename = std::enable_if_t<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value>>
    gm_vector(const gm_vector<U, 3>& other):
        x(static_cast<T>(other.x)),
        y(static_cast<T>(other.y)),
        z(static_cast<T>(other.z)),
        len2(static_cast<T>(other.len2)) {};

    gm_vector<T, 2> operator+(const gm_vector<T, 2> &other) const {
        return gm_vector<T, 2>(x + other.x, y + other.y);
    }

    gm_vector<T, 2> operator-(const gm_vector<T, 2> &other) const {
        return gm_vector<T, 2>(x - other.x, y - other.y);
    }

    gm_vector<T, 2> operator*(const T scalar) const {
        return gm_vector<T, 2>(x * scalar, y * scalar);
    }

    gm_vector<T, 2> operator=(const gm_vector<T, 2> &other) {
        x = other.x;
        y = other.y;
        len2 = other.len2;

        return *this;
    }

    gm_vector<T, 2> operator+=(const gm_vector<T, 2> &other) {
        len2 = NAN;
        x += other.x;
        y += other.y;
        return *this;
    }

    gm_vector<T, 2> operator-=(const gm_vector<T, 2> &other) {
        len2 = NAN;
        x -= other.x;
        y -= other.y;
        return *this;
    }

    gm_vector<T, 2> operator*=(const T scalar) {
         len2 *= scalar; 
        x *= scalar;
        y *= scalar;
        return *this;   
    }

    gm_vector<T, 3> to_3d() const { return gm_vector<T, 3>(x, y, 0); }

    gm_vector<double, 2> rotate(const double radians) const {
        double x_new = x * std::cos(radians) - y * std::sin(radians);
        double y_new = x * std::sin(radians) + y * std::cos(radians);

        return gm_vector<double, 2>(x_new, y_new);
    }

    T scalar_product(const gm_vector<T, 2> &other) const {
         return x * other.x + y * other.y;
    }

    inline T get_len2() {
        if (std::isnan(len2))
            len2 = x * x + y * y;
        return len2;
    }

    inline T get_x() const { return x; }
    inline T get_y() const { return y; }
};

template<typename T>
class gm_vector<T, 3> {
    T x, y, z;
    T len2;
public:
    gm_vector(T x = 0, T y = 0, T z = 0): x(x), y(y), z(z), len2(NAN) {}
    explicit gm_vector(T cord): x(cord), y(cord), z(cord), len2(NAN) {}

    template<typename U, typename = std::enable_if_t<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value>>
    gm_vector(const gm_vector<U, 3>& other):
        x(static_cast<T>(other.x)),
        y(static_cast<T>(other.y)),
        z(static_cast<T>(other.z)),
        len2(static_cast<T>(other.len2)) {};


    gm_vector<T, 3> operator+(const gm_vector<T, 3> &other) const { 
        return gm_vector<T, 3>(x + other.x, y + other.y, z + other.z);
    }

    gm_vector<T, 3> operator-(const gm_vector<T, 3> &other) const {
        return gm_vector<T, 3>(x - other.x, y - other.y, z - other.z);
    }

    gm_vector<T, 3> operator*(const T scalar) const {
        return gm_vector<T, 3>(x * scalar, y * scalar, z * scalar);
    }

    gm_vector<double, 3> operator!() {
        double len = std::sqrt(get_len2());
        len2 = 1.0;
        return gm_vector<T, 3>(x / len, y / len, z / len);
    }

    gm_vector<double, 3> operator=(const gm_vector<T, 3> &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        len2 = other.len2;
        return *this;
    }

    gm_vector<T, 3> operator+=(const gm_vector<T, 3> &other) {
        len2 = NAN;
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    gm_vector<T, 3> operator-=(const gm_vector<T, 3> &other) {
        len2 = NAN;
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    gm_vector<T, 3> operator*=(const T scalar) {
        len2 *= scalar; 
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    inline T get_len2() {
        if (std::isnan(len2))
            len2 = x * x + y * y + z * z;
        return len2;
    }

    T scalar_product(const gm_vector<T, 3> &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    inline T get_x() const { return x;}
    inline T get_y() const { return y;}
    inline T get_z() const { return z;}

    gm_vector<T, 3> clamp(const T min, const T max) {
        len2 = NAN;
        return gm_vector<T, 3>
        (
            std::clamp(x, min, max),
            std::clamp(y, min, max),
            std::clamp(z, min, max)
        );
    }

    

    template<typename U>
    friend inline std::ostream &operator<<(std::ostream &stream, const gm_vector<U, 3> &vector);

    template<typename U>
    friend inline gm_vector<U, 3> cord_mul(const gm_vector<U, 3> &a, const gm_vector<U, 3> &b);

    template<typename U>
    friend inline gm_vector<double, 3> cord_pow(const gm_vector<double, 3> &a, const double pow_val);

    friend inline gm_vector<double, 3> cord_pow(const gm_vector<double, 3> &a, const double pow_val);
};


template<typename T>
inline std::ostream &operator<<(std::ostream &stream, const gm_vector<T, 3> &vector) {
    stream << "gm_vector3 {" << vector.x << ", " << vector.y << ", " << vector.z << "}\n";
    return stream;
}

template<typename T>
inline gm_vector<T, 3> cord_mul(const gm_vector<T, 3> &a, const gm_vector<T, 3> &b) {
    return gm_vector<T, 3>(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline gm_vector<double, 3> cord_pow(const gm_vector<double, 3> &a, const double pow_val) {
     return gm_vector<double, 3>
    (
        std::pow(a.x, pow_val),
        std::pow(a.y, pow_val),
        std::pow(a.z, pow_val)
    );
}

inline gm_vector<double, 3> get_ortogonal(gm_vector<double, 3> a, gm_vector<double, 3> b) {
    double b_len = std::sqrt(b.get_len2());
    double c = (a.scalar_product(b)) / (b_len * b_len);
    return a - b * c;
}



// LINE
template<typename T, std::size_t N>
class gm_line {};

template<>
class gm_line<double, 3> {
    gm_vector<double, 3> start;
    gm_vector<double, 3> direction;
public:
    gm_line(gm_vector<double, 3> start, gm_vector<double, 3> direction):
        start(start), direction(direction) {}
    
    gm_vector<double, 3> get_start() const { return start; }
    gm_vector<double, 3> get_direction() const { return direction; }

    friend double get_dot_line_distance(gm_line<double, 3> line, gm_vector<double, 3> dot);
};



// SPHERE
template<typename T, std::size_t N>
class gm_sphere {};

template<>
class gm_sphere<double, 3> {
    gm_vector<double, 3> center;
    double radius;
public:
    gm_sphere(gm_vector<double, 3> center, double radius);
    gm_vector<double, 3> get_center() const { return center; }
    double get_radius() const { return radius; }
};



// GENERAL FUNCTIONS
inline double get_dot_line_distance(gm_line<double, 3> line, gm_vector<double, 3> dot) {
    gm_vector<double, 3> line_direction = line.direction;

    gm_vector<double, 3> start_to_dot = dot - line.start;
    gm_vector<double, 3> cross_product = start_to_dot.scalar_product(line_direction);

    return cross_product.get_len2() / line_direction.get_len2();
}

#endif // GM_VECTOR_HPP