#ifndef UTILS_HPP
#define UTILS_HPP

#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_POINTS 1000

typedef struct {
    double x, y, z;
} Point;

typedef struct {
    int p1, p2, p3;
    double area;
} Triangle;

double calculate_area(Point a, Point b, Point c);
int load_points_from_file(const char *filename, Point *points);

#endif // UTILS_HPP
