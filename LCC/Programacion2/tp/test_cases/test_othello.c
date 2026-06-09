
#include <assert.h>
#include <stdio.h>
#include <string.h>

// --- estructuras (del othello.c) ---

typedef struct {
    char *nombre;
    char color;
} Jugador;

typedef struct {
    Jugador j1;
    Jugador j2;
    char turno;
} Juego;

typedef struct {
    int r;
    int c;
} Pos;

int dentro(int r, int c);
char otro_color(char color);
Pos obtener_direccion(int dir);
void inicializar_tablero(char board[8][8]);

int parse_move(const char *move, int *out_r, int *out_c);
int calcular_flips(char board[8][8], char my, int r, int c, Pos flips[64]);
int hay_alguna_jugada_valida(char board[8][8], char color);

void aplicar_jugada(char board[8][8], char my, int r, int c, Pos flips[64], int cant_flips);
int verificar_ganador(char board[8][8]);

// --- helpers ---

void tablero_vacio(char board[8][8]) {
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            board[r][c] = 'X';
}

void tablero_inicial_estandar(char board[8][8]) {
    // el init clasico del juego
    tablero_vacio(board);
    board[4][3] = 'N'; // D5
    board[4][4] = 'B'; // E5
    board[3][4] = 'N'; // E4
    board[3][3] = 'B'; // D4
}

int mismo_set_flips(Pos a[64], int na, Pos b[64], int nb) {
    // para comparar sin importar el orden
    if (na != nb) return 0;

    for (int i = 0; i < na; ++i) {
        int ok = 0;
        for (int j = 0; j < nb; ++j) {
            if (a[i].r == b[j].r && a[i].c == b[j].c) {
                ok = 1;
                break;
            }
        }
        if (!ok) return 0;
    }
    return 1;
}

// --- tests unitarios ---

void test_obtener_direccion() {
    Pos p;

    // dir 0: (-1, -1)
    p = obtener_direccion(0);
    assert(p.r == -1);
    assert(p.c == -1);

    // dir 3: (0, -1)
    p = obtener_direccion(3);
    assert(p.r == 0);
    assert(p.c == -1);

    // dir 7: (1, 1)
    p = obtener_direccion(7);
    assert(p.r == 1);
    assert(p.c == 1);

    // fuera de rango -> (0,0)
    p = obtener_direccion(-1);
    assert(p.r == 0);
    assert(p.c == 0);

    p = obtener_direccion(8);
    assert(p.r == 0);
    assert(p.c == 0);
}

void test_dentro_y_otro_color() {
    assert(dentro(0, 0) == 1);
    assert(dentro(7, 7) == 1);
    assert(dentro(-1, 0) == 0);
    assert(dentro(0, -1) == 0);
    assert(dentro(8, 0) == 0);
    assert(dentro(0, 8) == 0);

    assert(otro_color('B') == 'N');
    assert(otro_color('N') == 'B');
}

void test_parse_move() {
    int r, c;

    r = c = -1;
    assert(parse_move("D6", &r, &c) == 1);
    assert(r == 5 && c == 3);

    r = c = -1;
    assert(parse_move("A1", &r, &c) == 1);
    assert(r == 0 && c == 0);

    r = c = -1;
    assert(parse_move("", &r, &c) == 2); // pass
    assert(r == -1 && c == -1); // no deberia tocarlo

    r = c = -1;
    assert(parse_move("AA", &r, &c) == 0);
    assert(parse_move("A9", &r, &c) == 0);
    assert(parse_move("I1", &r, &c) == 0);
    assert(parse_move("D66", &r, &c) == 0);
}

void test_calcular_flips_en_inicio() {
    char board[8][8];
    tablero_inicial_estandar(board);

    // en el tablero inicial, B tiene 4 jugadas validas y en todas voltea 1
    // en particular, C5 (r=4,c=2) voltea D5 (r=4,c=3)
    Pos flips[64];
    int cant = calcular_flips(board, 'B', 4, 2, flips);
    assert(cant == 1);
    assert(flips[0].r == 4 && flips[0].c == 3);

    // y una que no deberia ser valida
    cant = calcular_flips(board, 'B', 0, 0, flips);
    assert(cant == 0);

    // celda ocupada -> 0
    cant = calcular_flips(board, 'B', 3, 3, flips);
    assert(cant == 0);
}

void test_hay_alguna_jugada_valida() {
    char board[8][8];
    tablero_inicial_estandar(board);

    assert(hay_alguna_jugada_valida(board, 'B') == 1);
    assert(hay_alguna_jugada_valida(board, 'N') == 1);

    // tablero casi todo B, con una X y sin N: nadie puede encerrar nada
    tablero_vacio(board);
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            board[r][c] = 'B';
    board[0][0] = 'X';

    assert(hay_alguna_jugada_valida(board, 'B') == 0);
    assert(hay_alguna_jugada_valida(board, 'N') == 0);
}

void test_aplicar_jugada_voltea() {
    char board[8][8];
    tablero_inicial_estandar(board);

    // probamos una jugada concreta: B juega C5 (4,2) y voltea D5 (4,3)
    Pos flips[64];
    int cant = calcular_flips(board, 'B', 4, 2, flips);
    assert(cant == 1);

    aplicar_jugada(board, 'B', 4, 2, flips, cant);

    assert(board[4][2] == 'B');
    assert(board[4][3] == 'B'); // volteada
}

void test_calcular_flips_mas_de_uno() {
    // armo un caso facil donde una jugada voltea 3 en linea
    // fila 4: X N N N B ...
    // B juega A4 -> voltea B4,C4,D4
    char board[8][8];
    tablero_vacio(board);

    board[3][1] = 'N';
    board[3][2] = 'N';
    board[3][3] = 'N';
    board[3][4] = 'B';

    Pos flips[64];
    int cant = calcular_flips(board, 'B', 3, 0, flips);
    assert(cant == 3);

    Pos esperado[64];
    esperado[0].r = 3; esperado[0].c = 1;
    esperado[1].r = 3; esperado[1].c = 2;
    esperado[2].r = 3; esperado[2].c = 3;

    assert(mismo_set_flips(flips, cant, esperado, 3) == 1);
}

void test_verificar_ganador() {
    char board[8][8];

    // no terminado si hay alguna X
    tablero_vacio(board);
    board[0][0] = 'B';
    assert(verificar_ganador(board) == 0);

    // terminado si no hay X
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            board[r][c] = 'B';
    assert(verificar_ganador(board) == 1);
}

// --- runner ---

int main() {
    test_dentro_y_otro_color();
    test_obtener_direccion();
    test_parse_move();
    test_calcular_flips_en_inicio();
    test_hay_alguna_jugada_valida();
    test_aplicar_jugada_voltea();
    test_calcular_flips_mas_de_uno();
    test_verificar_ganador();

    printf("ok, pasaron todos los tests\n");
    return 0;
}
