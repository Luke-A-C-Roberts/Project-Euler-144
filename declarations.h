typedef struct elipse_t { double scale_x, scale_y, radius; } Elipse;
typedef struct point_t  { double x, y; } Point;
typedef struct line_t   { double gradient, interscept; } Line;

void print_elipse(const Elipse*);
void print_point(const Point*);
void print_line(const Line*);
void print_angle_r(const double*);
void print_angle_d(const double*);

Line create_line_p2(const Point*, const Point*);
Line create_line_pg(const Point*, const double* gradient);
Line find_tangent(const Elipse*, const Point*);

Point find_next(const Elipse*, const Line*, const int);

double get_angle(const Line*);
double get_gradient(const double*);
double reflected_angle(const double*, const double*);

int compare_points(Point, Point, const double);