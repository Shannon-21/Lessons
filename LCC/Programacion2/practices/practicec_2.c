#include <stdio.h>

int first() {
    int result;
    printf("Result: ");
    scanf("%d", &result);

    switch (result)
    {
        case 1:
            printf("Seis");
            break;
        case 6:
            printf("Uno");
            break;
        case 3:
            printf("Cuatro");
            break;
        case 4:
            printf("Tres");
            break;
        case 5:
            printf("Dos");
            break;
        case 2:
            printf("Cinco");
            break;
        default:
            printf("Numero incorrecto");
            break;
    }

    printf("\n");

    return 0;
}

#include <math.h>

void sum_for() {
    double result = 0.0;

    for (int j = 1; j <= 25; j++) {
        result += 1.0 / pow(j, j);
    }

    printf("%.15f\n", result);
}

void build_table() {
    int x , y ;
    printf (" Ingrese dos enteros dentro del rango [1 ,20]:\n") ;
    scanf (" %d %d", &x , & y ) ;
    if ( x >=1 && y >=1 && x <=20 && y <=20) {
        for (int i =1; i <= y ; i ++) {
            for (int j =1; j <= x ; j ++) {
                printf ("@") ;
            }
            printf ("\n") ;
        }
    } else {
        printf ("Los enteros no se encuentran en el rango pedido ") ;
    }
}

void build_arr() {
    int counts[100] = {0};
    int n;

    while (1) {
        scanf("%d", &n);

        if (n < 0) { break; }
        if (n >= 0 && n <= 99) { counts[n]++; }
    }

    int max_val = 0;
    int index = 0;

    for (int i = 0; i < 100; i++) {
        if (counts[i] > max_val) {
            max_val = counts[i];
            index = i;
        }
    }

    printf("Max: %d, %d\n", index, max_val);
}

void sum_arr() {
    int len;
    scanf("%d", &len);
    int arr[len];

    printf("sum([");
    for (int i = 0; i <= len; i++) {
        arr[i] = i + 5 * 2;
        printf("%d, ", arr[i]);
    }
    printf("]) = ");

    int result = 0;
    for (int i = 0; i <= len; i++) {
        result += arr[i];
    }

    printf("%d\n", result);
}

void print_arr(int arr[], int len) {
    printf("[");
    for (int index = 0; index < len; index++) {
        printf("%d,", arr[index]);
    }
    printf("]\n");
}

void criba_eratostenes() {
    const int N = 1000;
    int i, j, a[N+1]; // declaracion de dos enteros y un arreglo de 1001 componentes
    for (a[1] = 0, i = 2; i <= N; i++) { // asigna al segundo elemento el zero, y desde el tercer hasta el 1000, asigna 1, el primero queda sina asignar
        a[i] = 1;
    }
    
    for (i = 2; i <= N/2; i++) { // desde el tercer hasta 500
        for (j = 2; j <= N/i; j++) { // desde el tercer hasta cada iteracion del outer loop
            a[i*j] = 0;
        }
    }

    for (i = 1; i <= N; i++) {
        if(a[i]) {
            printf ("%d,", i) ;
        }
    }
    
    printf("\n");
}

#include <string.h>

int is_in(char c[10], char b) {
    for (int i = 0; i < strlen(c); i++) {
        if (c[i] == b) {
            return 0;
        }
    }
    return 1;
}

void reverse_input() {
    char ask[100];
    scanf("%s", &ask);
    
    int len = strlen(ask);
    char rev[len+1];

    int c = 0;
    for (int i = len-1; i >= 0; i--) {
        rev[c] = ask[i];
        c++;
    }

    rev[c] = '\0';
    
    printf("%s\n", rev);
}

int contains(char str1[20], char str2[20]) {
    char* larger;
    char* shorter;

    // find the larger to see if shorter is in larger
    if (strlen(str1) > strlen(str2)) {
        larger = str1;
        shorter = str2;
    }
    else {
        larger = str2;
        shorter = str1;
    }

    char app[20] = "";
    int shi = 0;
    int len = strlen(larger);

    for (int i = 0; i <= len-1; i++) {
        // start counting from the first match, and keep builing the app string until a mistmatch 
        if (larger[i] == shorter[shi]) {
            app[shi] = shorter[shi];
            shi++;
            // when it completes, return true
            if (strcmp(app, shorter) == 0) {
                return 1;
            }
        }
        // if a mistmatch, restart the built string, and conutinue comparing from the position we leave
        else {
            if (strlen(app) > 0) {
                i--;
            }
            for (int j=0; j < strlen(app); j++) {
                app[j] = '\0';
            }
            shi = 0;
        }
    }
    
    return 0;
}

int main(){
    // first();
    // sum_for();
    // build_table();
    // build_arr();
    // sum_arr();
    // criba_eratostenes();
    // printf("restult: %d\n", is_in("fasinating", 'y'));
    // reverse_input();
    // printf("%d\n", contains("significa", "insignsignifican"));
    return 0;
}