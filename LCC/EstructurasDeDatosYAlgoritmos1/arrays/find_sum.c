#include <stdlib.h>
#include <stdio.h>

// find the sum of elements of an array

int contains_int(int *arr, int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }

    return -1;
}

int find_sum(int *arr, const int size, int target, int *idx1, int *idx2) {
    int *seen = calloc(size, sizeof(int));
    if (seen == NULL) {
        return 1;
    }

    for (int i = 0; i < size; i++) {
        int diff = target - arr[i];
        int isin = contains_int(seen, size, diff);
        if (isin != -1) {
            *idx1 = isin;
            *idx2 = i;
            return 0;
        }
        seen[i] = arr[i];
    }

    return 2;
}

int main() {
    int arr[] = { 3, 6, 1, 2, 5, 9, 4 };
    const int n = sizeof(arr) / sizeof(int);

    int target = 8;
    int idx1 = -1;
    int idx2 = -1;

    int result = find_sum(arr, n, target, &idx1, &idx2);
    if (result != 0) {
        printf("error ocurred. code:%d", result);
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("; target:%d ; result:(%d, %d)\n", target, idx1, idx2);

    return 0;
}