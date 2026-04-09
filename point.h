#ifndef POINT_H
#define POINT_H

#include <math.h>
#include <stdio.h>

#define X 80
#define Y 25
#define XLEN 4 * M_PI
#define YLEN 2

struct point {
    int x;
    int y;
};

double scaled_x(int x);
int scaled_y(double y);
int is_point(struct point* points, int y, int x);

#endif