#include "lib1.h"

float FloatDerivative(float A, float deltaX) {
    return (cos(A + deltaX) - cos(A)) / deltaX;
}

void BubbleSort(int *array, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}