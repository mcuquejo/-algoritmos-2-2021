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


//la dejo modularizada por si quisiera cambiar la funcion de hash. Pensé en un puntero a funcion pero conllevaba tocar en más lugares
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


//CUANDO ACTUALIZO CLAVE NO TENGO QUE AUMENTAR CANTIDAD
bool insertar_nueva_posicion(hash_t* hash, const char* clave, void* elemento, size_t pos) {
  if(pos >= hash->capacidad_total)
    return false;

  if(!hash->elementos[pos]) {
    elemento_t* elemento_nuevo = elemento_crear(clave, elemento);
    if(!elemento)
      return false;
    hash->elementos[pos] = elemento_nuevo;
    hash->cantidad_elementos++;
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



bool _insertar_nueva_posicion(hash_t* hash, elemento_t** elementos_nuevo, elemento_t* elemento, size_t pos) {
  if(pos >= hash->capacidad_total * 2) {
    return false;
  }

  if(!elementos_nuevo[pos]) {
    elementos_nuevo[pos] = elemento;
    return true;
  }

  if (strcmp(elementos_nuevo[pos]->clave, elemento->clave) == 0) {
        void* auxiliar = elementos_nuevo[pos]->valor;
        elementos_nuevo[pos]->valor = elemento;
        if(hash->destructor)
          hash->destructor(auxiliar);
        return true;
  }
  return _insertar_nueva_posicion(hash, elementos_nuevo, elemento, ++pos);
}


bool rehash(hash_t* hash) {
  printf("toco hacer rehash\n");

  elemento_t** elementos_nuevo = calloc(hash->capacidad_total * 2, sizeof(elemento_t));
  if (!elementos_nuevo)
    return false;

  for(size_t i = 0; i < hash->capacidad_total; i++) {
      size_t posicion = calcular_posicion(hash->elementos[i]->clave, hash->capacidad_total * 2);
      if(!elementos_nuevo[i]){
        elementos_nuevo[i] = hash->elementos[i];
      } else {
        bool resultado = _insertar_nueva_posicion(hash, elementos_nuevo, hash->elementos[i], posicion);
        if(!resultado) {
          free(elementos_nuevo);
          return false;
        }
      }
  }

  hash->capacidad_total *= 2;
  elemento_t** elemento_aux = hash->elementos;
  hash->elementos = elementos_nuevo;
  free(elemento_aux);

  return true;
}

int hash_insertar(hash_t* hash, const char* clave, void* elemento) {
  if(!hash || !clave) {
    return -1;
  }

  size_t posicion = calcular_posicion(clave, hash->capacidad_total);

  if(!hash->elementos[posicion]) {
    elemento_t* elemento_nuevo = elemento_crear(clave, elemento);
    if(!elemento)
      return -1;
    hash->elementos[posicion] = elemento_nuevo;
    hash->cantidad_elementos++;
  } else {
    bool resultado = insertar_nueva_posicion(hash, clave, elemento, posicion);
    if(!resultado)
      return -1;
  }

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

void hash_imprimir(hash_t* hash) {
    if(hash){
        for(size_t i = 0; i < hash->capacidad_total; i++) {
            (hash->elementos[i]) ? printf("posicion %zu -> clave: %s - valor: %s\n", i, hash->elementos[i]->clave, (char*)hash->elementos[i]->valor) : printf("no hay elemento en la posicion %zu\n", i);

        }
    }
}