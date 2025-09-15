#ifndef GM_VECTOR_HPP
#define GM_VECTOR_HPP

#include <cmath>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <type_traits>

// VECTOR

template<typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;

template<arithmetic T, std::size_t N>  
class gm_vector {};

template<typename T>
class gm_vector<T, 2> {
    T x, y;
    T len2;
    bool valid_len2_state;
    bool poison_state;
public:
    gm_vector(T x = 0, T y = 0): x(x), y(y), valid_len2_state(false), poison_state(false) {}
    explicit gm_vector(T cord): x(cord), y(cord), valid_len2_state(false), poison_state(false) {}

    template<arithmetic U>
    gm_vector(const gm_vector<U, 2>& other):
        x(static_cast<T>(other.get_x())),
        y(static_cast<T>(other.get_y())),
        valid_len2_state(other.get_valid_len2_state()),
        poison_state(other.get_poison_state()),
        len2(other.get_len2()) {}

    bool is_valid() const {
        if (valid_len2_state)
            return (x * x + y * y == len2);
        if (!poison_state && (std::isnan(x) || std::isnan(y)))
            return false;
        
        return true;
    }

    static gm_vector<T, 3> POISON() {
        gm_vector<T, 3> poison_vector(0, 0);
        poison_vector.poison_state = true;

        return poison_vector;
    }

    gm_vector<T, 2> operator+(const gm_vector<T, 2> &other) const {
        assert(is_valid());
        return gm_vector<T, 2>(x + other.x, y + other.y);
    }

    gm_vector<T, 2> operator-(const gm_vector<T, 2> &other) const {
        assert(is_valid());
        return gm_vector<T, 2>(x - other.x, y - other.y);
    }

    gm_vector<T, 2> operator*(const T scalar) const {
        assert(is_valid());
        return gm_vector<T, 2>(x * scalar, y * scalar);
    }

    gm_vector<T, 2> operator=(const gm_vector<T, 2> &other) {
        assert(is_valid());

        x = other.x;
        y = other.y;
        len2 = other.len2;
        poison_state = other.poison_state;
        valid_len2_state = other.valid_len2_state;

        return *this;
    }

    bool operator==(const gm_vector<T, 2> &other) const {
        assert(is_valid());

        return  (x == other.x) &&
                (y == other.y);
    }

    gm_vector<T, 2> operator+=(const gm_vector<T, 2> &other) {
        assert(is_valid());

        valid_len2_state = false;
        x += other.x;
        y += other.y;
        return *this;
    }

    gm_vector<T, 2> operator-=(const gm_vector<T, 2> &other) {
        assert(is_valid());

        valid_len2_state = false;
        x -= other.x;
        y -= other.y;
        return *this;
    }

    gm_vector<T, 2> operator*=(const T scalar) {
        assert(is_valid());

        valid_len2_state = false;
        x *= scalar;
        y *= scalar;
        return *this;   
    }

    gm_vector<T, 3> to_3d() const {
        assert(is_valid());
        return gm_vector<T, 3>(x, y, 0); 
    }

    gm_vector<double, 2> rotate(const double radians) const {
        assert(is_valid());

        double x_new = x * std::cos(radians) - y * std::sin(radians);
        double y_new = x * std::sin(radians) + y * std::cos(radians);

        return gm_vector<double, 2>(x_new, y_new);
    }

    T scalar_product(const gm_vector<T, 2> &other) const {
        assert(is_valid());
        assert(other.is_valid());
        return x * other.x + y * other.y;
    }

    inline T get_len2() {
        assert(is_valid());

        if (valid_len2_state) {
            len2 = x * x + y * y;
            valid_len2_state = true;
        }

        return len2;
    }

    inline T get_x() const { 
        assert(is_valid());
        return x; 
    }

    inline T get_y() const {
        assert(is_valid());
        return y; 
    }

    inline bool get_valid_len2_state() const {
        assert(is_valid());
        return valid_len2_state; 
    }

    inline bool get_poison_state() const { 
        assert(is_valid());
        return poison_state; 
    }

};

template<typename T>
class gm_vector<T, 3> {
    T x, y, z;
    T len2;
    bool valid_len2_state;
    bool poison_state;

public:
    gm_vector(T x = 0, T y = 0, T z = 0): x(x), y(y), z(z), valid_len2_state(false), poison_state(false) {}
    explicit gm_vector(T cord): x(cord), y(cord), z(cord), valid_len2_state(false), poison_state(false) {}

    template<arithmetic U>
    gm_vector(const gm_vector<U, 3>& other):
        x(static_cast<T>(other.get_x())),
        y(static_cast<T>(other.get_y())),
        z(static_cast<T>(other.get_z())),
        valid_len2_state(other.get_valid_len2_state()),
        poison_state(other.get_poison_state()) {};

    bool is_valid() const {
        if (valid_len2_state)
            return (x * x + y * y + z * z) == len2;
        if (!poison_state && (std::isnan(x) || std::isnan(y) || std::isnan(z)))
            return false;
        
        return true;
    }

    static gm_vector<T, 3> POISON() {
        gm_vector<T, 3> poison_vector(0, 0, 0);
        poison_vector.poison_state = true;

        return poison_vector;
    }

    bool is_poison() const { return poison_state; }

    gm_vector<T, 3> operator+(const gm_vector<T, 3> &other) const {
        assert(is_valid());

        return gm_vector<T, 3>(x + other.x, y + other.y, z + other.z);
    }

    gm_vector<T, 3> operator-(const gm_vector<T, 3> &other) const {
        assert(is_valid());

        return gm_vector<T, 3>(x - other.x, y - other.y, z - other.z);
    }

    gm_vector<T, 3> operator*(const T scalar) const {
        assert(is_valid());

        return gm_vector<T, 3>(x * scalar, y * scalar, z * scalar);
    }

    gm_vector<double, 3> operator!() {
        assert(is_valid());

        double len = std::sqrt(get_len2());
        len2 = 1.0;
        return gm_vector<T, 3>(x / len, y / len, z / len);
    }

    gm_vector<double, 3> operator=(const gm_vector<T, 3> &other) {
        assert(is_valid());

        x = other.x;
        y = other.y;
        z = other.z;
        len2 = other.len2;
        poison_state = other.poison_state;
        valid_len2_state = other.valid_len2_state;
        return *this;
    }

    bool operator==(const gm_vector<T, 3> &other) const {
        assert(is_valid());

        return  (x == other.x) &&
                (y == other.y) &&
                (z == other.z);
    }

    gm_vector<T, 3> operator+=(const gm_vector<T, 3> &other) {
        assert(is_valid());

        valid_len2_state = false;
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    gm_vector<T, 3> operator-=(const gm_vector<T, 3> &other) {
        assert(is_valid());

        valid_len2_state = false;
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    gm_vector<T, 3> operator*=(const T scalar) {
        assert(is_valid());

        valid_len2_state = false;
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    inline T get_len2() {
        assert(is_valid());

        if (!valid_len2_state) {
            valid_len2_state = true;
            len2 = x * x + y * y + z * z;
        }
            
        return len2;
    }

    T scalar_product(const gm_vector<T, 3> &other) const {
        assert(is_valid());
        assert(other.is_valid());

        return x * other.x + y * other.y + z * other.z;
    }

    gm_vector<T, 3> vector_product(const gm_vector<T, 3> &other) const {
        assert(is_valid());
        assert(other.is_valid());
        
        return gm_vector<T, 3> (y * other.z - z * other.y,
                                z * other.x - x * other.z,
                                x * other.y - y * other.x);
    }

    template<arithmetic U>
    gm_vector<U, 3> set_len(U new_len) {
        assert(is_valid());
    
        U prev_len = std::sqrt(get_len2());
        x = x / prev_len * new_len;
        y = y / prev_len * new_len;
        z = z / prev_len * new_len;
        len2 = new_len * new_len;

        return *this;
    }

    gm_vector<T, 3> clamp(const T min, const T max) {
        assert(is_valid());

        valid_len2_state = false;
        return gm_vector<T, 3>
        (
            std::clamp(x, min, max),
            std::clamp(y, min, max),
            std::clamp(z, min, max)
        );
    }

    inline T get_x() const { 
        assert(is_valid());
        return x;
    }

    inline T get_y() const {
        assert(is_valid());
        return y;
    }
    inline T get_z() const { 
        assert(is_valid());
        return z;
    }
    inline bool get_valid_len2_state() const {
        assert(is_valid());
        return valid_len2_state; 
    }

    inline bool get_poison_state() const { 
        assert(is_valid());
        return poison_state; 
    }



   
    template<typename U>
    friend inline std::ostream &operator<<(std::ostream &stream, const gm_vector<U, 3> &vector);

    template<typename U>
    friend inline gm_vector<U, 3> cord_mul(const gm_vector<U, 3> &a, const gm_vector<U, 3> &b);

    friend inline gm_vector<double, 3> cord_pow(const gm_vector<double, 3> &a, const double pow_val);
};


template<typename T>
inline std::ostream &operator<<(std::ostream &stream, const gm_vector<T, 3> &vector) {
    assert(vector.is_valid());

    stream << "gm_vector3 {" << vector.x << ", " << vector.y << ", " << vector.z << "}\n";
    return stream;
}

template<typename T>
inline gm_vector<T, 3> cord_mul(const gm_vector<T, 3> &a, const gm_vector<T, 3> &b) {
    assert(a.is_valid());
    assert(b.is_valid());

    return gm_vector<T, 3>(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline gm_vector<double, 3> cord_pow(const gm_vector<double, 3> &a, const double pow_val) {
    assert(a.is_valid());

    return gm_vector<double, 3>
    (
        std::pow(a.x, pow_val),
        std::pow(a.y, pow_val),
        std::pow(a.z, pow_val)
    );
}

inline gm_vector<double, 3> get_ortogonal(gm_vector<double, 3> a, gm_vector<double, 3> b) {
    assert(a.is_valid());
    assert(b.is_valid());

    double b_len2 = b.get_len2();
    double c = (a.scalar_product(b)) / b_len2;
    return a - b * c;
}



// LINE
template<arithmetic T, std::size_t N>
class gm_line {};

template<>
class gm_line<double, 3> {
    gm_vector<double, 3> start;
    gm_vector<double, 3> direction;
public:
    gm_line(const gm_vector<double, 3> &start, const gm_vector<double, 3> &direction):
        start(start), direction(direction) {}
    
    bool is_valid() const { return start.is_valid() && direction.is_valid(); }

    gm_vector<double, 3> get_start() const { 
        assert(is_valid());
        return start; 
    }

    gm_vector<double, 3> get_direction() const { 
        assert(is_valid());
        return direction; 
    }

    friend double get_dot_line_distance2(gm_line<double, 3> line, gm_vector<double, 3> dot);
};



// SPHERE
template<arithmetic T, std::size_t N>
class gm_sphere {};

template<>
class gm_sphere<double, 3> {
    gm_vector<double, 3> center;
    double radius;
public:
    gm_sphere(const gm_vector<double, 3> &center, const double radius): center(center), radius(radius) {};

    double get_distance2_to_line(const gm_line<double, 3> &ray) const {
        return get_dot_line_distance2(ray, center);
    }

    gm_vector<double, 3> get_closest_intersection(const gm_line<double, 3> &ray) const {
        double sphere_ray_distance2 = get_distance2_to_line(ray);

        double radius2 = radius * radius;
        gm_vector<double, 3> ray_start_to_center = center - ray.get_start();

        
        if ((sphere_ray_distance2 > radius2) || ((center - ray.get_start()).scalar_product(ray.get_direction()) < 0))
            return gm_vector<double, 3>::POISON();

        if (sphere_ray_distance2 == radius2) return ray_start_to_center.get_len2() - radius2;
        
        
        double ray_start_to_center_projection_len = std::sqrt(ray_start_to_center.get_len2() - sphere_ray_distance2);
        double radius_projection = std::sqrt(radius2 - sphere_ray_distance2);
        double distance = ray_start_to_center_projection_len - radius_projection;
        
        gm_vector<double, 3> closest_intersection_direction = ray.get_direction().set_len(distance);

        return ray.get_start() + closest_intersection_direction;
    }

    gm_vector<double, 3> get_center() const { return center; }
    double get_radius() const { return radius; }
};



// GENERAL FUNCTIONS
double get_dot_line_distance2(gm_line<double, 3> line, gm_vector<double, 3> dot);

#endif // GM_VECTOR_HPP