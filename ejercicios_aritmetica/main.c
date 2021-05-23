#include <stdio.h>
#include <stdlib.h>

int main () {
    int* puntero = malloc(sizeof(int));

    puntero[0] = 1;
    free(puntero);
    return 0;
}