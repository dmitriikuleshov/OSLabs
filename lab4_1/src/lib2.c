#include "lib2.h"

float FloatDerivative(float A, float deltaX) {
    return (cos(A + deltaX) - cos(A - deltaX)) / (2 * deltaX);
}

void QuickSort(int *array, int left, int right) {
    if (left < right) {
        int pivot = array[right];
        int i = left - 1;
        for (int j = left; j < right; ++j) {
            if (array[j] < pivot) {
                ++i;
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        int temp = array[i + 1];
        array[i + 1] = array[right];
        array[right] = temp;

        QuickSort(array, left, i);
        QuickSort(array, i + 2, right);
    }
}