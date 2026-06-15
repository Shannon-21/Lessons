#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* direccion;
    int capacidad;    
} ArregloEnteros;

// a)
ArregloEnteros* arreglo_enteros_crear(int capacidad) {
    // we have to return an struct
    ArregloEnteros* res = malloc(sizeof(ArregloEnteros));
    if (res == NULL) return NULL;
    
    // the struct has the defined capacity inside
    res->direccion = malloc(capacidad * sizeof(int));
    if (res->direccion == NULL) {
        free(res);
        return NULL;
    }

    res->capacidad = capacidad;
    return res;
}

// b)
void arreglo_enteros_destruir(ArregloEnteros* arreglo) {
    if (arreglo == NULL) return;
    free(arreglo->direccion);
    free(arreglo);
}

// c)
int arreglo_enteros_leer(ArregloEnteros* arreglo, int pos) {
    if (arreglo == NULL || pos < 0 || pos >= arreglo->capacidad) 
        return -1;

    return arreglo->direccion[pos];
}

// d)
void arreglo_enteros_escribir(ArregloEnteros* arreglo, int pos, int dato) {
    if (arreglo == NULL || pos < 0 || pos >= arreglo->capacidad) 
        return;

    arreglo->direccion[pos] = dato;
}

// e)
int arreglo_enteros_capacidad(ArregloEnteros* arreglo) {
    if (arreglo == NULL) return -1;
    return arreglo->capacidad;
} 

// f)
void arreglo_enteros_imprimir(ArregloEnteros* arreglo) {
    if (arreglo == NULL) return;

    printf("[");
    for (int i = 0; i < arreglo->capacidad; i++) {
        printf("%d", arreglo->direccion[i]);
        
        if (i != arreglo->capacidad - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// 4.a)
void arreglo_enteros_ajustar(ArregloEnteros* arreglo, int capacidad) {
    if (arreglo == NULL || capacidad < 0) return;

    int* tmp = realloc(arreglo->direccion, capacidad * sizeof(int));
    if (tmp == NULL) return;

    arreglo->direccion = tmp;
    arreglo-> capacidad = capacidad;
}

// a.b)
void arreglo_enteros_insertar(ArregloEnteros* arreglo, int pos, int dato) {
    if (arreglo == NULL || pos < 0 || pos > arreglo->capacidad) return;

    int nueva_capacidad = arreglo->capacidad + 1;
    arreglo_enteros_ajustar(arreglo, nueva_capacidad);
    
    // mi solucion inicial inserta desde adelante,
    // asi que siempre termina iterando todos los elementos
    // hasta el final y ademas guardamos variables en memoria
    // intermedias
    
    /*
    int cache = -1;
    for (int i = 0; i < nueva_capacidad; i++) {
        if (i < pos) continue;
        
        if (i == pos) {
            cache = arreglo_enteros_leer(arreglo, i);
            arreglo_enteros_escribir(arreglo, i, dato);
        }
        else {
            int tmp = arreglo_enteros_leer(arreglo, i);
            arreglo_enteros_escribir(arreglo, i, cache);
            cache = tmp;
        }
    } 
    */

    // insertar desde atras es mas claro y efinciente, 
    // mientras mas al fondo, mas rapido inserta 
    // y no hay logica condicional extra al loop
    // solo recorre hasta pos

    // [1, 2], 0, 0:
    //      i=2, vi=2, [1, 2, 2]
    //      i=1, vi=1, [1, 1, 2]
    //    [0, 1, 2]

    // [1, 2], 1, 0:
    //      i=2, vi=2, [1, 2, 2]
    //    [1, 0, 2]

    // [1, 2], 2, 0:
    //    [1, 2, 0]

    for (int i = nueva_capacidad - 1; i > pos; i--) {
        int valor_anterior = arreglo_enteros_leer(arreglo, i - 1);
        arreglo_enteros_escribir(arreglo, i, valor_anterior);
    }

    arreglo_enteros_escribir(arreglo, pos, dato);
}

void arreglo_enteros_eliminar(ArregloEnteros* arreglo, int pos) {
    // look forward until pos. after pos, move posterior to i-1 until final. resize arr
    // O(n). stores cache sicen pos.
    if (arreglo == NULL || pos < 0 || pos >= arreglo->capacidad) return;

    int nueva_capacidad = arreglo->capacidad - 1;
        
    for (int i = pos; i < arreglo->capacidad - 1; i++) {
        int post = arreglo_enteros_leer(arreglo, i+1);
        arreglo_enteros_escribir(arreglo, i, post);
    }

    arreglo_enteros_ajustar(arreglo, nueva_capacidad);
}

int main() {
    int capacidad = 5;
    ArregloEnteros* arreglo = arreglo_enteros_crear(capacidad);

    arreglo_enteros_escribir(arreglo, 0, 1);
    arreglo_enteros_escribir(arreglo, 1, 1);
    arreglo_enteros_escribir(arreglo, 2, 2);
    arreglo_enteros_escribir(arreglo, 3, 3);
    arreglo_enteros_escribir(arreglo, 4, 5);
    arreglo_enteros_escribir(arreglo, 5, 8);

    arreglo_enteros_imprimir(arreglo);

    printf("%d, %d\n", arreglo_enteros_leer(arreglo, 4), arreglo_enteros_leer(arreglo, 5));
    printf("%d\n", arreglo_enteros_capacidad(arreglo));

    capacidad = 4;
    arreglo_enteros_ajustar(arreglo, capacidad);

    arreglo_enteros_imprimir(arreglo);

    printf("%d, %d\n", arreglo_enteros_leer(arreglo, 3), arreglo_enteros_leer(arreglo, 4));
    printf("%d \n", arreglo_enteros_capacidad(arreglo));

    arreglo_enteros_insertar(arreglo, 0, 0);
    arreglo_enteros_imprimir(arreglo);

    arreglo_enteros_insertar(arreglo, 1, 0);
    arreglo_enteros_imprimir(arreglo);
    
    arreglo_enteros_insertar(arreglo, 6, 5);
    arreglo_enteros_imprimir(arreglo);

    arreglo_enteros_eliminar(arreglo, 1);
    arreglo_enteros_imprimir(arreglo);

    arreglo_enteros_eliminar(arreglo, 5);
    arreglo_enteros_imprimir(arreglo);

    arreglo_enteros_eliminar(arreglo, 2);
    arreglo_enteros_imprimir(arreglo);

    printf("%d \n", arreglo_enteros_capacidad(arreglo));

    arreglo_enteros_destruir(arreglo);
    arreglo = NULL;

    printf("empty: %d\n", arreglo == NULL);

    return 0;
}
