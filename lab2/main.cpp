#include "utils.hpp"

int max_threads;
int num_points = 0;
Point points[MAX_POINTS];
pthread_mutex_t max_area_mutex;
Triangle max_triangle = {0, 1, 2, 0.0};


void *FindMaxAreaTriangle(void *arg) {
    int start = *(int *)arg;

    Triangle local_max_triangle = {0, 1, 2, 0.0};
    for (int i = start; i < num_points - 2; i += max_threads) {
        for (int j = i + 1; j < num_points - 1; j++) {
            for (int k = j + 1; k < num_points; k++) {
                double area = CalculateArea(points[i], points[j], points[k]);
                if (area > local_max_triangle.area) {
                    local_max_triangle.area = area;
                    local_max_triangle.p1 = i;
                    local_max_triangle.p2 = j;
                    local_max_triangle.p3 = k;
                }
            }
        }
    }

    pthread_mutex_lock(&max_area_mutex);
    if (local_max_triangle.area > max_triangle.area) {
        max_triangle = local_max_triangle;
    }
    pthread_mutex_unlock(&max_area_mutex);

    pthread_exit(NULL);
}

void HandleProcesses(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <file_path> <max_threads>\n", argv[0]);
        exit(1);
    }

    const char *file_path = argv[1];
    max_threads = atoi(argv[2]);

    // Loading points from file
    num_points = LoadPointsFromFile(file_path, points);
    if (num_points <= 0) {
        fprintf(stderr, "Error: could not load points from filen\n");
        exit(1);
    }

    if (num_points < 3) {
        fprintf(stderr, "Error: Too few points for triangle (< 3)\n");
        exit(1);
    }

    // Initializing mutex
    pthread_mutex_init(&max_area_mutex, NULL);

    // Dynamic memory allocation for threads and thread indices
    pthread_t *threads = (pthread_t *)malloc(max_threads * sizeof(pthread_t));
    int *thread_indices = (int *)malloc(max_threads * sizeof(int));

    for (int i = 0; i < max_threads; i++) {
        thread_indices[i] = i;
        if (pthread_create(&threads[i], NULL, find_max_area_triangle,
                           &thread_indices[i]) != 0) {
            perror("Error: error when trying to create a thread\n");
            exit(1);
        };
        pthread_create(&threads[i], NULL, FindMaxAreaTriangle,
                       &thread_indices[i]);


    // Waiting for all threads to finish
    for (int i = 0; i < max_threads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Error: error waiting for thread to finish.");
            exit(1);
        };
    }

    // Cleaning up resources
    free(threads);
    free(thread_indices);
    pthread_mutex_destroy(&max_area_mutex);
}

void PrintResult() {
    printf("Point 1: (%.2f, %.2f, %.2f)\n", points[max_triangle.p1].x,
           points[max_triangle.p1].y, points[max_triangle.p1].z);
    printf("Point 2: (%.2f, %.2f, %.2f)\n", points[max_triangle.p2].x,
           points[max_triangle.p2].y, points[max_triangle.p2].z);
    printf("Point 3: (%.2f, %.2f, %.2f)\n", points[max_triangle.p3].x,
           points[max_triangle.p3].y, points[max_triangle.p3].z);
    printf("Maximum area: %.2f\n", max_triangle.area);
}

int main(int argc, char *argv[]) {
    HandleProcesses(argc, argv);
    PrintResult();
    return 0;
}
