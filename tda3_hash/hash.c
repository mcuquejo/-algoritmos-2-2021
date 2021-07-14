#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include <stdio.h>

const int ERROR = -1;
const int EXITO = 0;
const int TAM_MINIMO_HASH = 3;


typedef struct par {
  const char* clave;
  void* valor;
} par_t;

struct hash {
  hash_destruir_dato_t destructor;
  size_t cantidad;
  size_t capacidad;
  par_t** tabla;
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


char* duplicar_string(const char* s){
  if(!s)
    return NULL;
  char* p = malloc(strlen(s)+1);
  strcpy(p,s);
  return p;
}


par_t* par_crear(const char* clave, void* valor) {
  par_t* par = calloc(1, sizeof(par_t));
  if(!par)
    return NULL;
  par->clave = duplicar_string(clave);
  if(!par->clave) {
      free(par);
      return NULL;
  }
  par->valor = valor;
  return par;
}

void borrar_tabla(par_t** tabla, size_t capacidad, hash_destruir_dato_t destructor, bool borrar_valor) {
    for(size_t i = 0; i < capacidad; i++) {
    if(tabla[i]){
        if(borrar_valor && destructor) {
        destructor(tabla[i]->valor);
        }
        free((void *) tabla[i]->clave);
    }
    free(tabla[i]);
  }
  free(tabla);
}

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad_inicial){
  hash_t* hash = calloc(1, sizeof(hash_t));
  if(!hash)
    return NULL;
  hash->destructor = destruir_elemento;
  hash->capacidad = (capacidad_inicial >= TAM_MINIMO_HASH) ? capacidad_inicial : TAM_MINIMO_HASH;
  hash->tabla = calloc(capacidad_inicial, sizeof(par_t));
  if(!hash->tabla){
    free(hash);
    return NULL;
  }
  return hash;
}


size_t nueva_posicion(hash_t* hash, size_t tope, size_t posicion, const char* clave) {
    posicion++;
    if (posicion >= tope)
        posicion = 0;

    while(hash->tabla[posicion] && strcmp(hash->tabla[posicion]->clave, clave) != 0) {
        posicion++;
        if (posicion >= tope)
        posicion = 0;
    }
    return posicion;
}

bool rehashear(hash_t* hash) {
    par_t** par_aux = hash->tabla;
    size_t cant_aux = hash->cantidad;
    size_t cap_aux = (hash->capacidad) ? hash->capacidad : 0;

    hash->tabla = calloc(hash->capacidad * 2, sizeof(par_t));
    if(!hash->tabla) {
        hash->tabla = par_aux;
        return false;
    }

    hash->capacidad *= 2;
    hash->cantidad = 0;

    for(size_t i = 0; i < cap_aux; i++) {
        if (par_aux[i]) {
            int resultado = hash_insertar(hash, par_aux[i]->clave, par_aux[i]->valor);
            if (resultado == ERROR){
                borrar_tabla(hash->tabla, hash->capacidad, hash->destructor, false);
                hash->capacidad = cap_aux;
                hash->cantidad = cant_aux;
                hash->tabla = par_aux;
                return false;
            }
        }
    }

    borrar_tabla(par_aux, cap_aux, hash->destructor, false);

    return true;
}

int hash_insertar(hash_t* hash, const char* clave, void* elemento) {
    if(!hash || !clave)
        return ERROR;

    if((hash->cantidad + 1) / hash->capacidad >= 0.75){
        bool exito = rehashear(hash);
        if (!exito)
            return ERROR;
    }

    size_t posicion = fnv_hashing(clave) % hash->capacidad;

    if (!hash->tabla[posicion]) {
        par_t* par = par_crear(clave, elemento);
        if(!par)
            return ERROR;
        hash->tabla[posicion] = par;
        hash->cantidad++;
        return EXITO;
    }
    if (strcmp(hash->tabla[posicion]->clave, clave) == 0) {
        void* valor_aux = hash->tabla[posicion]->valor;
        hash->tabla[posicion]->valor = elemento;
        if(hash->destructor)
            hash->destructor(valor_aux);
        return EXITO;
    }

    posicion = nueva_posicion(hash, hash->capacidad, posicion, clave);

    if (!hash->tabla[posicion]) {
        par_t* par = par_crear(clave, elemento);
        if(!par)
            return ERROR;
        hash->tabla[posicion] = par;
        hash->cantidad++;
        return EXITO;
    }

    void* valor_aux = hash->tabla[posicion]->valor;
    hash->tabla[posicion]->valor = elemento;
    if(hash->destructor)
        hash->destructor(valor_aux);
  return EXITO;
}

int hash_quitar(hash_t* hash, const char* clave) {
    return 0;
}

void* hash_obtener(hash_t* hash, const char* clave) {
    if(!hash || !clave)
        return NULL;

    size_t posicion = fnv_hashing(clave) % hash->capacidad;
    if(!hash->tabla[posicion])
        return NULL;

    if (strcmp(hash->tabla[posicion]->clave, clave) == 0)
        return hash->tabla[posicion]->valor;

    posicion = nueva_posicion(hash, hash->capacidad, posicion, clave);

    return (hash->tabla[posicion]) ? hash->tabla[posicion]->valor : NULL;
}

size_t hash_cantidad(hash_t* hash) {
  return (hash) ? hash->cantidad : 0;
}


bool hash_contiene(hash_t* hash, const char* clave) {
    return hash_obtener(hash, clave) != NULL;
}

void hash_destruir(hash_t* hash) {
  borrar_tabla(hash->tabla, hash->capacidad, hash->destructor, true);
  free(hash);
}

size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){
  return 0;
}

void hash_imprimir(hash_t* hash) {
    if(hash){
        for(size_t i = 0; i < hash->capacidad; i++) {
            (hash->tabla[i]) ? printf("posicion %zu -> clave: %s - valor: %s\n", i, hash->tabla[i]->clave, *(char**)hash->tabla[i]->valor) : printf("no hay elemento en la posicion %zu\n", i);

        }
    }
}
