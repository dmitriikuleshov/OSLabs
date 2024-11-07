#include "utils.hpp"


double calculate_area(Point a, Point b, Point c) {
    double abx = b.x - a.x;
    double aby = b.y - a.y;
    double abz = b.z - a.z;
    double acx = c.x - a.x;
    double acy = c.y - a.y;
    double acz = c.z - a.z;

    double cross_x = aby * acz - abz * acy;
    double cross_y = abz * acx - abx * acz;
    double cross_z = abx * acy - aby * acx;

    double area =
        0.5 * sqrt(cross_x * cross_x + cross_y * cross_y + cross_z * cross_z);
    return area;
}


int load_points_from_file(const char *filename, Point *points) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    int count = 0;
    while (fscanf(file, "%lf %lf %lf", &points[count].x, &points[count].y,
                  &points[count].z) == 3) {
        count++;
        if (count >= MAX_POINTS) {
            fprintf(stderr, "Error: too many points in file (max %d)\n",
                    MAX_POINTS);
            break;
        }
    }
    fclose(file);
    return count;
}