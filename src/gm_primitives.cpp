#include <iostream>
#include <cmath>
#include <algorithm>

#include "gm_primitives.hpp"


double get_dot_line_distance2(gm_line<double, 3> line, gm_vector<double, 3> point) {
    gm_vector<double, 3> line_direction = line.direction;

    gm_vector<double, 3> start_to_dot = point - line.start;
    gm_vector<double, 3> vector_product_res = start_to_dot.vector_product(line_direction);

    return vector_product_res.get_len2() / line_direction.get_len2();
}

