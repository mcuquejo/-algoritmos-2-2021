#include "gimnasios.h"
#include "hash.h"
#include <stdlib.h>
#include <string.h>

#define FUERTE 1.1
#define DEBIL 0.9
#define NEUTRAL 1.0

struct gimnasio
{
    const char *tipo;
    hash_t *efectividades;
};

char *duplicar_string(const char *s)
{
    if (!s)
        return NULL;

    char *p = malloc(strlen(s) + 1);
    strcpy(p, s);
    return p;
}

gimnasio_t *gimnasio_crear(char *tipo)
{
    gimnasio_t *gimnasio = calloc(1, sizeof(gimnasio_t));
    if (!gimnasio)
        return NULL;

    gimnasio->tipo = duplicar_string(tipo);
    gimnasio->efectividades = hash_crear(free, 10);

    if (!gimnasio->efectividades) {
        free(gimnasio);
        return NULL;
    }

    return gimnasio;
}

void gimnasio_agregar_efectividad(gimnasio_t *gimnasio, const char *tipo, double efectividad)
{
    if (!gimnasio || !tipo || !efectividad)
        return;

    double *var_efectividad = calloc(1, sizeof(efectividad));
    if (!var_efectividad)
        return;
    *var_efectividad = efectividad;
    hash_insertar(gimnasio->efectividades, tipo, var_efectividad);
}

const char *gimnasio_obtener_tipo(gimnasio_t *gimnasio)
{
    if (!gimnasio)
        return NULL;
    return gimnasio->tipo;
}

double gimnasio_obtener_efectividad_rival(gimnasio_t *gimnasio, const char *tipo_rival)
{
    if (!gimnasio)
        return -1;

    double *efectividad = hash_obtener(gimnasio->efectividades, tipo_rival);
    if (!efectividad)
        return -1;

    return *efectividad;
}

void gimnasio_destruir(gimnasio_t *gimnasio)
{
    free((void *)gimnasio->tipo);
    hash_destruir(gimnasio->efectividades);
    free(gimnasio);
}

gimnasio_t **gimnasio_inicializar_gimnasios()
{
    gimnasio_t **gimnasios = calloc(3, sizeof(gimnasio_t *));
    if (!gimnasios)
        return NULL;

    //inicializo gimnasio agua
    gimnasio_t *gimnasio_agua = gimnasio_crear("AGUA");

    gimnasio_agregar_efectividad(gimnasio_agua, "AGUA", NEUTRAL);
    gimnasio_agregar_efectividad(gimnasio_agua, "FUEGO", FUERTE);
    gimnasio_agregar_efectividad(gimnasio_agua, "PLANTA", DEBIL);
    //inicializo gimnasio FUEGO
    gimnasio_t *gimnasio_fuego = gimnasio_crear("FUEGO");
    gimnasio_agregar_efectividad(gimnasio_fuego, "AGUA", DEBIL);
    gimnasio_agregar_efectividad(gimnasio_fuego, "FUEGO", NEUTRAL);
    gimnasio_agregar_efectividad(gimnasio_fuego, "PLANTA", FUERTE);

    //inicializo gimnasio planta
    gimnasio_t *gimnasio_planta = gimnasio_crear("PLANTA");
    gimnasio_agregar_efectividad(gimnasio_planta, "AGUA", FUERTE);
    gimnasio_agregar_efectividad(gimnasio_planta, "FUEGO", DEBIL);
    gimnasio_agregar_efectividad(gimnasio_planta, "PLANTA", NEUTRAL);

    gimnasios[0] = gimnasio_agua;
    gimnasios[1] = gimnasio_fuego;
    gimnasios[2] = gimnasio_planta;

    if (!gimnasio_agua || !gimnasio_fuego || !gimnasio_planta) {
        gimnasio_destruir_gimnasios(gimnasios);
        return NULL;
    }

    return gimnasios;
}

void gimnasio_destruir_gimnasios(gimnasio_t **gimnasios)
{
    for (size_t i = 0; i < 3; i++) {
        if (gimnasios[i])
            gimnasio_destruir(gimnasios[i]);
    }
    free(gimnasios);
}