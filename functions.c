#include <stdio.h>
#include <math.h>

#include "declarations.h"

void print_elipse(const Elipse* e) {
    printf ("Elipse: %lfx^2 + %lfy^2 = %lf\n",
        pow(e->scale_x, 2),
        pow(e->scale_y, 2),
        e->radius
    );
}

void print_point(const Point* p) {
    printf ("(%lf, %lf)\n",
        p->x,
        p->y
    );
}

void print_line(const Line* l) {
    if (l->interscept < 0)
        printf("y = %lfx - %lf\n",
            l->gradient,
            -l->interscept
        );
    else
        printf ("y = %lfx + %lf\n",
            l->gradient,
            l->interscept
        );
}

void print_angle_r(const double* angle) {
    printf ("%lf radians\n",
        *angle
    );
}

void print_angle_d(const double* angle) {
    printf ("%lf degrees\n",
        *angle / (2 * M_PI) * 360
    );
}

Line create_line_p2(const Point* p1, const Point* p2) {
    //m = dy / dx
    //y = mx + c where p1 is on the line somewhere
    //p1 = (a, b) so b = ma + c -> c = b - ma
    double gradient = (p2->y - p1->y) / (p2->x - p1->x);
    Line tempLine = {
        gradient,
        p1->y - gradient * p1->x
    };
    return tempLine;
}

Line create_line_pg(const Point* point, const double* gradient) {
    //(x1, y1), y = mx + c
    //y1 = mx1 + c, c = y1 - mx1
    Line tempLine = {
        *gradient,
        point->y - *gradient * point->x
    };
    return tempLine;
}

Point find_next(const Elipse* elipse, const Line* line, const int minus) {
    const double a = elipse->scale_x, b = elipse->scale_y, c = line->interscept, m = line->gradient,
        r2 = pow(elipse->radius, 2), m2 = pow(m, 2), s = minus * sqrt(a*r2 + b*m2*r2 - a*b*pow(c, 2)),
        x = (-b*c*m + s) / (a + b*m2), y = m * x + c;
    Point tempPoint = {x, y};
    return tempPoint;
}

Line find_tangent(const Elipse* elipse, const Point* point) {
    const double a2 = 1 / elipse->scale_x,
        b2 = 1 / elipse->scale_y,
        r2 = pow(elipse->radius, 2),
        x1 = point->x,
        y1 = point->y,
        m = -(b2 * x1) / (y1 * a2),
        c = b2 * r2 / y1;
    Line tempLine = {m, c};
    return tempLine;
}

double get_angle(const Line* line) {
    double val = atan(1 / line->gradient);
    return (val < 0 ? val + M_PI * 2 : (val < M_PI * 2 ? val : val - M_PI * 2));
}

double get_gradient(const double* angle) {
    return 1 / tan(*angle);
}

double reflected_angle(const double* tangent_angle, const double* line_angle) {
    double val = M_PI + *tangent_angle * 2 - *line_angle;
    return (val < 0 ? val + M_PI * 2 : (val < M_PI * 2 ? val : val - M_PI * 2));
}

int compare_points(Point p1, Point p2, const double error) {
    p1.x = floor(p1.x * error) / error;
    p1.y = floor(p1.y * error) / error;
    p2.x = floor(p2.x * error) / error;
    p2.y = floor(p2.y * error) / error;
    return ((p1.x == p2.x && p1.y == p2.y)? 1 : 0);
}