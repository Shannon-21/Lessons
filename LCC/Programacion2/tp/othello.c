/// librerias

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/// estructuras

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

/// helpers

int dentro(int r, int c) {
    // para nunca salirse del rango del tablero
    return (r >= 0 && r < 8 && c >= 0 && c < 8);
}

char otro_color(char color) {
    return (color == 'B') ? 'N' : 'B';
}

Pos obtener_direccion(int dir) {
    // las 8 celdas de las direcciones contiguas posibles desde una posicion dada
    const int dr[8] = {-1,-1,-1,0,0,1,1,1};
    const int dc[8] = {-1,0,1,-1,1,-1,0,1};

    Pos dpos;
    dpos.r = 0;
    dpos.c = 0;

    if (dir < 0 || dir >= 8) return dpos;

    dpos.r = dr[dir];
    dpos.c = dc[dir];
    return dpos;
}

/// funciones inicializacion y parseo

void liberar_jugador(Jugador *j) {
    if (j->nombre) {
        free(j->nombre);
        j->nombre = NULL;
    }
}

void parse_jugador(char *line, Jugador *j) {
    // line viene sin \n
    char *comma = strchr(line, ',');
    if (!comma) {
        fprintf(stderr, "linea de jugador invalida\n");
        exit(1);
    }

    *comma = '\0';

    j->nombre = (char *)malloc(strlen(line) + 1);
    if (!j->nombre) {
        fprintf(stderr, "malloc fallo\n");
        exit(1);
    }
    strcpy(j->nombre, line);

    // coma + color (ej "Alejandro,B")
    if (comma[1] == 'B' || comma[1] == 'N') j->color = comma[1];
    else {
        fprintf(stderr, "color de jugador invalido\n");
        exit(1);
    }
}

void cargar_datos_iniciales(FILE *f, Juego *juego) {
    char line[128];

    juego->j1.nombre = NULL;
    juego->j2.nombre = NULL;
    juego->turno = 'B';

    if (!fgets(line, sizeof(line), f)) {
        fprintf(stderr, "archivo incompleto para jugador 1\n");
        exit(1);
    }
    line[strcspn(line, "\n")] = 0;
    parse_jugador(line, &juego->j1);

    if (!fgets(line, sizeof(line), f)) {
        fprintf(stderr, "archivo incompleto para jugador 2\n");
        exit(1);
    }
    line[strcspn(line, "\n")] = 0;
    parse_jugador(line, &juego->j2);

    if (!fgets(line, sizeof(line), f)) {
        fprintf(stderr, "archivo incompleto para color inicial\n");
        exit(1);
    }
    line[strcspn(line, "\n")] = 0;

    if (line[0] != 'B' && line[0] != 'N') {
        fprintf(stderr, "color inicial invalido\n");
        exit(1);
    }
    juego->turno = line[0];
}

void inicializar_tablero(char board[8][8]) {
    /* Init of the board:
       D5:N, E5:B, E4:N, D4:B
       Usamos indices 0..7 para filas y columnas
       Mapeo: columna 'A'->0 ... 'H'->7
       fila '1'->0 ... '8'->7
    */

    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            board[r][c] = 'X';

    // config inicial del juego
    board[4][3] = 'N'; // D5
    board[4][4] = 'B'; // E5
    board[3][4] = 'N'; // E4
    board[3][3] = 'B'; // D4
}

void imprimir_tablero(char board[8][8]) {
    // imprimir en formato parecido al tablero de othello para que sea facil identificar las celdas
    printf("   A B C D E F G H\n");
    for (int r = 0; r < 8; ++r) {
        printf("%d  ", r+1);
        for (int c = 0; c < 8; ++c) {
            char ch = board[r][c];
            if (ch == 'X') printf(". ");
            else printf("%c ", ch);
        }
        printf("\n");
    }
}

/// funciones de validacion

int parse_move(const char *move, int *out_r, int *out_c) {
    // move tipo "D6". el caller ya recorta \n
    if (!move) return 0;

    if (move[0] == '\0') {
        return 2; // pass
    }

    if (strlen(move) != 2) return 0;

    char colc = toupper((unsigned char)move[0]);
    char rowc = move[1];

    // usa el ordinal del caracter para comparar, por lo que resulta en un orden 'natural'
    if (colc < 'A' || colc > 'H') return 0;
    if (rowc < '1' || rowc > '8') return 0;

    *out_c = colc - 'A';
    *out_r = rowc - '1';
    return 1;
}

int calcular_flips(char board[8][8], char my, int r, int c, Pos flips[64]) {
    // devuelve cantidad de fichas a girar si juego en (r,c), si es invalida -> 0
    // aca NO chequea "pass", eso va por otro lado
    if (!dentro(r, c)) return 0;
    if (board[r][c] != 'X') return 0;

    char opp = otro_color(my);
    int total = 0;

    for (int d = 0; d < 8; ++d) {
        Pos dir = obtener_direccion(d);

        // se para una celda al lado en la direccion dada
        int rr = r + dir.r;
        int cc = c + dir.c;

        if (!dentro(rr, cc)) continue;
        if (board[rr][cc] != opp) continue;

        // guardo camino temporal de esta dir
        Pos camino[64];
        int cant_camino = 0;

        // se va acoirdando las fichas que encierra en el camino del opuesto
        while (dentro(rr, cc) && board[rr][cc] == opp) {
            camino[cant_camino].r = rr;
            camino[cant_camino].c = cc;
            cant_camino++;
            rr += dir.r;
            cc += dir.c;
        }

        // y si termina con ficha propia, todo lo del medio, se voltea
        if (cant_camino > 0 && dentro(rr, cc) && board[rr][cc] == my) {
            // cierro, agrego a flips
            for (int i = 0; i < cant_camino; ++i) {
                flips[total++] = camino[i];
            }
        }
    }

    return total;
}

int hay_alguna_jugada_valida(char board[8][8], char color) {
    // ver si el color del turno tiene algun movimiento valido en el tablero
    Pos flips[64];
    // lo haria viendo si puede poner una ficha que podruzca cambios en el tablero en alguna de todas las celdas
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (board[r][c] != 'X') continue;
            if (calcular_flips(board, color, r, c, flips) > 0) {
                return 1;
            }
        }
    }
    return 0;
}

int validar_jugada(Juego *juego, char *move, char board[8][8]) {
    // devuelve 0 si es valida, 1 si invalida
    int r = 0, c = 0;
    int kind = parse_move(move, &r, &c);

    if (kind == 2) {
        // pass solo si no hay jugadas validas
        if (hay_alguna_jugada_valida(board, juego->turno)) return 1;
        return 0;
    }

    if (kind == 0) return 1;

    Pos flips[64];
    if (calcular_flips(board, juego->turno, r, c, flips) <= 0) return 1;

    return 0;
}

int verificar_ganador(char board[8][8]) {
    // termino solo si no hay X
    int countB = 0, countN = 0;

    // contar las fichas de cada uno y compararlas
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (board[r][c] == 'X') return 0;
            if (board[r][c] == 'B') countB++;
            else if (board[r][c] == 'N') countN++;
        }
    }

    printf("\nResultado:\n");
    printf("Puntuacion -> B: %d, N: %d\n", countB, countN);
    if (countB > countN) printf("Gano el jugador con color B\n");
    else if (countN > countB) printf("Gano el jugador con color N\n");
    else printf("Empate\n");

    return 1;
}

/// salida

void aplicar_jugada(char board[8][8], char my, int r, int c, Pos flips[64], int cant_flips) {
    // aca ya viene todo validado
    // agrega la ficha nueva
    board[r][c] = my;
    // y cambia de color cada ficha a voltear al color del turno actual
    for (int i = 0; i < cant_flips; ++i) {
        board[flips[i].r][flips[i].c] = my;
    }
}

void escribir_tablero(char board[8][8], Juego *juego, const char *nombre_salida) {
    FILE *out = fopen(nombre_salida, "w");
    if (!out) {
        fprintf(stderr, "No se pudo crear archivo de salida %s\n", nombre_salida);
        return;
    }

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            fputc(board[r][c], out);
        }
        fputc('\n', out);
    }

    fputc(juego->turno, out);
    fputc('\n', out);

    fclose(out);
    printf("Resultado de la partida '%s'\n", nombre_salida);
}

/// loop

int procesar_jugadas(FILE *f, Juego *juego, char board[8][8]) {
    char line[32];

    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = 0;

        // validacion una vez
        if (validar_jugada(juego, line, board)) {
            printf("El jugador con color %c realizo una jugada invalida\n", juego->turno);
            imprimir_tablero(board);
            return 1;
        }

        int r = 0, c = 0;
        int kind = parse_move(line, &r, &c);

        if (kind == 1) {
            Pos flips[64];
            int cant = calcular_flips(board, juego->turno, r, c, flips);
            // cant > 0 seguro pq ya valido
            aplicar_jugada(board, juego->turno, r, c, flips, cant);
        } else {
            // pass, no hace nada
        }

        if (verificar_ganador(board)) return 1;

        juego->turno = otro_color(juego->turno);
    }

    return 0;
}

#ifndef TESTING // para no chocar con el main del test
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <archivo_entrada> <archivo_salida>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        printf("No se encontro el archivo %s\n", argv[1]);
        return 1;
    }

    Juego juego;
    juego.j1.nombre = NULL;
    juego.j2.nombre = NULL;
    juego.turno = 'B';

    cargar_datos_iniciales(f, &juego);

    char board[8][8];
    inicializar_tablero(board);

    if (!procesar_jugadas(f, &juego, board)) {
        escribir_tablero(board, &juego, argv[2]);
    }

    liberar_jugador(&juego.j1);
    liberar_jugador(&juego.j2);

    fclose(f);
    return 0;
}
#endif