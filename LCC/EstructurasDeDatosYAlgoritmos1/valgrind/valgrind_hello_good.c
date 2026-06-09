// Save as valgrind_hello_bad.c
// Compile with debug info: $ gcc  -Wall -gstabs valgrind_hello_bad.c -o valgrind_hello_bad
// Test with  valgrind:     $ valgrind --tool=memcheck  ./valgrind_hello_bad
//
#include <stdlib.h>
int main()
{
  void* ptr=malloc(1);
  free(ptr);
  return 0;
}
