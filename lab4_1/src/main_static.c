// File: test1.c
#include "lib1.h"
#include <math.h>
#include <stdio.h>

// Подключение библиотеки (например, libvariant1)
// float FloatDerivative(float A, float deltaX);
// void BubbleSort(int *array, int size);

int main() {
    printf("Testing static linking...\n");

    // Производная
    float result = FloatDerivative(1.0f, 0.001f);
    printf("FloatDerivative(1.0, 0.001) = %f\n", result);

    // Сортировка
    int array[] = {5, 3, 8, 4, 1};
    int size = sizeof(array) / sizeof(array[0]);
    BubbleSort(array, size);
    printf("Sorted array: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
