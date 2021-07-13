#include "hash_abierto.h"
#include <string.h>
#include <stdio.h>

hash_t* hash_crear(size_t capacidad_inicial) {
    hash_t* hash = calloc(1, sizeof(hash_t));

    if(!hash)
        return NULL;

    hash->capacidad = capacidad_inicial;
    hash->tabla = calloc(capacidad_inicial, sizeof(par_t*));
    if(!hash->tabla){
        free(hash);
        return NULL;
    }

    return hash;
}

void hash_destruir(hash_t* h){}

size_t funcion_hash(const char* clave){
    size_t  valor = 0;

    while(*clave){
        valor += *clave;
        clave++;
    }
    return valor;
}

char* duplicar_string(const char* s){
  if(!s)
    return NULL;

  char* p = malloc(strlen(s)+1);
  strcpy(p,s);
  return p;
}

par_t* par_crear(const char* k, void* v) {
    par_t* par = malloc(sizeof(par_t));
    if(!par)
        return NULL;
    par->clave = duplicar_string(k);
    par->valor = v;

    if(!par->clave){
        free(par);
        return NULL;
    }

    return par;
}

bool rehashear(hash_t* h){
    hash_t hash_auxiliar = *h;

    h->tabla = calloc(h->capacidad * 2, sizeof(par_t));
    h->capacidad *= 2;
    h->cantidad = 0;

    printf("%zu\n", hash_auxiliar.cantidad);

    //itero hash_aux e inserto en h
    //itero hash_aux y traspaso los elementos (esta es mejor)
    return true;
}

bool hash_insertar(hash_t* h, const char* k, void* v){
    size_t hash = funcion_hash(k);
    size_t posicion = hash % h->capacidad;

    //rehashear en algun momento

    if(!h->tabla[posicion]) {
        par_t* par = par_crear(k, v);
        if(!par)
            return false;
        h->tabla[posicion] = par;
        return true;
    }

    par_t* actual = h->tabla[posicion];
    while(actual && strcmp(actual->clave, k) != 0)
        actual = actual->siguiente;

    if(actual) {
        printf("aca esta actualizando clave\n");
        actual->valor = v;
        return true;
    }

    par_t* par = par_crear(k,v);
    if(!par)
        return false;

    printf("Colision\n");
    par->siguiente = h->tabla[posicion];
    h->tabla[posicion] = par;
    return true;
}

void* hash_buscar(hash_t* h, const char* k){
    size_t hash = funcion_hash(k);
    size_t posicion = hash % h->capacidad;

    par_t* actual = h->tabla[posicion];
    while(actual && strcmp(actual->clave, k) != 0)
        actual = actual->siguiente;

    if(!actual)
        return NULL;
    return actual->valor;
}

bool hash_eliminar(hash_t* h, const char* k){
    size_t hash = funcion_hash(k);
    size_t posicion = hash % h->capacidad;

    par_t* anterior = NULL;
    par_t* actual = h->tabla[posicion];
    while(actual && strcmp(actual->clave, k) != 0) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if(!actual)
        return false;

    if(anterior) {
        anterior->siguiente = actual->siguiente;
        free((char*)actual->clave);
        //aca habria que destruir el elemento con un destructor
        free(actual);
        return true;
    }

    par_t* primero = h->tabla[posicion];
    h->tabla[posicion] = h->tabla[posicion]->siguiente;

    free((char*)primero->clave);
    //aca habria que destruir el elemento con un destructor
    free(primero);
    return true;
}