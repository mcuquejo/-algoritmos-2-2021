#include "entrenador.h"
#include "utils.h"

struct _entrenador_t {
    const char* nombre;
    size_t victorias;
};

entrenador_t* entrenador_crear(const char* nombre, size_t victorias) {
    entrenador_t* entrenador = malloc(sizeof(entrenador));
    if (!entrenador)
        return NULL;
    entrenador->nombre = strdup_c99(nombre);
    if(!entrenador->nombre)  {
        free(entrenador);
        return NULL;
    }
    entrenador->victorias = victorias;
    return entrenador;
}

void entrenador_destruir(entrenador_t* entrenador) {
    free(entrenador->nombre);
    free(entrenador);
}