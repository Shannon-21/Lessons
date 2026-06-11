# include <stdlib.h>
# include <stdio.h>
# include <string.h>

// a) int string_len(char* str), que retorne la longitud de la cadena str, excluyendo el caracter nulo (’\0’).

int string_len(char* str) {
    int idx = 0;
    
    while (str[idx] != '\0') {
        idx++;    
    }
    
    return idx;
}

int string_len_with_pointers(const char* str) {
    const char* p = str;
    
    while (*p != '\0') {
        p++;
    }
    
    return p - str;
}

// b) void string reverse(char* str), que invierta la cadena str.

int compare_reverse(const void* a, const void* b) {
    return 1;
}

void string_reverse(char* str, int size) {
    qsort(str, size, sizeof(char), compare_reverse);
}

/* c) int string concat(char* str1, char* str2, int max), 
 que concatene no mas de max caracteres de la cadena str2 al final de la cadena str1. 
 El caracter inicial de str2 debe sobrescribir el caracter nulo de str1. 
 La cadena resultante debe terminar con un caracter nulo. Retorna el numero de caracteres copiados.
 Nota: Si str1 no tiene espacio suficiente para almacenar el resultado, el comportamiento queda indefinido. 
*/

int string_concat(char* str1, char* str2, int max) {
    if (max <= 0) {
        return 0;
    }
    
    int len1 = string_len(str1);
    int copied = 0;
    
    while(str2[copied] != '\0' && copied < max) {
        str1[len1 + copied] = str2[copied];
        copied++;
    }

    str1[len1 + copied] = '\0';
    
    return copied;
}

/* 
d) int string compare(char* str1, char* str2), que compare en orden lexicografico las cadenas
str1 y str2, y retorne retorne -1 si la primera es menor que la segunda, 0 si son iguales, y 1 si es
mayor.
*/

int string_compare(char * str1, char* str2) {
    // iterar sobre la mas corta
    //  verificar diff entre las letras del mismo indx de ambos strings
    //  la diff es el resultado del orden

    int len1 = string_len(str1);
    int len2 = string_len(str2);
    
    int min = (len1 <= len2) ? len1 : len2;

    for (int i = 0; i < min; i++) {
        if (str1[i] == str2[i])
            continue;
        else if (str1[i] > str2[i])
            return 1;
        else
            return -1;
    }

    return (len1 < len2) ? -1 : (len1 > len2) ? 1 : 0;
}

/* e) int string subcadena(char* str1, char* str2), que retorne el ´ındice de la primera ocurrencia
de la cadena str2 en la cadena str1. En caso de no ocurrir nunca, retorna −1. */

int string_subcadena(char* str1, char* str2) {
    // strign rig
    // string rig
    int len1 = string_len(str1);
    int len2 = string_len(str2);
    int idx2 = 0;
    int f_idx2 = -1;

    if (len1 == 0 || len2 == 0) return f_idx2;

    for (int idx1 = 0; idx1 < len1; idx1++) {
        if (str1[idx1] == str2[idx2]) {
            if (f_idx2 == -1) {
                f_idx2 = idx1;
            }
            
            idx2++;
        }
        else {
            idx2 = 0;
            f_idx2 = -1;
        }

        if (idx2 == len2) return f_idx2;
    }

    return f_idx2;
}

/* f) void string unir(char* arregloStrings[], int n, char* sep, char* res), que concatene
las n cadenas del arreglo arregloStrings, separ´andolas por la cadena sep y almacenando el resultado en res.
Nota: Si res no tiene espacio suficiente para almacenar el resultado, el comportamiento queda
indefinido. */

void string_unir(char* arregloStrings[], int n, char* sep, char* res) {
    // for c in arr until n, res += c + sep; if c is last: res -= rep
    int sep_size = string_len(sep);
    int res_len = 0;

    for (int i = 0; i < n; i++) {
        int str_size = string_len(arregloStrings[i]);
        int cp = string_concat(res + res_len, arregloStrings[i], str_size);
        res_len += cp;
        
        if (i != n-1) {
            int cp_sep = string_concat(res + res_len, sep, sep_size);
            res_len += cp_sep;
        }
    }
}

// helpers

void print_arr_char(char *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%c", arr[i]);
    }
    printf("\n");
}

void print_arr_int(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

void print_arr_float(float *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%f, ", arr[i]);
    }
    printf("\n");
}

int main() {
    char* arrStr[] = {"string1", "str2", "string3"};
    char* sep = "-";
    char res[100];
    res[0] = '\0';
    
    string_unir(arrStr, 3, sep, res);

    printf("%s\n", res);

    return 0;
}