# include <stdio.h>
# include <stdlib.h>
# include <math.h>

char board[9] = {
    ' ', ' ', ' ',
    ' ', ' ', ' ',
    ' ', ' ', ' '
};

int player = 0;

char get_letter() {
    return player == 0 ? 'O' : 'X';
}

void print_board() {
    for (int pos = 0; pos < 9; pos++) {
        printf("%c, ", board[pos]);
        if (pos == 2 || pos == 5) {
            printf("\n");
        }
    }
    printf("\n");
}

void print_finished_board() {
    for (int pos = 0; pos < 9; pos++) {
        printf("%c, ", board[pos]);
        if (pos == 2 || pos == 5) {
            printf("\n");
        }
    }
    printf("\n");
}

int ask_position() {
    int pos;
    printf("pos: ");
    scanf("%d", &pos);
    return pos;
}

int place_player(int pos) {
    char letter = get_letter();
    if (board[pos] == ' ' || pos < 0 || pos >= 9) {
        board[pos] = letter;
        return 1;
    }
    else {
        return 0;
    }
}

int same_contiguous(int curr_pos, int next_pos) {
    if (board[curr_pos] == ' ' || board[next_pos] == ' ')
        return 0;

    if (board[curr_pos] == board[next_pos]) {
        return 1;
    }
    return 0;
}

int check_line(int start, int step) {    
    if (same_contiguous(start, start+step) && same_contiguous(start+step, start+step*2)) {
        return 1;
    }

    return 0;
}

void change_turn() {
    if (player == 0) {
        player++;
    }
    else {
        player--;
    }
}

int check_status() {
    if (// cols
        check_line(0, 3) ||
        check_line(1, 3) ||
        check_line(2, 3) ||
        // rows
        check_line(0, 1) ||
        check_line(3, 1) ||
        check_line(6, 1) ||
        // diagonals
        check_line(0, 4) ||
        check_line(2, 2)) {
            change_turn();
            return player;
    }

    return -1;
}

int completed_board() {
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            return 0;
        }
    }
    return 1;
}

int sucess_winner() {
    int winner = check_status();
    if (winner == -1) {
        return 0;
    }
    printf("Winner: %d\n", winner);
    return 1;
}

int finished() {
    return sucess_winner() || completed_board();
}

void start_game() {
    while (!finished()) {
        print_board();
        int pos = ask_position();
        int sucess_place = place_player(pos);
        if (!sucess_place) {
            printf("It's already occuped. Try again.\n");
            continue;
        }
        change_turn();
    }
    print_finished_board();
}

int main() {
    start_game();
    return 0;
}