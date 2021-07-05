#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include <stdio.h>

typedef struct elemento {
  const char* clave;
  void* valor;
} elemento_t;

struct hash {
  hash_destruir_dato_t destructor;
  size_t cantidad_elementos;
  size_t capacidad_total;
  elemento_t** elementos;
};


long fnv_hashing(const char* clave) {
  long h = 1469591039346656037;
  int n = strlen(clave);
  for (size_t i = 0; i < n; i++) {
    h *= 1099511628211;
    h ^= clave[i];
  }
  return h;
}



int calcular_posicion(const char* clave, size_t tamanio_hash){
  return fnv_hashing(clave) % tamanio_hash;
}

elemento_t* elemento_crear(const char* clave, void* valor) {
  elemento_t* elemento = malloc(sizeof(elemento_t));
  if(!elemento)
    return NULL;

  elemento->clave = clave;
  elemento->valor = valor;
  return elemento;
}

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad_inicial){
  hash_t* hash = calloc(1, sizeof(hash_t));
  if(!hash)
    return NULL;
  hash->destructor = destruir_elemento;
  hash->capacidad_total = (capacidad_inicial >= 3) ? capacidad_inicial : 3;
  hash->elementos = calloc(capacidad_inicial, sizeof(elemento_t));
  if(!hash->elementos){
    free(hash);
    return NULL;
  }
  return hash;
}


bool insertar_nueva_posicion(hash_t* hash, const char* clave, void* elemento, size_t pos) {
  if(pos >= hash->capacidad_total) {
    printf("fallo la insercion para el elemento %s\n", *(char**)elemento);
    return false;
  }

  printf("Entra y entra y cap total: %li, pos: %li\n", hash->capacidad_total, pos);

  if(!hash->elementos[pos]) {
    elemento_t* elemento_nuevo = elemento_crear(clave, elemento);
    if(!elemento)
      return false;
    printf("posicion en donde va a insertar: %li\n", pos);
    hash->elementos[pos] = elemento_nuevo;
    return true;
  }

  if (strcmp(hash->elementos[pos]->clave, clave) == 0) {
        void* auxiliar = hash->elementos[pos]->valor;
        hash->elementos[pos]->valor = elemento;
        if(hash->destructor)
          hash->destructor(auxiliar);
        return true;
  }
  return insertar_nueva_posicion(hash, clave, elemento, ++pos);
}


bool rehash(hash_t* hash) {
  printf("toco hacer rehash\n");
  return true;
}

int hash_insertar(hash_t* hash, const char* clave, void* elemento) {
  if(!hash || !clave) {
    return -1;
  }

  size_t posicion = calcular_posicion(clave, hash->capacidad_total);
  printf("El elemento %s deberia ser insertado en la posicion: %li\n", *(char**)elemento, posicion);

  //rehashear en algun momento.

  if(!hash->elementos[posicion]) {
    elemento_t* elemento_nuevo = elemento_crear(clave, elemento);
    if(!elemento)
      return -1;
    hash->elementos[posicion] = elemento_nuevo;
  } else {
    bool resultado = insertar_nueva_posicion(hash, clave, elemento, posicion);
    if(!resultado)
      return -1;
  }

  hash->cantidad_elementos++;

  if(hash->cantidad_elementos / hash->capacidad_total >= 0.75) {
    bool resultado = rehash(hash);
    return (resultado) ? 0 : -1;
  }
  return 0;
}

int hash_quitar(hash_t* hash, const char* clave) {
  return 0;
}

elemento_t* elemento_obtener(hash_t* hash, size_t pos, const char* clave) {
  if (!hash->elementos[pos] || pos > hash->capacidad_total)
    return NULL;
  if(strcmp(hash->elementos[pos]->clave, clave) == 0)
    return hash->elementos[pos];
  return elemento_obtener(hash, ++pos, clave);
}

void* hash_obtener(hash_t* hash, const char* clave){
  if(!hash || !clave)
    return NULL;
  size_t posicion = calcular_posicion(clave, hash->capacidad_total);
  elemento_t* elemento_buscado = elemento_obtener(hash, posicion, clave);
  return (elemento_buscado) ? elemento_buscado->valor : NULL;
}

size_t hash_cantidad(hash_t* hash) {
  return (hash) ? hash->cantidad_elementos : 0;
}


bool hash_contiene(hash_t* hash, const char* clave){
  if(!hash || !clave)
    return false;
  size_t posicion = calcular_posicion(clave, hash->capacidad_total);
  elemento_t* elemento_buscado = elemento_obtener(hash, posicion, clave);
  return (elemento_buscado != NULL);
}

void hash_destruir(hash_t* hash) {
  for(size_t i = 0; i < hash->capacidad_total; i++) {
    if(hash->destructor) {
      hash->destructor(hash->elementos[i]->valor);
    }
    free(hash->elementos[i]);
  }
  free(hash->elementos);
  free(hash);
}

size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){
  return 0;
}

