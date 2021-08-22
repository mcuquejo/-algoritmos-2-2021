#ifndef POKEMON_H
#define POKEMON_H

typedef struct _pokemon_t pokemon_t;

pokemon_t *pokemon_crear(char *nombre, int nivel, int fuerza, int inteligencia, int velocidad, int defensa);

char *pokemon_obtener_nombre(pokemon_t *pokemon);

int pokemon_obtener_nivel(pokemon_t *pokemon);

int pokemon_obtener_fuerza(pokemon_t *pokemon);

int pokemon_obtener_inteligencia(pokemon_t *pokemon);

int pokemon_obtener_velocidad(pokemon_t *pokemon);

int pokemon_obtener_defensa(pokemon_t *pokemon);

void pokemon_destruir(void *pokemon);

#endif /* POKEMON_H */