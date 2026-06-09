# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct {
    char nombre[20];
    int longitud;
    int fila;
    int col_inicio;
} Barco;

void mostrar_tablero(char** tablero, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%c ", tablero[i][j]);
        }
        printf("\n");
    }
}

char** crear_tablero(int N , int M) {
    char** tablero = malloc(N*sizeof(char*));
    for(int i = 0; i < N; i++) {
        tablero[i] = malloc(M*sizeof(char));
        for (int j = 0; j < M; j++) {
            tablero[i][j] = '~';
        }
    }
    return tablero;
}

void colocar_barco(char** tablero, Barco* barco) {
    for (int i = 0; i < barco->longitud; i++) {
        tablero[barco->fila][barco->col_inicio+i] = 'B';
    }
}

int disparo(char** tablero, int fila, int col) {
    int valid = fila > 0 && col > 0;
    char c = valid ? tablero[fila][col] : 'N';
    switch (c)
    {
        case '~':
            return 0;        
        case 'B':
            tablero[fila][col] = 'X';
            return 1;
        case 'X':
            return 0;
        case 'N':
            return -1;
    };
}

int hundido(char** tablero, Barco* b) {
    for (int i = 0; i < b->longitud; i++) {
        if (tablero[b->fila][b->col_inicio+i] == 'B') {
            return 0;
        }
    }
    return 1;
}

int main() {
    int N = 10, M = 10;
    char** t = crear_tablero(N, M);

    Barco b1 = {"Destructor", 3, 2, 4};
    Barco b2 = {"Fragata", 2, 5, 7};

    colocar_barco(t, &b1);
    colocar_barco(t, &b2);

    int tries = 8, try = 0;
    while (try < tries) {
        mostrar_tablero(t, N, M);

        // El usuario dispara
        int f, c;
        scanf("%d %d", &f, &c);
        if (f >= N || c >= M) continue;
        if (disparo(t, f, c) == 1) printf("Impacto!\n");
        else { printf("Agua!\n"); try++; }

        if (hundido(t, &b1) || hundido(t, &b2)) printf("Barco hundido!\n");
    }
}
