#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void locales() {
    int local_x = 5;
    char* local_c = "Hello";
    printf("%p %d\n", &local_x, local_x);
    printf("\n%p %p\n", &local_c, &local_c[0]);
    for (int i = 0; i < 5; i++)
        printf("-%p %c\n", &local_c[i], local_c[i]);
}

void setserosero(int arr[]) {
    arr[0] = 0;
}

void setin(int *ptr) {
    *ptr = *ptr != 0 ? 1 : 0;
}

void swap(int *one, int *two) {
    int valone = *one;
    int valtwo = *two;
    *one = valtwo;
    *two = valone;
}

char* getnewline(void) {
    char* ptr = malloc(sizeof(char)*100);
    fgets(ptr, 100, stdin);

    return ptr;
}

void free_error() {
    char* ptr = malloc(100);
    free(ptr);
    free(ptr);
}

int main1() {
    // locales();

    // int arr[] = {1, 2, 3};
    // setserosero(arr);
    // for (int i = 0; i < 3; i++)
    //     printf("%i,", arr[i]);

    // int x = 4, y = 0;
    // int* ptr1 = &x;
    // int* ptr2 = &y;
    // setin(ptr1);
    // setin(ptr2);
    // printf("%i,", *ptr1);
    // printf("%i,", *ptr2);

    // swap(ptr1, ptr2);
    // printf("%i, %i", *ptr1, *ptr2);

    // printf("%s\n", getnewline());

    // free_error();
}

int apply(int (*f)(int), int x) {
    return f(x);
}

int int_sqrt(int x) {
    return x * (1.0/2.0);
}

void sqr(int* x) {
    *x *= *x;
}

void applyin(int (*f)(int), int* ptr) {
    *ptr = f(*ptr);
}

typedef void (*VisitorFunc)(int);

void recorre(VisitorFunc f, int arr[], int len) {
    for (int i = 0; i < len; i++) {
        f(arr[i]);
    }
}

void imprimir(int n) {
    printf("%d \n", n);
}

int main2() {
    // printf("%i\n", apply(int_sqrt, 16));

    // int x = 16;
    // int* ptrx = &x;
    // applyin(int_sqrt, ptrx);
    // printf("%i\n", *ptrx);

    int arr[] = {1, 2, 3, 4, 5};
    VisitorFunc f = imprimir;
    recorre(f, arr, 5);

    return 0;
}

void nullify(int* a) {
    a = NULL;
}

int main3() {
    int a[67];
    a[0] = 123;
    printf("%d\n", a[0]);
    nullify(a);
    printf("%d\n", a[0]);
    return 0;
}

int main4() {
    char ptr1[10] = "hola mundo";
    ptr1[0] = 's';
    printf("%s\n", ptr1);
    
    char* ptr2 = "hola mundo";
    ptr2[0] = 's';
    printf("%s\n", ptr2);
    return 0;
}

typedef struct {
    int numero;
    char* palo;
} Carta;

void crear_cartas(Carta* mazo) {
    int idx = 0;
    for (int p = 0; p < 4; p++) {
        for (int i = 1; i < 13; i++) {
            Carta carta;
            carta.numero = i;
            switch (p)
            {
                case 0:
                    carta.palo = "oro";
                    break;
                case 1:
                    carta.palo = "basto";
                    break;
                case 2:
                    carta.palo = "copa";
                    break;
                case 3:
                    carta.palo = "espada";
                    break;
            }
            mazo[idx] = carta;
            idx++;
        }
    }
}

Carta azar(Carta mazo[], int len) {
    int random = (rand() % (len -1 - 0 + 1)) + 0;
    printf("%i\n", random);
    return mazo[random];
}

int main6() {
    Carta mazo[48];
    crear_cartas(mazo);

    srand(time(NULL));

    Carta n = azar(mazo, 48);
    printf("(%i, %s)\n", n.numero, n.palo);
    
}

struct Contacto {
    char* nombre;
    char* telefono;
    unsigned int edad;
};

struct Agenda
{
    struct Contacto* contactos;
    int counter;
};

struct Contacto crear_contacto() {
    struct Contacto new;
    new.nombre = malloc(50);
    new.telefono = malloc(20);
    scanf("%49s %19s %u", new.nombre, new.telefono, &new.edad);
    return new;
}

void actualizar_edad(struct Contacto* c) {
    unsigned int edad;
    scanf("%u", &edad);
    c->edad = edad;
}

void alta_contacto(struct Agenda *agenda) {
    struct Contacto c = crear_contacto();
    agenda->contactos[agenda->counter] = c;
    agenda->counter++;
}

void imprimir_contactos(struct Agenda *agenda) {
    for (int i = 0; i < agenda->counter; i++) {
        struct Contacto n = agenda->contactos[i];
        printf("-(%s, %s, %u)\n", n.nombre, n.telefono, n.edad);
    }
}

void agregar_agenda(struct Agenda agenda[], int qty) {
    for (int i = 0; i < qty; i++) {
        alta_contacto(agenda);
    }

    imprimir_contactos(agenda);
}

void modificar_edad_por_nombre(struct Agenda *agenda) {
    char nombre[50];
    scanf("%49s", &nombre);

    for (int i = 0; i < agenda->counter; i++) {
        if (strcmp(nombre, agenda->contactos[i].nombre) == 0) {
            actualizar_edad(&(agenda->contactos[i]));
        }
    }
    return;
}

double prom(struct Agenda *agenda) {
    double sum = 0;
    for (int i = 0; i < agenda->counter; i++) {
        sum += agenda->contactos[i].edad;
    }
    return sum / (double)(agenda->counter);
}

int main7() {
    struct Agenda agenda;
    agenda.counter = 0;
    agenda.contactos = malloc(sizeof(struct Contacto)*10);

    struct Agenda* ptrA = &agenda;
    
    agregar_agenda(ptrA, 3);

    modificar_edad_por_nombre(ptrA);
    imprimir_contactos(ptrA);

    printf("%f\n", prom(ptrA));
}

struct Point {
    double x, y;
};

struct Point medio(struct Point point1, struct Point point2) {
    struct Point medio;
    medio.x = (point1.x + point2.x) / 2;
    medio.y = (point1.y + point2.y) / 2; 
    return medio;
}

int main() {
    struct Point point1, point2, med;
    point1.x = 2;
    point1.y = 2;
    point2.x = 4;
    point2.y = 4;
    med = medio(point1, point2);
    printf("(%f, %f)\n", med.x, med.y);
}




