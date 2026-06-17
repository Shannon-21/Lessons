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
