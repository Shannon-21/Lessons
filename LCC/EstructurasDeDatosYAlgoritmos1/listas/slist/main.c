#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int main(int argc, char *argv[]) {

  SList lista = slist_crear();

  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_inicio(lista, 2);
  lista = slist_agregar_inicio(lista, 1);
  lista = slist_agregar_final(lista, 4);

  SList lista2 = slist_crear();

  lista2 = slist_agregar_inicio(lista2, 5);
  lista2 = slist_agregar_inicio(lista2, 4);
  lista2 = slist_agregar_inicio(lista2, 3);

  slist_recorrer(lista, imprimir_entero);
  puts("");

  slist_recorrer(lista2, imprimir_entero);
  puts("");

  slist_concatenar(lista, lista2);
  slist_recorrer(lista, imprimir_entero);
  puts("");

  lista = slist_insertar(lista, 0, 0);
  lista = slist_insertar(lista, 5, 5);
  lista = slist_insertar(lista, 9, 6);
  slist_recorrer(lista, imprimir_entero);
  puts("");

  lista = slist_eliminar(lista, 6);
  lista = slist_eliminar(lista, 6);
  lista = slist_eliminar(lista, 6);
  slist_recorrer(lista, imprimir_entero);
  puts("");

  slist_destruir(lista);

  return 0;
}
