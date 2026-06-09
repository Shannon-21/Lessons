#include <stdio.h>

int is_even(int value) {
    return value % 2 == 0;
}

int main() {
    int even = 8;
    int odd = 3;
    int zero = 0;
    int neg_even = -6;

    printf("%d, %d, %d, %d", is_even(even), is_even(odd), is_even(zero), is_even(neg_even));
}