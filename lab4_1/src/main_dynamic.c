#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h> // Для atoi
#include <string.h> // Для strtok

typedef float (*FloatDerivativeFunc)(float, float);
typedef void (*SortFunc)(int *, int);

int main() {
    void *libHandle1 = dlopen("./build/lib1.so", RTLD_LAZY);
    void *libHandle2 = dlopen("./build/lib2.so", RTLD_LAZY);

    if (!libHandle1 || !libHandle2) {
        fprintf(stderr, "Failed to load libraries\n");
        return 1;
    }

    FloatDerivativeFunc FloatDerivative1 =
        (FloatDerivativeFunc)dlsym(libHandle1, "FloatDerivative");
    SortFunc Sort1 = (SortFunc)dlsym(libHandle1, "BubbleSort");

    FloatDerivativeFunc FloatDerivative2 =
        (FloatDerivativeFunc)dlsym(libHandle2, "FloatDerivative");
    SortFunc Sort2 = (SortFunc)dlsym(libHandle2, "QuickSort");

    int useVariant = 1; // Начинаем с первой библиотеки
    char command[256];
    while (1) {
        printf("Enter command: ");
        fgets(command, sizeof(command), stdin);

        if (command[0] == '0') {
            useVariant = 3 - useVariant; // Переключение 1 -> 2, 2 -> 1
            printf("Switched to library %d\n", useVariant);
        } else if (command[0] == '1') {
            float A, deltaX;
            sscanf(command + 2, "%f %f", &A, &deltaX);
            float result = (useVariant == 1 ? FloatDerivative1(A, deltaX)
                                            : FloatDerivative2(A, deltaX));
            printf("Result: %f\n", result);
        } else if (command[0] == '2') {
            int array[100], size = 0;
            char *token = strtok(command + 2, " ");
            while (token) {
                array[size++] = atoi(token);
                token = strtok(NULL, " ");
            }
            if (useVariant == 1) {
                Sort1(array, size);
            } else {
                Sort2(array, size);
            }
            printf("Sorted array: ");
            for (int i = 0; i < size; ++i) {
                printf("%d ", array[i]);
            }
            printf("\n");
        }
    }

    dlclose(libHandle1);
    dlclose(libHandle2);
    return 0;
}
