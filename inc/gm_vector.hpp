#ifndef GM_VECTOR_HPP
#define GM_VECTOR_HPP

#include <cmath>
#include <iostream>

// VECTOR
template<typename T, std::size_t N>
class gm_vector {};

template<typename T>
class gm_vector<T, 2> {
    T x, y;
    T len2;
public:
    gm_vector(T x = 0, T y = 0);
    gm_vector<T, 2> operator+(const gm_vector<T, 2> &other) const;
    gm_vector<T, 2> operator-(const gm_vector<T, 2> &other) const;
    gm_vector<T, 2> operator*(const T scalar) const;
    gm_vector<T, 2> operator+=(const gm_vector<T, 2> &other);
    gm_vector<T, 2> operator-=(const gm_vector<T, 2> &other);
    gm_vector<T, 2> operator*=(const T scalar);
    gm_vector<double, 2> rotate(const double radians) const;
    T dot(const gm_vector<T, 2> &other) const;
    T get_len2();
    T get_x() const;
    T get_y() const;
};

template<typename T>
class gm_vector<T, 3> {
    T x, y, z;
    T len2;
public:
    gm_vector(T x = 0, T y = 0, T z = 0);
    gm_vector<T, 3> operator+(const gm_vector<T, 3> &other) const;
    gm_vector<T, 3> operator-(const gm_vector<T, 3> &other) const;
    gm_vector<T, 3> operator*(const T scalar) const;
    gm_vector<double, 3> operator!();
    gm_vector<T, 3> operator+=(const gm_vector<T, 3> &other);
    gm_vector<T, 3> operator-=(const gm_vector<T, 3> &other);
    gm_vector<T, 3> operator*=(const T scalar);
    T get_len2();
    T dot(const gm_vector<T, 3> &other) const;
    T get_x() const;  
    T get_y() const;
    T get_z() const; 
    gm_vector<T, 3> clamp(const T min, const T max);

    friend gm_vector<double, 3> cord_pow(const gm_vector<double, 3> &a, const double pow_val);
    gm_vector<T, 3> cord_mul(const gm_vector<T, 3> &a, const gm_vector<T, 3> &b);
};

template<typename T>
std::ostream &operator<<(std::ostream &stream, const gm_vector<T, 3> &vector);

template<typename T>
gm_vector<T, 3> cord_mul(const gm_vector<T, 3> &a, const gm_vector<T, 3> &b);

gm_vector<double, 3> cord_pow(const gm_vector<double, 3> &a, const double pow_val);
gm_vector<double, 3> get_ortogonal(gm_vector<double, 3> a, gm_vector<double, 3> b);


// LINE
template<typename T, std::size_t N>
class gm_line {};

template<>
class gm_line<double, 3> {
    gm_vector<double, 3> start;
    gm_vector<double, 3> direction;
public:
    gm_line(gm_vector<double, 3> start, gm_vector<double, 3> direction);
    gm_vector<double, 3> get_start() const;
    gm_vector<double, 3> get_direction() const;

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
    gm_vector<double, 3> get_center() const;
    double get_radius() const;
};


// GENERAL FUNCTIONS
double get_dot_line_distance(gm_line<double, 3> line, gm_vector<double, 3> dot);


#endif // GM_VECTOR_HPP