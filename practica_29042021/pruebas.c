#include <stdio.h>

void imprimir_invertido(char* texto) {
    if(texto[0] == 0)
        return;

imprimir_invertido(texto + 1);
printf("%c", *texto);
}


int main(int argc, char const *argv[])
{
    char* texto = "hola mundo!";

    imprimir_invertido(texto);

    return 0;
}
