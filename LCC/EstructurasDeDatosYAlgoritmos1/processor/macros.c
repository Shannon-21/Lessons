# include <stdio.h>

#define PRINT(x) printf("%s\n", x)

#define PRINTARRAY(arr, size) do { \
  char result[256] = ""; \
  int offset = 0; \
  for (int i = 0; i < size; i++) { \
    offset += snprintf(result + offset, sizeof(result) - offset, " %d", arr[i]); \
  } \
  PRINT(result); \
} while(0)

int main() {
  PRINT("Hola");
  int arr[] = {1, 2, 3, 4, 5};
  PRINTARRAY(arr, 5);
}
