
#include <stdlib.h>
#include <stdio.h>

// 🧠 PARTE 4 – Structs y aliasing
// 7. Struct por valor vs por puntero
struct Point {
    int x, y;
};

void move(struct Point p) {
    p.x += 1;
    printf("%i\n", p.x);
}

void move2(struct Point *p) {
    p->x += 1;
}

int main1() {
    struct Point p1;
    struct Point p2;
    p1.x = 10;
    p2.x = 20;
    struct Point *ptr2 = &p2;
    move(p1);
    move2(ptr2);
    printf("%i %i\n", p1.x, p2.x);
}

// ¿Qué modifica cada función?

// ¿Cuál es más eficiente y por qué?

// ¿Cuándo conviene pasar structs por valor?

// ¿Qué implicancias tiene sobre aliasing?

// 8. Padding y alineación
struct S {
    char c;
    int i;
    char d;
};

struct S2 {
    int i;
    char c;
    char d;
};

int main3() {
    struct S s;
    s.c = 'a';
    s.i = 0;
    s.d = 'b';
    printf("%i, %i, %i\n", sizeof(s), sizeof(int), sizeof(char));

    struct S2 s2;
    s2.c = 'a';
    s2.i = 0;
    s2.d = 'b';
    printf("%i, %i, %i\n", sizeof(s2), sizeof(int), sizeof(char));

}


// ¿Por qué sizeof(struct S) puede ser mayor que la suma de los campos?

// ¿Qué es padding?

// ¿Por qué existe?

// ¿Cómo podrías reducir el tamaño sin cambiar los tipos?

// 🧠 PARTE 5 – Undefined Behavior (UB)
// 9. Acceso fuera de rango
int main9 () {
    int v[3] = {1, 2, 3};
    printf("%d\n", v[3]);
}

// ¿Qué tipo de error es?

// ¿Por qué C no lo detecta?

// ¿Qué puede pasar?

// ¿Por qué esto es una decisión de diseño del lenguaje?

// 10. Secuencia de evaluación
int main10 () {
    int i = 0;
    i = i++ + 1;
    printf("%d\n", i);
}

// ¿Es válido?

// ¿Tiene comportamiento definido?

// ¿Por qué este tipo de expresiones es peligroso?

// ¿Cómo escribirlo correctamente?

// 🧠 PARTE 6 – Strings en C
// 11. char* vs char[]
int main11 () {
    char *s1 = "hola";
    char s2[] = "hola";

    // s1[0] = 'H';
    s2[0] = 'H';
    printf("%s %s\n", s1, s2);
}

// ¿Dónde vive cada string?

// ¿Cuál se puede modificar?

// ¿Qué pasa si hacés s1[0] = 'H';?

// ¿Por qué esta diferencia es fundamental en C?

// 12. Funciones con strings
void f(char *s) {
    s[0] = 'X';
}

int main12() {
    char *s1 = "hola";
    char s2[] = "hola";

    // f(s1);
    f(s2);
    printf("%s %s\n", s1, s2);
}


// ¿Qué asume esta función?

// ¿Qué pasa si recibe un literal?

// ¿Cómo documentarías o reforzarías el contrato?

// 🧠 PARTE 7 – Diseño en C
// 13. APIs y ownership

// ¿Qué significa “ownership” de memoria en C?

// ¿Por qué es crucial documentarlo?

// Da un ejemplo de función que:

// devuelve memoria

// y explica quién debe liberarla.

// 14. const no es cosmético
// void print(const char *s);


// ¿Qué garantiza const acá?

// ¿Qué NO garantiza?

// ¿Por qué const mejora el diseño de APIs?

// ¿Qué pasa si intentás modificar s dentro?

// 🧠 PARTE 8 – Pregunta integradora
// 15. (Razonamiento global)

// Diseñá mentalmente una función en C que:

// reciba un array de enteros y su tamaño

// devuelva:

// el primer elemento

// el último elemento

// el promedio

// sin usar variables globales

// ¿Qué pasa si el tamaño es 0?

// ¿Cómo devolverías múltiples valores?

// ¿Qué decisiones de diseño tenés que tomar?

// ¿Cómo evitarías UB?