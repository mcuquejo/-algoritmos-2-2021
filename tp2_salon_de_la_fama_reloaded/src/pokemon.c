#include "pokemon.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

struct _pokemon_t
{
    char *nombre;
    int nivel;
    int fuerza;
    int inteligencia;
    int velocidad;
    int defensa;
};

pokemon_t *pokemon_crear(char *nombre, int nivel, int fuerza, int inteligencia, int velocidad, int defensa)
{
    pokemon_t *pokemon = calloc(1, sizeof(pokemon_t));

    if (!pokemon)
        return NULL;

    pokemon->nombre = calloc(1, sizeof(char) * (strlen(nombre) + 1));
    if (!pokemon->nombre)
    {
        free(pokemon);
        return NULL;
    }
    strcpy(pokemon->nombre, nombre);

    pokemon->nivel = nivel;
    pokemon->fuerza = fuerza;
    pokemon->inteligencia = inteligencia;
    pokemon->velocidad = velocidad;
    pokemon->defensa = defensa;

    return pokemon;
}

char *pokemon_obtener_nombre(pokemon_t *pokemon)
{
    return (pokemon) ? pokemon->nombre : NULL;
}

int pokemon_obtener_nivel(pokemon_t *pokemon)
{
    return (pokemon) ? pokemon->nivel : 0;
}

int pokemon_obtener_fuerza(pokemon_t *pokemon)
{
    return (pokemon) ? pokemon->fuerza : 0;
}

int pokemon_obtener_inteligencia(pokemon_t *pokemon)
{
    return (pokemon) ? pokemon->inteligencia : 0;
}

int pokemon_obtener_velocidad(pokemon_t *pokemon)
{
    return (pokemon) ? pokemon->velocidad : 0;
}

int pokemon_obtener_defensa(pokemon_t *pokemon)
{
    return (pokemon) ? pokemon->defensa : 0;
}

void pokemon_destruir(void *pokemon)
{
    if (pokemon)
    {
        free(((pokemon_t *)pokemon)->nombre);
        free(pokemon);
    }
}