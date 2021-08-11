#include "entrenador.h"
#include "utils.h"
#include <string.h>

struct _entrenador_t
{
    char *nombre;
    int victorias;
    lista_t *equipo;
};

entrenador_t *entrenador_crear(char *nombre, int victorias)
{
    entrenador_t *entrenador = calloc(1, sizeof(entrenador_t));
    if (!entrenador)
        return NULL;
    entrenador->nombre = calloc(1, sizeof(char) * (strlen(nombre) + 1));
    if (!entrenador->nombre) {
        free(entrenador);
        return NULL;
    }
    strcpy(entrenador->nombre, nombre);
    entrenador->victorias = victorias;
    entrenador->equipo = lista_crear(pokemon_destruir);
    if (!entrenador->equipo) {
        free(entrenador->nombre);
        free(entrenador);
        return NULL;
    }
    return entrenador;
}

int entrenador_obtener_victorias(entrenador_t *entrenador)
{
    return (entrenador) ? entrenador->victorias : 0;
}

char *entrenador_obtener_nombre(entrenador_t *entrenador)
{
    return (entrenador) ? entrenador->nombre : NULL;
}

lista_t *entrenador_obtener_equipo(entrenador_t *entrenador)
{
    return (entrenador) ? entrenador->equipo : NULL;
}

/**
 * Recibe un entrenador y un pokemon. Encola al pokemon al final del equipo. Si pudo enconlar, retorna puntero al entrenador. Caso contrario, retorna NULL.
 **/
entrenador_t *entrenador_cargar_pokemon(entrenador_t *entrenador, pokemon_t *pokemon)
{
    int error_en_insercion = lista_encolar(entrenador_obtener_equipo(entrenador), pokemon);
    return (!error_en_insercion) ? entrenador : NULL;
}

void entrenador_liberar_equipo(entrenador_t *entrenador)
{
    if (entrenador->equipo) {
        lista_destruir(entrenador->equipo);
    }
}

void entrenador_destruir(void *entrenador)
{
    entrenador_t *entrenador_aux = (entrenador_t *)entrenador;
    free(entrenador_aux->nombre);
    entrenador_liberar_equipo(entrenador_aux);
    free(entrenador_aux);
}