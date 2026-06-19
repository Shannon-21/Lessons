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

void matriz_intercambiar_filas(Matriz *matriz, size_t fila1, size_t fila2) {
  if (matriz == NULL) return;
  
  size_t num_filas = matriz_num_filas(matriz);
  size_t num_cols = matriz_num_columnas(matriz);
  if (num_filas <= fila1 || num_filas <= fila2 || fila1 == fila2) return;

  /* implementacion correcta pero ineficiente porque copia todos los datos de cada fila 
     y alloca una fila nueva temporal
  double *cache = (double *)malloc(sizeof(double) * num_cols);
  if (cache == NULL) return;

  for (size_t i = 0; i < num_cols; i++) {
    double val = matriz_leer(matriz, fila1, i);
    cache[i] = val;
  }

  for (size_t i = 0; i < num_cols; i++) {
    double val = matriz_leer(matriz, fila2, i);
    matriz_escribir(matriz, fila1, i, val);
  }

  for (size_t i = 0; i < num_cols; i++) {
    double val = cache[i];
    matriz_escribir(matriz, fila2, i, val);
  }

  free(cache);
  */

  // esta es mas eficiente porque solo reapunta punteros, no toca ningun valor
  double *temp = matriz->data[fila1];
  matriz->data[fila1] = matriz->data[fila2];
  matriz->data[fila2] = temp;
}

void matriz_insertar_fila(Matriz *matriz, size_t posicion, double *fila) {
  
}


