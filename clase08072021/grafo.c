#include <stdlib.h>
#include <stdio.h>

#define ENTRADA 0
#define SALA 1
#define COCINA 2
#define BANIO 3
#define FIUBA 4
#define CALABOZO 5
#define JARDIN 6
#define TERRAZA 7


typedef struct {
    size_t cantidad_vertices;
    double* matriz;
} Grafo;

Grafo* grafo_crear(size_t cantidad_vertices) {
    Grafo* g = malloc(sizeof(Grafo));
    g->cantidad_vertices = cantidad_vertices;
    g->matriz = calloc(1, cantidad_vertices*cantidad_vertices*sizeof(double));
    return g;
}

Grafo* grafo_agregar_arista(Grafo* g, size_t v1, size_t v2, double peso) {
    g->matriz[v1*g->cantidad_vertices+v2] = peso;
    g->matriz[v2*g->cantidad_vertices+v1] = peso;
    return g;
}

double grafo_obtener_peso(Grafo* g, size_t v1, size_t v2) {
    return g->matriz[v1*g->cantidad_vertices+v2];
}

void grafo_destruir(Grafo* g) {
    free(g->matriz);
    free(g);
}

void grafo_mostrar(Grafo* g){
    for (size_t i = 0; i < g->cantidad_vertices; i++)
    {
        for (size_t j = 0; j < g->cantidad_vertices; j++)
        {
            printf("%f ", grafo_obtener_peso(g, i, j));

        }
        printf("\n");
    }
}

int main(){
    Grafo* g = grafo_crear(10);
    //grafo_agregar_arista(g, ENTRADA, FIUBA, 8);
    //grafo_agregar_arista(g, ENTRADA, SALA, 1);
    //grafo_agregar_arista(g, FIUBA, TORTURA, 2);
    //grafo_agregar_arista(g, TORTURA, CALABOZO, 3);
    //grafo_agregar_arista(g, SALA, COCINA, 2);
    //grafo_agregar_arista(g, SALA, BANIO, 4);
    //grafo_agregar_arista(g, SALA, COCINA, 2);
    //grafo_agregar_arista(g, SALA, BANIO, 4);
    //grafo_agregar_arista(g, BANIO, TERRAZA, 3);
    //grafo_agregar_arista(g, TERRAZA, JARDIN, 2);



    grafo_destruir(g);
    return 0;
}