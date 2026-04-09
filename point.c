#include "point.h"

double scaled_x(int x) { return (double)x / 80 * XLEN; }

int scaled_y(double y) { return (int)round((1.0 - y) * (Y - 1) / 2.0); }

int is_point(struct point* points, int y, int x) {
    if (x < 0 || x >= X || y < 0 || y >= Y) return 0;
    for (int i = 0; i < X; i++) {
        if (points[i].x == x && points[i].y == y) {
            return 1;
        }
    }
    return 0;
}
