#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main() {
    Matriz* m = matriz_crear(3, 4);

    double val = 1;
    for (size_t i = 0; i < matriz_num_filas(m); i++)
        for (size_t j = 0; j < matriz_num_columnas(m); j++) {
            matriz_escribir(m, i, j, val);
            val++;
        }

    matriz_imprimir(m);
    printf("\n");

    matriz_intercambiar_filas(m, 0 , 2);
    matriz_imprimir(m);
    printf("\n");

    double *fila = (double *)malloc(4 * sizeof(double));
    fila[0] = 70.0; fila[1] = 80.0; fila[2] = 90.0; fila[3] = 100.0;
    matriz_insertar_fila(m, 1, fila);
    matriz_imprimir(m);
    printf("\n");

    matriz_destruir(m);

    return 0;
}