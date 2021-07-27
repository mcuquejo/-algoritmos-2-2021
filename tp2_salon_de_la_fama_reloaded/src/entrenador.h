#ifndef ENTRENADOR_H_
#define ENTRENADOR_H_

#include <stdlib.h>
#include "lista.h"
#include "pokemon.h"

typedef struct _entrenador_t entrenador_t;

entrenador_t* entrenador_crear(char* nombre, int victorias);

int entrenador_obtener_victorias(entrenador_t* entrenador);

char* entrenador_obtener_nombre(entrenador_t* entrenador);

lista_t* entrenador_obtener_equipo(entrenador_t* entrenador);

entrenador_t* entrenador_cargar_pokemon(entrenador_t* entrenador, pokemon_t* pokemon);

void entrenador_destruir(void* entrenador);

#endif // ENTRENADOR_H_
