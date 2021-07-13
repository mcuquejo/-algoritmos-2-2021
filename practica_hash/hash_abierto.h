#ifndef HASH_ABIERTO_H_
#define HASH_ABIERTO_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct par {
    const char* clave;
    void* valor;
    struct par* siguiente;
} par_t;

typedef struct hash {
    size_t cantidad;
    size_t capacidad;
    par_t** tabla;
} hash_t;

hash_t* hash_crear(size_t capacidad_inicial);
void hash_destruir(hash_t* h);

bool hash_insertar(hash_t* h, const char* k, void* v);

void* hash_buscar(hash_t* h, const char* k);

bool hash_eliminar(hash_t* h, const char* k);

#endif // HASH_ABIERTO_H_