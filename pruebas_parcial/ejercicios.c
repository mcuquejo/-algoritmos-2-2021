#include <stdio.h>
#include <stdlib.h>

int busqueda_binaria(int* vector, int inicio, int fin, int elemento_buscado) {
    int centro;
    if(inicio <= fin) { // O(1)
        centro = (inicio + fin) / 2; //O(1)
        if (elemento_buscado == vector[centro]) {
            return centro;
        } else if (elemento_buscado > vector[centro]) {
            return busqueda_binaria(vector, centro + 1, fin, elemento_buscado);
        } else {
            return busqueda_binaria(vector, inicio, centro - 1, elemento_buscado);
        }
    }
    return -1;
}

//Ejercicio 1 complejidad
long suma (int numeros) {
    long acumulador = 0; //O(1)
    for(int i = 1; i <= numeros; i++) //O(n)
        acumulador += numeros; //O(1)

    return acumulador; //O(1)
}
//T(n) = O(n)

//Ejercicio 2 complejidad
int suma_por_tre(int n) {
    int contador = 1;
    for(int i = 1; i < n; i*=3)
        contador++;
    return contador;
}

/*
CALCULO DE BIG-O MATEMATICAMENTE HABLANDO A PARTIR DE F(X) = O(G(X))*************************************************************

Cuando yo estoy calculando la complejidad de una funciona, puedo definir que F(n) = O(g(n)), siempre que pueda encontrar un valor c > 0 y un n0 tal que F(n) <= c*g(n) para todo n > n0.
¿Qué me dice esto?, que siempre que pueda encontrar una cota superior de mi funcion, el orden Big-O de mi funcion será el de la cota. Por ejemplo, si yo quisiera demostrar cual es el orden de
x + 7, puedo definir una g(x) = x + 7x, que para cualquier x > 1, siempre será mayor a mi f(x) original. Por lo tanto, despejando, puedo determinar que
x + 7 <= x + 7x
= x + 7 <= 8x, donde |x + 7| <= |8x|, esto se cumplirá siempre que x > 1, por lo tanto, encontré mi c = 8, mi g(x) = x y mi x0 = 1, que me dicen que x + 7 = O(g(x) = O(x).

*/

void ejercicio_punteros() {
    int a = 4;
    printf("a vale :%i\n", a);
    int* b;
    int* c = malloc(sizeof(int));
    int** d = & c;

    b = *d;
    **d = 8;
    printf("a vale :%i\n", a);
    printf("b vale :%i\n", *b);
    printf("c vale :%i\n", *c);
    printf("d vale :%i\n", **d);
    a = *c;
    printf("a vale :%i\n", a);
    printf("b vale :%i\n", *b);
    printf("c vale :%i\n", *c);
    printf("d vale :%i\n", **d);
    **d = *b;
    printf("a vale :%i\n", a);
    printf("b vale :%i\n", *b);
    printf("c vale :%i\n", *c);
    printf("d vale :%i\n", **d);
    *b = 16;
    printf("a vale :%i\n", a);
    printf("b vale :%i\n", *b);
    printf("c vale :%i\n", *c);
    printf("d vale :%i\n", **d);
}

int prueba() {
    return 0;
}


int main() {
    printf("hola mundo\n");
    ejercicio_punteros();
    int arreglo[] = {1,2,3,4,5};

    int resultado = -2;

    resultado = busqueda_binaria(arreglo, 0, 4, 5);
    if(resultado == 4)
        printf("se encontró el 5\n");

    resultado = busqueda_binaria(arreglo, 0, 4, 6);
    if(resultado == -1)
        printf("No se encontró el 6\n");

    return 0;
}

