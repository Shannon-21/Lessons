#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>
#include <stdbool.h>

typedef void (*FuncionVisitante) (int dato);

typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Determina si la lista es vacía.
 */
int slist_vacia(SList lista);

/**
 * Agrega un elemento al final de la lista.
 */
SList slist_agregar_final(SList lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_recorrer(SList lista, FuncionVisitante visit);

/**
 * Lee la longitud de la lista
 */
int slist_longitud(SList lista);

/**
 * devuelve la concatenacion de dos listas, modificando la primera
 */
void slist_concatenar(SList lista1, SList lista2);

/**
 * inserta un dato en una lista en una posicion arbitraria
 */
SList slist_insertar(SList lista, size_t posicion, int dato);

/**
 * eliminar un dato en una lista en una posicion arbitraria
 */
SList slist_eliminar(SList lista, size_t posicion);

/**
 * determina si un elemento esta en una lista dada
 */
bool slist_contiene(SList lista, int dato);

/**
 * devuelve la posicion de la primera ocurrencia de un elemento si el mismo
 * esta en la lista dada, y -1 en caso de que no este
 */
size_t slist_indice(SList list, int dato);

#endif /* __SLIST_H__ */
