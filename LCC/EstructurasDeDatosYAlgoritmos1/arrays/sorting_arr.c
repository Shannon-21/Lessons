#include <stdlib.h> 
#include <stdio.h> 

int comp(const void* a, const void* b) {
    // qsort: - a is before b; 0 keep a and b; + a is after b
    int ar = *(int*)a, br = *(int*)b;
    return br - ar;
}

int main() {
    int arr[] = { 3, 6, 1, 2, 5, 9, 4 };
    int n = sizeof(arr) / sizeof(int);

    qsort(arr, n, sizeof(int), comp);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

