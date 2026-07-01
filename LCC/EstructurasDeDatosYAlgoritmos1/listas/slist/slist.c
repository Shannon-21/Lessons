#include "slist.h"
#include <stdlib.h>

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL || slist_longitud(lista) == 0;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  if (nuevoNodo == NULL) return lista;
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (slist_vacia(lista))
    return nuevoNodo;

  SList nodo = lista;
  for (; nodo->sig != NULL; nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  if (nuevoNodo == NULL) return lista;
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  if (slist_vacia(lista)) return;

  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

int slist_longitud(SList lista) {
  int size = 0;

  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    size++;

  return size;
}

void slist_concatenar(SList lista1, SList lista2) {
  if (slist_vacia(lista1)) {
    lista1 = lista2;
    return;
  }
  else if (slist_vacia(lista2))
    return;
  
  for (SNodo *nodo = lista1; nodo != NULL; nodo = nodo->sig) {
    if (nodo->sig == NULL) {
      nodo->sig = lista2;
      break;
    }
  }
}

SList slist_insertar(SList lista, size_t posicion, int dato) {
  if (slist_vacia(lista) || posicion < 0 || slist_longitud(lista) < posicion) 
    return lista;

  if (posicion == 0)
    return slist_agregar_inicio(lista, dato);

  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  if (nuevoNodo == NULL) return lista;
  nuevoNodo->dato = dato;
  
  SNodo *corte = lista;
  for (int i = 1; i < posicion; i++)
    corte = corte->sig;

  nuevoNodo->sig = corte->sig;
  corte->sig = nuevoNodo; 

  return lista;
}

SList slist_eliminar(SList lista, size_t posicion) {
  if (slist_vacia(lista) || posicion < 0 || slist_longitud(lista) <= posicion) 
    return lista;

  if (posicion == 0) {
    SNodo *nodoEliminar = lista;
    lista = lista->sig;
    free(nodoEliminar);
    return lista;
  }
  
  SNodo *corte = lista;
  for (int i = 1; i < posicion; i++)
    corte = corte->sig;
  
  SNodo *nodoEliminar = corte->sig;
  corte->sig = nodoEliminar->sig;
  free(nodoEliminar);

  return lista;
}

bool slist_contiene(SList lista, int dato) {
  if (slist_vacia(lista)) return false;

  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    if (nodo->dato == dato)
      return true;

  return false;
}

size_t slist_indice(SList lista, int dato) {
  if (slist_vacia(lista)) return -1;

  SNodo *nodo = lista;
  for (int i = 0; i < slist_longitud(lista); i++) {
    if (nodo->dato == dato)
      return i;
    
    nodo = nodo->sig;
  }

  return -1;
}

