#include <stdlib.h>
#include <stdio.h>

void map_multiply(float *arr, int size, const float multiplier) {
    for (int i = 0; i < size; i++) {
        printf("%f * %f", arr[i], multiplier);
        arr[i] = arr[i] * multiplier;
        printf(" = %f\n", arr[i]);
    }
}

int main() {
    float arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    const float multiplier = 5;

    map_multiply(arr, size, multiplier);

    for (int i = 0; i < size; i++) {
        printf("%f, ", arr[i]);
    }

    return 0;
}