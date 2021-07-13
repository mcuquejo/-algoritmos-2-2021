#ifndef __PLAYA_PRIVADA_H__
#define __PLAYA_PRIVADA_H__
#include <stdbool.h>

#define MAX_NOMBRE 100
#define MAX_CARPAS 1000

typedef struct vacacionista {
    int dni;
    char nombre[MAX_NOMBRE];
} vacacionista_t;

typedef struct carpa {
    vacacionista_t vacacionista;
    bool ocupada;
} carpa_t;

typedef struct playa {
    carpa_t carpas[MAX_CARPAS];
    int cant_carpas;
    int cant_ocupadas;
} playa_t;

playa_t* playa_crear();

int playa_alquilar_carpa(playa_t* playa, vacacionista_t vacacionista);

int playa_dejar_carpa(playa_t* playa, int dni);

void playa_destruir(playa_t* playa);

void playa_mostrar(playa_t* playa);

#endif //__PLAYA_PRIVADA_H__