#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int findSquare(int a)
{
    return a * a;
}

int main(int n, char** args)
{
    for (int i = 1; i < n; i++) 
    {
        int a = atoi(args[i]);
        printf("%d\n", findSquare(a));
    }
    return 0;
}
