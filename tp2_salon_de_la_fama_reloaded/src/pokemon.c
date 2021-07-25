#include "pokemon.h"
#include "utils.h"
struct _pokemon_t {
    const char* nombre;
    int nivel;
    int fuerza;
    int inteligencia;
    int velocidad;
    int defensa;
};


pokemon_t* pokemon_crear(const char* nombre, int nivel, int fuerza, int inteligencia, int velocidad, int defensa) {
    pokemon_t* pokemon = malloc(sizeof(pokemon_t));

}