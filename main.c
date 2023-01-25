#include <stdio.h>
#include <math.h>

#include "declarations.h"

int main(void) {
    const Elipse elipse = {4, 1, 10};
    Point start_point = {0.0, 10.1};
    Point end_point = {1.4, -9.6};
    Line l = create_line_p2(&start_point, &end_point);
    const double error = 100000.0;

    unsigned int count = 0;
    while (end_point.x >= 0.01 || end_point.x <= -0.01) {
        printf("-- Iteration: %d --\n", count);
        Line t = find_tangent(&elipse, &end_point);
        print_line(&l);
        print_line(&t);
        double al = get_angle(&l);
        double at = get_angle(&t);
        print_angle_d(&al);
        print_angle_d(&at);
        double ar = reflected_angle(&at, &al);
        print_angle_d(&ar);
        double g = get_gradient(&ar);
        l = create_line_pg(&end_point, &g);
        start_point = end_point;
        Point temp_1 = find_next(&elipse, &l, -1),
            temp_2 = find_next(&elipse, &l, +1);
        //print_point(&temp_1);
        //print_point(&temp_2);
        if (compare_points(start_point, temp_1, error))
            end_point = temp_2;
        else
            end_point = temp_1;
        print_point(&end_point);
        printf("\n");
        count++;
    }

    return 0;
}