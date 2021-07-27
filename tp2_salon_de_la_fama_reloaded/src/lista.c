#include "lista.h"
#include <stdlib.h>

lista_t* lista_crear(lista_liberar_elemento destructor){
    lista_t* lista = calloc(1, sizeof(lista_t));
    if(!lista)
        return NULL;
    lista->destructor = destructor;
    return lista;
}

/*
 * Crea un nodo reservando el espacio necesario en memoria.
 * Devuelve un puntero al nodo creado o NULL en caso de error.
 */
nodo_t* lista_nodo_crear(void* elemento) {
    nodo_t* nodo = calloc(1, sizeof(nodo_t));
    if (!nodo)
        return NULL;
    nodo->elemento = elemento;
    return nodo;
}

int lista_insertar(lista_t* lista, void* elemento){
    if(!lista)
        return -1;
    nodo_t* nodo = lista_nodo_crear(elemento);
    if(!nodo)
        return -1;
    if (lista_vacia(lista)) {
        lista->nodo_inicio = nodo;
        lista->nodo_fin = nodo;
    } else {
        lista->nodo_fin->siguiente = nodo;
        lista->nodo_fin = nodo;
    }
    lista->cantidad++;
    return 0;
}

/*
 * Inserta un elemento al inicio de la lista
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar_al_inicio(lista_t* lista, void* elemento) {
    if(!lista)
        return -1;
    if(lista_vacia(lista))
        return lista_insertar(lista, elemento);

    nodo_t* nodo = lista_nodo_crear(elemento);
    if(!nodo)
        return -1;
    nodo->siguiente = lista->nodo_inicio;
    lista->nodo_inicio = nodo;
    lista->cantidad++;
    return 0;
}

/*
 * Navega los nodos siguientes al nodo inicial posicion - 1 veces y retorna el nodo que se encuentre en dicha posicion.
 */
nodo_t* obtener_nodo_anterior_posicion(nodo_t* nodo, size_t posicion) {
    if (posicion == 1)
        return nodo;
    return obtener_nodo_anterior_posicion(nodo->siguiente, posicion-1);
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
    if(!lista)
        return -1;
    if(posicion == 0)
        return lista_insertar_al_inicio(lista, elemento);
    if(posicion >= lista_elementos(lista))
        return lista_insertar(lista, elemento);
    nodo_t* nodo_nuevo = lista_nodo_crear(elemento);
    if(!nodo_nuevo)
        return -1;

    nodo_t* nodo_auxiliar_anterior = obtener_nodo_anterior_posicion(lista->nodo_inicio, posicion);
    nodo_t* nodo_auxiliar_siguiente = nodo_auxiliar_anterior->siguiente;
    nodo_auxiliar_anterior->siguiente = nodo_nuevo;
    nodo_nuevo->siguiente = nodo_auxiliar_siguiente;
    lista->cantidad++;

    return 0;
}

/*
 * Quita de la lista el elemento que se encuentra en la primera posicion.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar_primero(lista_t* lista) {
    if(!lista)
        return -1;
    if (lista_vacia(lista))
        return -1;
    nodo_t* nodo_auxiliar = lista->nodo_inicio;
    lista->nodo_inicio = nodo_auxiliar->siguiente;
    lista->cantidad--;
    if (lista_elementos(lista) == 1)
        lista->nodo_fin = lista->nodo_inicio;
    if(lista_vacia(lista)) {
        lista->nodo_inicio = NULL;
        lista->nodo_fin = NULL;
    }
    if(lista->destructor)
        lista->destructor(nodo_auxiliar->elemento);
    free(nodo_auxiliar);
    return 0;
}

int lista_borrar(lista_t* lista){
    if(!lista)
        return -1;
    if (lista_vacia(lista))
        return -1;

    if (lista->nodo_inicio != lista->nodo_fin) {
        nodo_t* nodo_anterior_auxiliar = obtener_nodo_anterior_posicion(lista->nodo_inicio, lista->cantidad - 1);
        nodo_anterior_auxiliar->siguiente = lista->nodo_fin->siguiente;
        if(lista->destructor)
            lista->destructor(lista->nodo_fin->elemento);
        free(lista->nodo_fin);
        lista->nodo_fin = nodo_anterior_auxiliar;
        if (lista_elementos(lista) == 1)
            lista->nodo_fin = lista->nodo_inicio;
    } else {
        if(lista->destructor)
            lista->destructor(lista->nodo_fin->elemento);
        free(lista->nodo_fin);
        lista->nodo_inicio = NULL;
        lista->nodo_fin = NULL;
    }

    lista->cantidad--;

    return 0;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
    if(!lista)
        return -1;
    if (lista_vacia(lista))
        return -1;

    if(posicion == 0)
        return lista_borrar_primero(lista);
    if(posicion >= lista_elementos(lista) - 1)
        return lista_borrar(lista);

    nodo_t* nodo_auxiliar_anterior = obtener_nodo_anterior_posicion(lista->nodo_inicio, posicion);
    nodo_t* nodo_auxiliar_a_borrar = nodo_auxiliar_anterior->siguiente;
    nodo_auxiliar_anterior->siguiente = nodo_auxiliar_a_borrar->siguiente;
    if(lista->destructor)
        lista->destructor(nodo_auxiliar_a_borrar->elemento);
    free(nodo_auxiliar_a_borrar);
    lista->cantidad--;

    return 0;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
    if(!lista)
        return NULL;
    if(lista_vacia(lista) || posicion >= lista_elementos(lista))
        return NULL;
    if(posicion == lista_elementos(lista) - 1)
        return lista_ultimo(lista);
    if(posicion == 0)
        return lista_primero(lista);
    nodo_t* nodo_auxiliar_anterior = obtener_nodo_anterior_posicion(lista->nodo_inicio, posicion);
    return nodo_auxiliar_anterior->siguiente->elemento;
}

void* lista_ultimo(lista_t* lista){
    if(!lista)
        return NULL;
    return (lista_vacia(lista)) ? NULL : lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t* lista){
    if(!lista)
        return true;
    return lista_elementos(lista) == 0;
}

size_t lista_elementos(lista_t* lista){
    if(!lista)
        return 0;
    return lista->cantidad;
}

int lista_apilar(lista_t* lista, void* elemento){
    return lista_insertar(lista, elemento);
}

int lista_desapilar(lista_t* lista){
    return lista_borrar(lista);
}

void* lista_tope(lista_t* lista){
    return lista_ultimo(lista);
}

int lista_encolar(lista_t* lista, void* elemento){
    return lista_insertar(lista, elemento);
}

int lista_desencolar(lista_t* lista){
    return lista_borrar_primero(lista);
}

void* lista_primero(lista_t* lista){
    if(!lista)
        return NULL;
    return (lista_vacia(lista)) ? NULL : lista->nodo_inicio->elemento;
}

void lista_destruir(lista_t* lista){
    while(lista_elementos(lista) > 0)
        lista_borrar_primero(lista);
    free(lista);
}

lista_iterador_t* lista_iterador_crear(lista_t* lista) {
    if (!lista)
        return NULL;

    lista_iterador_t* iterador = calloc(1, sizeof(lista_iterador_t));
    if (!iterador)
        return NULL;
    iterador->lista = lista;
    iterador->corriente = lista->nodo_inicio;
    return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador) {
    if(!iterador)
        return false;
    return iterador->corriente != NULL;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador) {
    if (!lista_iterador_tiene_siguiente(iterador))
        return false;
    iterador->corriente = iterador->corriente->siguiente;
    return iterador->corriente != NULL;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador) {
    if(!iterador)
        return NULL;
    if (!iterador->corriente)
        return NULL;
    return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t* iterador){
    free(iterador);
}

size_t _lista_con_cada_elemento(nodo_t* nodo, bool (*funcion)(void*, void*), void *contexto, bool* continuar) {
    if(!nodo)
        return 0;
    *continuar = funcion(nodo->elemento, contexto);
    if(*continuar)
        return 1 + _lista_con_cada_elemento(nodo->siguiente, funcion, contexto, continuar);
    return 1;
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto) {
    if(!lista || !funcion || !contexto)
        return 0;
    nodo_t* nodo_actual = lista->nodo_inicio;
    bool continuar = true;
    return _lista_con_cada_elemento(nodo_actual, funcion, contexto, &continuar);
}


