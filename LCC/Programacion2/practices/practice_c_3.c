# include <stdio.h>
# include <math.h>
# include <stdlib.h>

struct Complex
{
    double r;
    double i;
};

typedef struct Complex C;

C complejo(double re, double im) {
    C cn;
    cn.r = re;
    cn.i = im;
    return cn;
}

double parte_real(C c) {
    return c.r;
}

double parte_imaginaria(C c) {
    return c.i;
}

double modulo_C(C c) {
    return sqrt(c.r*c.r + c.i*c.i);
}

C suma_C(C c1, C c2) {
    C r;
    r.r = c1.r + c2.r;
    r.i = c1.i + c2.i;
    return r; 
}

C producto(C c1, C c2) {
    C r;
    r.r = c1.r * c2.r - c1.i * c2.i;
    r.i = c1.r * c2.i + c1.i * c2.r;
    return r;
}

C opuesto_C(C c) {
    C r;
    c.r = -1 * c.r;
    c.i = -1 * c.i;
    return c;
}

C reciproco(C c) {
    C r;
    c.r = ((double)c.r / (c.r*c.r + c.i*c.i));
    c.i = ((double)c.i / (c.r*c.r + c.i*c.i));
    return r;
}

C conjugado(C c) {
    C r;
    r.r = c.r;
    r.i = -1 * c.i;
    return r;
}

void mandelbrot () {
    int filas = 50 , columnas = 150;
    for (int i = 0; i < filas; ++ i) {
        for (int j = 0; j < columnas; ++ j) {
            double x = -2.0 + 3.0 * j / ( columnas - 1);
            double y = 1.0 - 2.0 * i / ( filas - 1);
            C c = complejo(x, y);
            C z = complejo(0.0, 0.0);
            int pertenece = 1;
            for (int k = 0; k < 20; ++k) {
                z = suma_C(producto(z, z), c);
                if (modulo_C(z) > 2.0)
                    pertenece = 0;
                }
            putchar(pertenece ? '#' : ' ');
        }
        putchar ('\n');
    }
}

typedef struct { double x, y ; } R2_1;
typedef struct { double v[2]; } R2;

void size_of_vector() {
    R2_1 v1;
    v1.x = 1;
    v1.y = 1;

    R2 v2;
    v2.v[0] = 1;
    v2.v[1] = 1;

    printf("%lu, %lu\n", sizeof(v1), sizeof(v2));
}

R2 suma_R2(R2 n1, R2 n2) {
    R2 r;
    r.v[0] = n1.v[0]+ n2.v[0];
    r.v[1] = n1.v[1]+ n2.v[1]; 
    return r;
}

R2 diferencia(R2 n1, R2 n2) {
    R2 r;
    r.v[0] = n1.v[0] - n2.v[0];
    r.v[1] = n1.v[1] - n2.v[1];
    return r;
}

R2 opuesto_R2(R2 n) {
    R2 r;
    r.v[0] *= -1;
    r.v[1] *= -1;
    return r;
}

R2 producto_con_escalar(double s, R2 n) {
    R2 r;
    r.v[0] *= s;
    r.v[1] *= s;
    return r;
}

double producto_escalar(R2 n1, R2 n2) {
    return n1.v[0] * n2.v[0] + n1.v[1] * n2.v[1];
}

double modulo_R2(R2 n) {
    return sqrt(n.v[0]*n.v[0] + n.v[1]*n.v[1]);
}

R2 proyeccion(R2 n1, R2 n2) {
    double r1;
    R2 rf;

    r1 = ((double)(producto_escalar(n1, n2))) / (modulo_R2(n2)*modulo_R2(n2));
    rf = producto_con_escalar(r1, n2);
}


void find_type() {
    int vector[5] = {10, 20, 30, 40, 50};
    int a = 3;
    int *ptr = &a;
    int *qtr = vector;

    // quiero saber que tipo de dato es, el valor que tiene, y una muy breve explicacion de porque es lo que es
    /* 
    a 
    &a
    *a 
    ptr
    &ptr 
    *ptr 
    qtr 
    &qtr
    *qtr 
    vector 
    &vector 
    *vector
    ++qtr 
    ++*qtr 
    ++*vector 
    *&ptr 
    */
}

void types() {
    int *ip1, ip2;
    char ch, *cp;

    ip1 = 0;
    printf("%d", ip1);
}

void exe_1a() {
    int* punt;
    int x = 7, y = 5;
    punt = &x;
    *punt = 4;
    printf("%d %d", x, y);
}

void exe_1b() {
    int* punt;
    int x = 7, y = 5;
    punt = &x;
    x = 4;
    punt = &y;
    printf("%d %d", *punt, x);
}

void exe_1c() {
    int* punt, i;
    int x[] = {1, 2, 3, 4, 5};
    punt = x;
    *punt = 9;
    for (i = 0; i < 5; i++) {
        printf("%d, ", x[i]);
    }
}

void exe_1d() {
    int* punt, i;
    int x[] = {1, 2, 3, 4, 5};
    punt = x;
    *(punt + 2) = 9;
    *(x + 3) = 7;
    punt[1] = 11;
    for (i = 0; i < 5; i++) {
        printf("%d, ", *(punt+i));
    }
}

void exe_1e() {
    int *punt, i;
    int x[5] = {1, 2, 3, 4, 5};
    punt = &x[0] + 3;
    *(punt - 2) = 9;
    punt--;
    *(punt) = 7;
    punt[1] = 11;
    punt = x;
    for (i = 0; i < 5; i++) {
        printf("%d, ", punt[i]);
    }
}

void exe_1f() {
    int v[4] = {2, 4, 5, 7}, a, *p;
    p = v + 2; // &v[2]
    p--; // &v[1]
    a = *p + *(p + 1) + *(v + 1) + p[2]; // 4 + 5 + 4 + 7 = 8 + 12 = 20
    printf("%d", a);
}

void aumentar(int* x, int* y, int z) {
    *x = *x + 2;
    *y = *y + 5;
    z = z + 4;
}

void exe_1g() {
    int x, y, z;
    x = 3;
    y = 10;
    z = 15;
    aumentar(&x, &y, z);
    printf("%d %d %d", x, y, z);
}

void ingreseCadena(char* c) {
    fgets(c, 10, stdin);
}

void exe_1h() {
    char* cadena = malloc(sizeof(char) * 10);
    fgets(cadena, 10, stdin);
    printf("%s %p\n", cadena, &cadena);
    ingreseCadena(cadena);
    printf("%s %p", cadena, &cadena);
    free(cadena);
}

int *direccion_local(int x) {
    // return &x;
    return 0;
}

void exe_1i() {
    int *ptr = NULL;
    ptr = direccion_local(2);
    printf("%d\n", *ptr);
}

void exe_2a() {
    char textoA[30] = "Agarrate Catalina";
    char textoB[30] = "El cuarteto de Nos";
    char* p = textoA;
    char* q = textoB;
    char a;
    printf("textoA: %s\ntextoB: %s\n", textoA, textoB);
    while (*p++ = *q++) a = a;
    printf("while\n");
    printf("textoA: %s\ntextoB: %s\n", textoA, textoB);
}

void exe_2b() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *ptr;
    ptr = array;
    printf("array[0]>%d; *ptr: %d\n", array[0], *ptr);
    printf("array[1]>%d; *(ptr+1): %d\n", array[1], *(ptr+1));
    ptr++;
    printf("ptr++; *ptr: %d\n", *ptr);
}

char* copiar_cadena(char* cad, int longitud) {
    char* a = malloc(sizeof(char) * longitud);
    a = cad;
    return a;
}

void exe_2c() {
    char a[10] = "hola";
    char* b = copiar_cadena(a, 10);
    printf("%s %s\n", a, b);
    b[0] = 's';
    printf("%s %s\n", a, b);
}

int vector[5] = {10, 20, 30, 40, 50};
#define SIZE 100

struct informacionCelda {
    char nombre[SIZE];
    int identificador;
    float calidad;
    struct informacionOp * op;
};

struct informacionOp {
    char nombre[SIZE];
    int prioridad;
    int ultimaComprobacion;
};

void exe_3a() {
    struct informacionCelda c;
    printf("%d\n", sizeof(c));
}

void exe_3b() {
    struct informacionCelda a;
    struct informacionCelda* b;
    printf("%d %d\n", sizeof(a), sizeof(b));
}

void exe_3c() {
    struct informacionCelda a;
    struct informacionOp op;

    // enlazo el puntero interno
    a.op = &op;

    printf("a                  = %p\n", (void*)&a);
    printf("a.nombre           = %p\n", (void*)&a.nombre);
    printf("a.identificador    = %p\n", (void*)&a.identificador);
    printf("a.calidad          = %p\n", (void*)&a.calidad);
    printf("a.op               = %p\n", (void*)&a.op);  // la dirección del puntero
    printf("*a.op (op)         = %p\n", (void*)a.op);    // la dirección de la estructura op

    printf("\nCampos del struct informacionOp:\n");
    printf("op                 = %p\n", (void*)&op);
    printf("op.nombre          = %p\n", (void*)&op.nombre);
    printf("op.prioridad       = %p\n", (void*)&op.prioridad);
    printf("op.ultimaComp      = %p\n", (void*)&op.ultimaComprobacion);
}

void exe_3d() {
    struct informacionCelda c;
    struct informacionCelda* cptr = &c;
    struct informacionCelda d;
    struct informacionCelda* dptr = cptr;
    printf("%p %p", cptr, dptr);
}

struct pack3 {
    int a;
};

struct pack2 {
    int b;
    struct pack3 *next;
};

struct pack1 {
    int c;
    struct pack2 *next;
};

void exe_4a() {
    struct pack1 data1, *dataPtr;
    struct pack2 data2;
    struct pack3 data3;
    data1.c = 30;
    data2.b = 20;
    data3.a = 10;
    dataPtr = &data1;
    data1.next = &data2;
    data2.next = &data3;

    printf("%d", dataPtr->next->b);
}

void assign(const char* texto, const char* sub) {
    // char t[] = texto;
    // char s[] = sub;
    printf("%s %s\n", texto, sub);
}

void init() {
    const char text[] = "Hola";
    const char sub[] = "Sub";
    assign(text, sub);
}

int main() {
    // mandelbrot();
    // size_of_vector();
    // find_type();
    // types();
    // exe_1i();
    // exe_2c();
    // exe_3d();
    // exe_4a();
    init();
    return 0;
}