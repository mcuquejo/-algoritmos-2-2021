#include "abb.h"

nodo_abb_t* nodo_crear() {
    nodo_abb_t* nodo = calloc(1, sizeof(nodo_abb_t));
    return nodo;
}


abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor) {
    if(!comparador)
        return NULL;

    abb_t* arbol = calloc(1, sizeof(abb_t));
    if(arbol) {
        arbol->comparador = comparador;
        arbol->destructor = destructor;
    }
    return arbol;
}


nodo_abb_t* nodo_insertar(abb_comparador comparador, nodo_abb_t* nodo, void* elemento) {
    if(!nodo) {
        nodo = nodo_crear();
        if(!nodo)
            return NULL;
        nodo->elemento = elemento;
        return nodo;
    }
    if(comparador(elemento, nodo->elemento) > 0)
        nodo->derecha = nodo_insertar(comparador, nodo->derecha, elemento);
    if(comparador(elemento, nodo->elemento) <= 0)
        nodo->izquierda = nodo_insertar(comparador, nodo->izquierda, elemento);
    return nodo;
}


int arbol_insertar(abb_t* arbol, void* elemento){
    if(!arbol)
        return -1;
    arbol->nodo_raiz = nodo_insertar(arbol->comparador, arbol->nodo_raiz, elemento);
    return (!arbol->nodo_raiz) ? -1 : 0;
}


nodo_abb_t* buscar_nodo(abb_comparador comparador, nodo_abb_t* nodo, void* elemento) {
    if(!nodo)
        return NULL;

    nodo_abb_t* resultado = NULL;
    if (comparador(elemento, nodo->elemento) == 0) {
        return nodo;
    }
    if (comparador(elemento, nodo->elemento) > 0) {
        resultado = buscar_nodo(comparador, nodo->derecha, elemento);
    } else {
        resultado = buscar_nodo(comparador, nodo->izquierda, elemento);
    }
    return resultado;
}


int arbol_borrar(abb_t* arbol, void* elemento){
    if(arbol_vacio(arbol))
        return -1;
    nodo_abb_t* nodo_a_eliminar = buscar_nodo(arbol->comparador, arbol->nodo_raiz, elemento);
    if (!nodo_a_eliminar)
        return -1;
    return 0;
}


void* arbol_buscar(abb_t* arbol, void* elemento){
    if(arbol_vacio(arbol))
        return NULL;
    nodo_abb_t* elemento_buscado = buscar_nodo(arbol->comparador, arbol->nodo_raiz, elemento);
    return (!elemento_buscado) ? NULL : elemento_buscado->elemento;
}


void* arbol_raiz(abb_t* arbol){
    if(!arbol)
        return NULL;
    if(!arbol->nodo_raiz)
        return NULL;
    return arbol->nodo_raiz->elemento;
}


bool arbol_vacio(abb_t* arbol){
    if (!arbol)
        return true;
    return (!arbol->nodo_raiz);
}


size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
    return 0;
}


size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
    return 0;
}


size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
    return 0;
}


void liberar_nodos(nodo_abb_t* nodo, abb_liberar_elemento destructor) {
    if (!nodo)
        return;
    liberar_nodos(nodo->izquierda, destructor);
    liberar_nodos(nodo->derecha, destructor);

    if(destructor)
        destructor(nodo->elemento);
    free(nodo);
}


void arbol_destruir(abb_t* arbol){
    if(!arbol)
        return;
    liberar_nodos(arbol->nodo_raiz, arbol->destructor);
    free(arbol);
}


size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
    return 0;
}
