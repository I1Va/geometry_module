#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <cmath>
#include <iostream>

geom_vector3 get_ortogonal(geom_vector3 &a, geom_vector3 &b);
double get_dot_line_distance(geom_line line, geom_vector3 dot);


class geom_vector3 {
    double x, y, z;
    double len2;
public:
    geom_vector3(const double x, const double y, const double z);
    explicit geom_vector3(const double val);
    
    double get_x() const;
    double get_y() const;
    double get_z() const;
    double get_len2(); 

    geom_vector3 operator-(const geom_vector3 &other);
    geom_vector3 operator*(const geom_vector3 &other);
    geom_vector3 operator*(const double scalar);
    geom_vector3 operator+(const geom_vector3 &other);
    geom_vector3 operator!();   
    geom_vector3 operator+=(const geom_vector3 &other);
    geom_vector3 operator-=(const geom_vector3 &other);
    geom_vector3 operator*=(const double scalar);
    double       operator^(const geom_vector3 &other);
    
    
    
    geom_vector3 clamp(const double min, const double max);
    friend std::ostream &operator<<(std::ostream &stream, const geom_vector3 &vector);
    friend geom_vector3 cord_mul(const geom_vector3 &a, const geom_vector3 &b);
    friend geom_vector3 cord_pow(const geom_vector3 &a, const double pow_val);
};

class geom_sphere3 {
    geom_vector3 center;
    double radius;
public:
    geom_sphere3(const geom_vector3 &center, const double radius);
    geom_vector3 get_center() const;
    double get_radius() const;
};


class geom_line {
    geom_vector3 start;
    geom_vector3 direction;
public:
    geom_line(const geom_vector3 &start, const geom_vector3 &direction);
    geom_vector3 get_start() const;
    geom_vector3 get_direction() const;
};


#endif // GEOMETRY_HPP