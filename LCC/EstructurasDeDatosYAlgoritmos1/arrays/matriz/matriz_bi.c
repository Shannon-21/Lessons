#include "matriz.h"
#include <stdio.h>
#include <math.h>

/*
** Implementacion utilizando un arreglo bidimensional (arreglo de punteros a arreglo)

# ventajas:
  - acceso intuitivo [fil][col]

# desventajas:
  - la reserva y liberacion tiene que ser ordeneda por fila al estar contenidas 
  - los malloc por fila pueden alocarse lejos en memoria fisica unas de las otras, y esto empeora el rendimiento en operaciones grandes
  - realiza mas mallocs que puede dejar espacios de memoria entre cada fila vacios inutiliables
  - el tamaño total es rows * cols * sizeof(double) + qty punteros a cada fila
*/

struct Matriz_ {
  size_t filas;
  size_t columnas;
  double **data;
};


Matriz* matriz_crear(size_t numFilas, size_t numColumnas) {
  Matriz *m = (Matriz *)malloc(sizeof(Matriz));
  if (m == NULL) return NULL;
  
  m->filas = numFilas;
  m->columnas = numColumnas;
  
  m->data = (double **)malloc(numFilas * sizeof(double *));
  if (m->data == NULL) return NULL;

  for (size_t i = 0; i < numFilas; i++) {
    m->data[i] = (double *)malloc(numColumnas * sizeof(double));
    if (m->data[i] == NULL) return NULL;
  }

  return m;
}

void matriz_destruir(Matriz* matriz) {
  if (matriz == NULL) return;

  for (size_t i = 0; i < matriz->filas; i++) {
    free(matriz->data[i]);
    matriz->data[i] = NULL;
  }

  free(matriz->data);
  matriz->data = NULL;

  matriz->filas = 0;
  matriz->columnas = 0;

  free(matriz);
}

double matriz_leer(Matriz* matriz, size_t fil, size_t col) {
  if (matriz == NULL || 
      matriz_num_filas(matriz) <= fil || 
      matriz_num_columnas(matriz) <= col) 
    return NAN;

  return matriz->data[fil][col];
}

void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val) {
  if (matriz == NULL || 
      matriz_num_filas(matriz) <= fil || 
      matriz_num_columnas(matriz) <= col) 
    return;

  matriz->data[fil][col] = val;
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

  size_t cols = matriz_num_columnas(matriz);

  for (size_t i = 0; i < matriz_num_filas(matriz); i++) {
    printf("[");
    
    for (size_t j = 0; j < cols; j++) {
      printf("%.1f", matriz_leer(matriz, i, j));

      if (j != cols - 1)
        printf(", ");
    }

    printf("]\n");
  }
}


