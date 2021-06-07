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


nodo_abb_t* nodo_insertar(abb_t* arbol, nodo_abb_t* nodo, void* elemento) {
    if(!nodo) {
        nodo = nodo_crear();
        if(!nodo)
            return NULL;
        nodo->elemento = elemento;
        return nodo;
    }
    if(arbol->comparador(elemento, nodo->elemento) > 0)
        nodo->derecha = nodo_insertar(arbol, nodo->derecha, elemento);
    if(arbol->comparador(elemento, nodo->elemento) <= 0)
        nodo->izquierda = nodo_insertar(arbol, nodo->izquierda, elemento);
    return nodo;
}


int arbol_insertar(abb_t* arbol, void* elemento){
    if(!arbol)
        return -1;
    arbol->nodo_raiz = nodo_insertar(arbol, arbol->nodo_raiz, elemento);
    return (!arbol->nodo_raiz) ? -1 : 0;
}

bool es_hoja(nodo_abb_t* nodo) {
    return (!nodo->derecha && !nodo->izquierda);
}

bool tiene_un_hijo(nodo_abb_t* nodo) {
    return ((nodo->derecha != NULL && !nodo->izquierda) || (!nodo->derecha && nodo->izquierda != NULL));
}

bool tiene_dos_hijos(nodo_abb_t* nodo) {
    return (nodo->derecha != NULL && nodo->izquierda != NULL);
}

nodo_abb_t* _buscar_predecesor_inorden(nodo_abb_t* nodo) {
    if (!nodo->derecha)
        return nodo;
    return _buscar_predecesor_inorden(nodo->derecha);
}

nodo_abb_t* buscar_predecesor_inorden(nodo_abb_t* nodo) {
    return _buscar_predecesor_inorden(nodo->izquierda);
}


nodo_abb_t* eliminar_nodo(abb_t* arbol, nodo_abb_t* nodo, void* elemento) {
    if(!nodo)
        return NULL;

    nodo_abb_t* resultado = NULL;
    if (arbol->comparador(elemento, nodo->elemento) == 0) {
        if(es_hoja(nodo)){
            if(arbol->destructor)
                arbol->destructor(nodo->elemento);
            free(nodo);
            return NULL;
        }
        if(tiene_un_hijo(nodo)) {
            nodo_abb_t* hijo = (!nodo->derecha) ? nodo->izquierda : nodo->derecha;
            if(arbol->destructor)
                arbol->destructor(nodo->elemento);
            free(nodo);
            return hijo;
        }
        if(tiene_dos_hijos(nodo)) {
            nodo_abb_t* nodo_predecesor = buscar_predecesor_inorden(nodo);
            nodo_abb_t* nodo_auxiliar = nodo;
            nodo = nodo_predecesor;
            nodo->izquierda = nodo_auxiliar->izquierda;
            nodo->derecha = nodo_auxiliar->derecha;
            if(arbol->destructor)
                arbol->destructor(nodo_auxiliar->elemento);
            free(nodo_auxiliar);
            return nodo;

        }
    }
    if (arbol->comparador(elemento, nodo->elemento) > 0) {
        resultado = eliminar_nodo(arbol, nodo->derecha, elemento);
    } else {
        resultado = eliminar_nodo(arbol, nodo->izquierda, elemento);
    }
    return resultado;
}



int arbol_borrar(abb_t* arbol, void* elemento){
    if(arbol_vacio(arbol))
        return -1;
    nodo_abb_t* nodo_a_eliminar = eliminar_nodo(arbol, arbol->nodo_raiz, elemento);
    if (!nodo_a_eliminar)
        return 0;
    //dejo que falle hasta que implemente los distintos borrados
    //sin hijos
    //con un hijo
    //con dos hijos
    return 0;
}

nodo_abb_t* buscar_nodo(abb_t* arbol, nodo_abb_t* nodo, void* elemento) {
    if(!nodo)
        return NULL;

    nodo_abb_t* resultado = NULL;
    if (arbol->comparador(elemento, nodo->elemento) == 0) {
        return nodo;
    }
    if (arbol->comparador(elemento, nodo->elemento) > 0) {
        resultado = buscar_nodo(arbol, nodo->derecha, elemento);
    } else {
        resultado = buscar_nodo(arbol, nodo->izquierda, elemento);
    }
    return resultado;
}

void* arbol_buscar(abb_t* arbol, void* elemento){
    if(arbol_vacio(arbol))
        return NULL;
    nodo_abb_t* elemento_buscado = buscar_nodo(arbol, arbol->nodo_raiz, elemento);
    return (!elemento_buscado) ? NULL : elemento_buscado->elemento;
}


void* arbol_raiz(abb_t* arbol){
    return (arbol_vacio(arbol)) ? NULL : arbol->nodo_raiz->elemento;
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
