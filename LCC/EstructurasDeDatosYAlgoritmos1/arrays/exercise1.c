# include <stdlib.h>
# include <stdio.h>

/* 1. 
La mediana de un arreglo ordenado de n n´umeros se define como el elemento del medio cuando n es
impar y como el promedio de los dos elementos del medio cuando n es par. Por ejemplo,

    mediana([-1.0, 2.2, 2.9, 3.1, 3.5]) = 2.9
    mediana([-1.0, 2.2, 2.9, 3.1]) = 2.55

Escriba una funci´on que reciba un arreglo, no necesariamente ordenado, de n´umeros y calcule su mediana:
    float mediana(float *arreglo, int longitud);

Puede utilizar la siguiente rutina para ordenar un arreglo de menor a mayor
*/

void bubble_sort(float arreglo[], int longitud) {
    for (int iter = 0 ; iter < longitud - 1 ; iter++) {
        for (int i = 0 ; i < longitud - iter - 1; i++) {
            if (arreglo[i] > arreglo[i + 1]) {
                float aux = arreglo[i];
                arreglo[i] = arreglo[i + 1];
                arreglo[i + 1] = aux;
        }
        }
    }
}

void print_arr(float *arreglo, int longitud) {
    printf("[");
    for (int idx = 0; idx < longitud; idx++) {
        if (idx == longitud - 1) {
            printf("%f", arreglo[idx]);
            break;
        }
        printf("%f, ", arreglo[idx]);
    }
    printf("], len:%i\n", longitud);

}

float mediana(float *arreglo, int longitud) {
    bubble_sort(arreglo, longitud);
    print_arr(arreglo, longitud);
    printf("len:%i\n", longitud);

    if (longitud == 0) {
        return -1;
    }
    else if (longitud % 2 == 0) {
        int middleIdxBef = longitud / 2 - 1;
        int middleIdxAft = longitud / 2;
        printf("middleIndexBef:%i, middleIndexAft:%i, len:%i\n", middleIdxBef, middleIdxAft, longitud);
        return (arreglo[middleIdxBef] + arreglo[middleIdxAft]) / 2;
    }
    else {
        int middleIdx = longitud / 2;
        printf("middleIndex:%i, len:%i\n", middleIdx, longitud);
        return arreglo[middleIdx];
    }
}

int main() {
    float arreglo1[5] = {-1.0, 2.9, 2.2, 3.1, 3.5};
    float arreglo2[4] = {-1.0, 2.2, 2.9, 3.1};
    printf("Arr1:%f \nArr2:%f\n", mediana(arreglo1, 4), mediana(arreglo2, 5));
    return 0;
}