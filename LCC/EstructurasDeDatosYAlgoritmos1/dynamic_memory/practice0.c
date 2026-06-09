# include <stdlib.h>
# include <stdio.h>

void set_first(int arr[]) {
    arr[0] = 0;
}

void set_in(int *ptr) {
    *ptr = *ptr == 0 ? 1 : 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

char *get_new_line(void) {
    char *line = malloc(100);
    if (line == NULL) {
        return NULL; // Handle memory allocation failure
    }
    printf("Enter a line of text: ");
    fgets(line, 100, stdin);
    return line;
}

void free_line() {
    char *line = malloc(100);
    if (line == NULL) {
        return; // Handle memory allocation failure    
    }
    free(line);
    free(line); // This is incorrect, it will cause a double free error. Only free once.
}

int add_one(int x) {
    return x + 1;
}

int apply(int (*func)(int), int *x) {
    return func(*x);
}

void apply_in(int (*func)(int), int *x) {
    *x = func(*x);
}

typedef void (*VisitorFunc)(int);

void recorre(VisitorFunc func, int arr[], int size) {
    for (int i = 0; i < size; i++) {
        func(arr[i]);
    }
}

void print_element(int element) {
    printf("%d ", element);
}

// Quede en el 8, continuar con el 9

int main() {
    // int arr[5] = {1, 2, 3, 4, 5};
    // set_first(arr);
    // printf("First element of arr: %d\n", arr[0]);

    // int value = 0;
    // set_in(&value);
    // printf("Value after set_in: %d\n", value);

    // int a = 10, b = 20;
    // swap(&a, &b);
    // printf("After swap: a = %d, b = %d\n", a, b);

    // char *line = get_new_line();
    // if (line != NULL) {
    //     printf("You entered: %s", line);
    //     free(line); // Free the allocated memory
    // }

    // free_line();

    // int x = 5;
    // int result = apply(add_one, &x);
    // printf("Result: %d, x: %d\n", result, x);

    // apply_in(add_one, &x);
    // printf("After apply_in: x = %d\n", x);

    // int arr[] = {1, 2, 3, 4, 5};
    // recorre(print_element, arr, 5);

    return 0;
}