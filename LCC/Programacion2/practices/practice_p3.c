#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;   // fila
    int y;   // columna
    int vida;
    int oro;
} Player;

int within_bounds(int x, int y, int filas, int columnas) {
    return x >= 0 && x < filas && y >= 0 && y < columnas;
}

char get_cell(char** board, int x, int y) {
    return board[x][y];
}

void set_cell(char** board, int x, int y, char c) {
    board[x][y] = c;
}

char** create_board(int filas, int columnas) {
    char** tablero = malloc(sizeof(char*)*filas);
    for (int i = 0; i < filas; i++) {
        tablero[i] = malloc(sizeof(char)*columnas);
        for (int j = 0; j < columnas; j++) {
            tablero[i][j] = '.';
        }
    }
    return tablero;
}

void place_player(char** board, Player* p) {
    board[p->x][p->y] = 'P';
}

void move_player(char** board, Player* p, char move, int filas, int columnas) {
    int nx, ny;
    switch (move)
    {
        case 'W':
            nx = p->x-1;
            ny = p->y;
            break;
        case 'S':
            nx = p->x+1;
            ny = p->y;
            break;
        case 'A':
            nx = p->x;
            ny = p->y-1;
            break;
        case 'D':
            nx = p->x;
            ny = p->y+1;
            break;
        default:
            break;

    }
    
    if (!within_bounds(nx, ny, filas, columnas)) return;

    switch (get_cell(board, nx, ny))
    {
        case '#':
            return;
        case 'T':
            p->vida -= 20;
            break;
        case 'R':
            p->oro += 10;
        default:
            break;
    }

    set_cell(board, p->x, p->y, '.');
    p->x = nx;
    p->y = ny;
    set_cell(board, p->x, p->y, 'P');
}

void show_status(Player* p) {
    printf("(%i, %i), %i, %i\n", p->x, p->y, p->vida, p->oro);
}

void free_board(char** board, int filas) {
    for (int i = 0; i < filas; i++) {
        free(board[i]);
    }
    free(board);
}

void print_board(char** board, int filas, int columnas) {
    printf("\nTablero:\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int F, C;
    printf("Filas y columnas del tablero: ");
    scanf("%d %d", &F, &C);

    char** board = create_board(F, C);

    // Colocamos algunos elementos fijos para probar
    if (F > 2 && C > 2) {
        board[1][1] = 'T';  // trampa
        board[2][2] = 'R';  // tesoro
        board[0][2] = '#';  // muro
    }

    Player p = {0, 0, 100, 0};
    place_player(board, &p);

    int M;
    printf("Cantidad de movimientos: ");
    scanf("%d", &M);

    printf("Ingrese los movimientos (W A S D):\n");

    for (int i = 0; i < M; i++) {
        char mv;
        scanf(" %c", &mv);
        move_player(board, &p, mv, F, C);
    }

    print_board(board, F, C);
    show_status(&p);

    free_board(board, F);

    return 0;
}