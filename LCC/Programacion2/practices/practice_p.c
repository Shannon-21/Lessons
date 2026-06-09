# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct {
    char nombre[20];
    int edad;
    float promedio;
} Alumno;

int n;

Alumno* build_arr() {
    Alumno* arr;
    scanf("%i", &n);
    arr = malloc(sizeof(Alumno)*n);
    if (arr == NULL) {
        printf("Error");
    }
    return arr;
}

void fill_arr(Alumno* arr) {
    for (int i = 0; i < n; i++) {
        char name[20]; scanf("%s", &name);
        int age; scanf("%i", &age);
        float avg; scanf("%f", &avg);

        strcpy((*(arr+i)).nombre, name);
        (*(arr+i)).edad = age;
        (*(arr+i)).promedio = avg;
    }
}

Alumno* best_avg(Alumno* arr, int n) {
    int best_idx = 0;
    float best_p = 0;
    for (int i = 0; i < n; i++) {
        Alumno st = *(arr+i);
        if (st.promedio > best_p) {
            best_idx = i;
            best_p = st.promedio;
        }
    }
    return arr + best_idx;
}

int main() {
    Alumno* arr = build_arr();
    fill_arr(arr);
    Alumno* best = best_avg(arr, n);
    printf("%s, %i, %f\n", best->nombre, best->edad, best->promedio);
    free(arr);
    return 0;
}