#include <iostream>
#include <cmath>
#include <algorithm>

#include "gm_primitives.hpp"


double get_dot_line_distance2(gm_line<double, 3> line, gm_vector<double, 3> point) {
    gm_vector<double, 3> line_direction = line.get_direction();

    gm_vector<double, 3> start_to_dot = point - line.get_start();
    gm_vector<double, 3> vector_product_res = start_to_dot.vector_product(line_direction);

    return vector_product_res.get_len2() / line_direction.get_len2();
}

double get_dot_line_distance2(gm_line<double, 2> line, gm_vector<double, 2> point) {
    gm_vector<double, 2> line_direction = line.get_direction();

    gm_vector<double, 2> start_to_dot = point - line.get_start();
    double vector_product_res = start_to_dot.vector_product(line_direction);

    return std::fabs(vector_product_res) / line_direction.get_len2();
}


gm_vector<double, 2> get_lines_intersection(const gm_line<double, 2> &line_a, const gm_line<double, 2> &line_b) {
    double x1 = line_a.get_start().get_x();
    double y1 = line_a.get_start().get_y();
    double x2 = line_b.get_start().get_x();
    double y2 = line_b.get_start().get_y();
    double dx1 = line_a.get_direction().get_x();
    double dy1 = line_a.get_direction().get_y();
    double dx2 = line_b.get_direction().get_x();
    double dy2 = line_b.get_direction().get_y();

    double det = dx1 * dy2 - dy1 * dx2;

    if (det == 0) return gm_vector<double, 2>::POISON();

    double t = ((x2 - x1) * dy2 - (y2 - y1) * dx2) / det;
    
    gm_vector<double, 2> intersection = line_a.get_start() + line_a.get_direction() * t;

    return intersection;
}

gm_vector<double, 2> get_ray_line_intersection(const gm_line<double, 2> &ray, const gm_line<double, 2> &line) {
    gm_vector<double, 2> intersection = get_lines_intersection(ray, line);
    
    gm_vector<double, 2> intersection_direction = intersection - ray.get_start();
    if ((ray.get_start() + ray.get_direction()).scalar_product(intersection_direction) > 0)
        return intersection;

    return gm_vector<double, 2>::POISON();
}

void solveQuadratic(double a, double b, double c, double* x1, double* x2, int* n_roots) {
    assert(n_roots);
    assert(x1);
    assert(x2);

    double d = b * b - 4 * a * c;

    if (std::fabs(d) < std::numeric_limits<double>::epsilon()) {
        *n_roots = 1;
        *x1 = -b / (2 * a);
        *x2 = 0;
        return;
    }

    if (d < 0) {
        *n_roots = 0;
        *x1 = *x2 = 0;
        return;
    }
    
    *n_roots = 2;
    *x1 = (-b - std::sqrt(d)) / (2 * a);
    *x2 = (-b + std::sqrt(d)) / (2 * a);
}

