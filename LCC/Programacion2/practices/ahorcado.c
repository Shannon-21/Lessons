# include <stdio.h>
# include <string.h>

char used[27] = {'\0'}; 
char guess[30]; 
char word[30];
int tries = 7; 
int try = 0;

void print_board() {
    printf("try:%i/%i, used: ", try, tries);
    for (int i = 0; i < strlen(used); i++) {
        printf("%c", used[i]);
    }
    printf("\nguess: ");
    for (int i = 0; i < strlen(guess); i++) {
        printf("%c", guess[i]);
    }
    printf("\n");
}

int alredy_used(char g) {
    for (int i = 0; i < strlen(used); i++) {
        if (used[i] == g) {
            return 1;
        }
    }
    return 0;
}

int add_to_guess(char g) {
    int is_in = 0;
    for (int i = 0; i < strlen(guess); i++) {
        if (word[i] == g) {
            guess[i] = g;
            is_in = 1;
        }
    }
    return is_in;
}

int has_empty(char *g) {
    for (int i = 0; i < strlen(g); i++) {
        if (g[i] == '_') {
            return 1;
        }
    }
    return 0;
}

int finished() {
    if (guess == word || !has_empty(guess)) {
        return 1;
    }
    return 0;
}

int main () {
    printf("word: ");
    scanf("%s", &word);
    for (int i = 0; i < strlen(word); i++) {
        guess[i] = '_';
    }
    print_board();
    
    while (!finished() || try < tries) {
        printf("char: ");
        char g;
        scanf("%c", &g);

        if (alredy_used(g)) {
            continue;
        }
        else {
            int is_in = add_to_guess(g);
            if (!is_in) {
                used[strlen(used)] = g;
                try++;
            }
        }

        print_board();
    }
}