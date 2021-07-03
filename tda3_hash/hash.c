#include <string.h>
#include <stdlib.h>
#include "hash.h"

struct hash{
};


hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad_inicial){
  return NULL;
}


int hash_insertar(hash_t* hash, const char* clave, void* elemento){
  return 0;
}

int hash_quitar(hash_t* hash, const char* clave){
  return 0;
}

void* hash_obtener(hash_t* hash, const char* clave){
  return NULL;
}

size_t hash_cantidad(hash_t* hash){
  return 0;
}

bool hash_contiene(hash_t* hash, const char* clave){
  return false;
}

void hash_destruir(hash_t* hash){
}

size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){
  return 0;
}

