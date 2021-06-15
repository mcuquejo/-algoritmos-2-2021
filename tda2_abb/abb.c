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

nodo_abb_t* _buscar_predecesor_inorden(nodo_abb_t* nodo, nodo_abb_t** extraido) {
    if(!nodo)
        return NULL;
    if(nodo->derecha) {
        nodo->derecha = _buscar_predecesor_inorden(nodo->derecha, extraido);
        return nodo;
    }
    *extraido = nodo;
    return nodo->izquierda;
}

nodo_abb_t* buscar_predecesor_inorden(nodo_abb_t* nodo) {
    nodo_abb_t* extraido = NULL;
    nodo->izquierda = _buscar_predecesor_inorden(nodo->izquierda, &extraido);
    return extraido;
}


nodo_abb_t* eliminar_nodo(abb_t* arbol, nodo_abb_t* nodo, void* elemento, int* pudo_eliminar) {
    if(!nodo)
        return NULL;

    if (arbol->comparador(elemento, nodo->elemento) == 0) {
        if(es_hoja(nodo)) {
            if(arbol->destructor)
                arbol->destructor(nodo->elemento);
            free(nodo);
            *pudo_eliminar = 0;
            return NULL;
        }
        if(tiene_un_hijo(nodo)) {
            nodo_abb_t* hijo = (!nodo->derecha) ? nodo->izquierda : nodo->derecha;
            if(arbol->destructor)
                arbol->destructor(nodo->elemento);
            free(nodo);
            *pudo_eliminar = 0;
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
            *pudo_eliminar = 0;
            return nodo;
        }
    }
    if (arbol->comparador(elemento, nodo->elemento) > 0) {
        nodo->derecha = eliminar_nodo(arbol, nodo->derecha, elemento, pudo_eliminar);
    } else {
        nodo->izquierda =  eliminar_nodo(arbol, nodo->izquierda, elemento, pudo_eliminar);
    }
    return nodo;
}



int arbol_borrar(abb_t* arbol, void* elemento){
    int pudo_eliminar = -1;
    if(arbol_vacio(arbol))
        return pudo_eliminar;
    arbol->nodo_raiz = eliminar_nodo(arbol, arbol->nodo_raiz, elemento, &pudo_eliminar);
    return pudo_eliminar;
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


void _arbol_recorrido_inorden(nodo_abb_t* nodo, void** array, size_t* tamanio_array, size_t* contador) {
    if(!nodo)
        return;
    _arbol_recorrido_inorden(nodo->izquierda, array, tamanio_array, contador);

    if(*tamanio_array > 0) {
        array[(*contador)++] = nodo->elemento;
        (*tamanio_array)--;
    }
    _arbol_recorrido_inorden(nodo->derecha, array, tamanio_array, contador);
}


size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
    size_t contador = 0;
    if(array != NULL && arbol != NULL)
        _arbol_recorrido_inorden(arbol->nodo_raiz, array, &tamanio_array, &contador);
    return contador;
}


void _arbol_recorrido_preorden(nodo_abb_t* nodo, void** array, size_t* tamanio_array, size_t* contador) {
    if(!nodo)
        return;
    if(*tamanio_array > 0) {
        array[(*contador)++] = nodo->elemento;
        (*tamanio_array)--;
    }
    _arbol_recorrido_preorden(nodo->izquierda, array, tamanio_array, contador);
    _arbol_recorrido_preorden(nodo->derecha, array, tamanio_array, contador);
}

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
    size_t contador = 0;
    if (array != NULL && arbol != NULL)
        _arbol_recorrido_preorden(arbol->nodo_raiz, array, &tamanio_array, &contador);
    return contador;
}

void _arbol_recorrido_postorden(nodo_abb_t* nodo, void** array, size_t* tamanio_array, size_t* contador) {
    if(!nodo)
        return;
    _arbol_recorrido_postorden(nodo->izquierda, array, tamanio_array, contador);
    _arbol_recorrido_postorden(nodo->derecha, array, tamanio_array, contador);
    if(*tamanio_array > 0) {
        array[(*contador)++] = nodo->elemento;
        (*tamanio_array)--;
    }
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
    size_t contador = 0;
    if (array != NULL && arbol != NULL)
        _arbol_recorrido_postorden(arbol->nodo_raiz, array, &tamanio_array , &contador);
    return contador;
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


void abb_con_cada_elemento_preorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void *extra, size_t* contador, bool* finalizar) {
    if(!nodo)
        return;
    if(!*finalizar) {
        (*contador)++;
        *finalizar = funcion(nodo->elemento, extra);
        if(*finalizar) {
            return;
        }
    }

    abb_con_cada_elemento_preorden(nodo->izquierda, funcion, extra, contador, finalizar);
    abb_con_cada_elemento_preorden(nodo->derecha, funcion, extra, contador, finalizar);
}

void abb_con_cada_elemento_inorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void *extra, size_t* contador, bool* finalizar) {
    if(!nodo)
        return;
    abb_con_cada_elemento_inorden(nodo->izquierda, funcion, extra, contador, finalizar);
    if(!*finalizar) {
        (*contador)++;
        *finalizar = funcion(nodo->elemento, extra);
        if(*finalizar) {
            return;
        }
    }
    abb_con_cada_elemento_inorden(nodo->derecha, funcion, extra, contador, finalizar);
}

void abb_con_cada_elemento_postorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void *extra, size_t* contador, bool* finalizar) {
    if(!nodo)
        return;
    abb_con_cada_elemento_postorden(nodo->izquierda, funcion, extra, contador, finalizar);
    abb_con_cada_elemento_postorden(nodo->derecha, funcion, extra, contador, finalizar);
    if(!*finalizar) {
        (*contador)++;
        *finalizar = funcion(nodo->elemento, extra);
        if(*finalizar) {
            return;
        }
    }
}

size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
    size_t contador = 0;
    bool finalizar = false;
    if(!arbol || !funcion)
        return contador;
    nodo_abb_t* nodo_actual = arbol->nodo_raiz;
    if (recorrido == ABB_RECORRER_PREORDEN)
        abb_con_cada_elemento_preorden(nodo_actual, funcion, extra, &contador, &finalizar);
    if (recorrido == ABB_RECORRER_INORDEN)
        abb_con_cada_elemento_inorden(nodo_actual, funcion, extra, &contador, &finalizar);
    if (recorrido == ABB_RECORRER_POSTORDEN)
        abb_con_cada_elemento_postorden(nodo_actual, funcion, extra, &contador, &finalizar);
    return contador;
}
