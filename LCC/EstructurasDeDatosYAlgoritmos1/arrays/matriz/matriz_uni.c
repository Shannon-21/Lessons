#include "matriz.h"
#include <math.h>
#include <stdio.h>

/*
** Implmentacion utilizando un unico arreglo unidimensional

# ventajas:
  - mantener un solo array se hace mas facil para la reserva y liberacion de memoria
  - tener los datos contiguos es mas rapido para el procesador en los accessos
  - solo realiza dos mallocs para la estrucutura y para el array
  - el tamano total es rows * cols * sizeof(double)

# desventajas:
  - para el acceso a cada valor hay que pensar en dezplamientos planos porque no hay pared que diga donde termina cada fila
*/

struct Matriz_ {
  size_t filas;
  size_t columnas;
  double* data;
};


Matriz* matriz_crear(size_t numFilas, size_t numColumnas) {
  Matriz *m = (Matriz *)malloc(sizeof(Matriz));
  if (m == NULL) return NULL;

  m->filas = numFilas;
  m->columnas = numColumnas;

  m->data = (double *)malloc(numFilas * numColumnas * sizeof(double));
  if (m->data == NULL) return NULL;

  return m;
}

void matriz_destruir(Matriz* matriz) {
  if (matriz == NULL) return;

  matriz->filas = 0;
  matriz->columnas = 0;

  if (matriz->data == NULL) return;
  free(matriz->data);

  free(matriz);
}

double matriz_leer(Matriz* matriz, size_t fil, size_t col) {
  if (matriz == NULL ||
      fil >= matriz_num_filas(matriz) ||
      col >= matriz_num_columnas(matriz))
    return NAN;

  return matriz->data[fil * matriz_num_columnas(matriz) + col];
}

void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val) {
  if (matriz == NULL ||
      fil >= matriz_num_filas(matriz) ||
      col >= matriz_num_columnas(matriz))
    return;

  matriz->data[fil * matriz_num_columnas(matriz) + col] = val;
}

size_t matriz_num_filas(Matriz* matriz) {
  if (matriz == NULL) return NAN;
  return matriz->filas;
}

size_t matriz_num_columnas(Matriz* matriz) {
  if (matriz == NULL) return NAN;
  return matriz->columnas;
}

void matriz_imprimir(Matriz* matriz) {
  if (matriz == NULL) return;

  size_t fils = matriz_num_filas(matriz);
  size_t cols = matriz_num_columnas(matriz);

  for (int i = 0; i < fils; i++) {
    printf("[");

    for (int j = 0; j < cols; j++) {
      printf("%.1f", matriz_leer(matriz, i, j));

      if (j != cols - 1)
        printf(", ");
    }

    printf("]\n");
  }
}

void matriz_intercambiar_filas(Matriz *matriz, size_t fila1, size_t fila2) {
  if (matriz == NULL) return;
  
  size_t num_filas = matriz_num_filas(matriz);
  size_t num_cols = matriz_num_columnas(matriz);
  if (num_filas <= fila1 || num_filas <= fila2 || fila1 == fila2) return;

  /*
  123, 456, 789, 0, 3
    - t=1;  723, 456, 789; 723, 456, 189;
    - t=2;  783, 456, 189; 783, 456, 129;
    - t=3;  789, 456, 129; 783, 456, 123;
  */

  for (size_t i = 0; i < num_cols; i++) {
    double temp = matriz_leer(matriz, fila1, i);

    matriz_escribir(matriz, fila1, i, matriz_leer(matriz, fila2, i));
    matriz_escribir(matriz, fila2, i, temp);
  }
}

void matriz_insertar_fila(Matriz *matriz, size_t posicion, double *fila) {
  
}
