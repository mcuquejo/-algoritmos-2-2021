#include "abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"


int comparar_elementos_tipo_int(void* elemento1, void* elemento2) {
  return *(int*)elemento1 - *(int*)elemento2;
}

void destruir_elemento(void* elemento) {
  if (elemento)
    free(elemento);
}

void dadoUnABBNull_SiCreoUnABBSinComparador_ElABBSigueSiendoNull() {
  abb_t* arbol_bb = NULL;

  arbol_bb = arbol_crear(NULL, NULL);
  pa2m_afirmar(arbol_bb == NULL, "El arbol sigue siendo NULL porque no se puede crear sin pasar una funcion comparadora");
  arbol_destruir(arbol_bb);
}

void dadoUnABBNull_SiCreoUnABB_ResultaUnABBNoNullYVacio() {
  abb_t* arbol_bb = NULL;
  pa2m_afirmar(arbol_vacio(arbol_bb), "El ABB NULL esta vacio");
  arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  pa2m_afirmar(arbol_bb != NULL, "El ABB ya no es NULL");
  pa2m_afirmar(arbol_vacio(arbol_bb), "El ABB esta vacio");

  arbol_destruir(arbol_bb);
}

void dadoUnABBVacio_SiInsertoDatos_ElABBYaNoEstaVacio() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int dato1 = 1;
  arbol_insertar(arbol_bb, &dato1);
  pa2m_afirmar(!arbol_vacio(arbol_bb), "El ABB ya no esta vacio");

  arbol_destruir(arbol_bb);

}

void dadoUnABBNull_SiInsertoDatos_NoPermiteInsertarDatosEnUnABBNull (){
  abb_t* arbol_bb = NULL;
  int dato1 = 1;
  pa2m_afirmar(arbol_insertar(arbol_bb, &dato1) == -1, "No permite insertar datos en un ABB NULL");

  arbol_destruir(arbol_bb);

}

void dadoUnABBVacio_SiInsertoDatosEnOrdenABC_LosDatosSeInsertanEnElOrdenCorrecto() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int dato1 = 1;
  int dato2 = 2;
  int dato3 = 3;
  arbol_insertar(arbol_bb, &dato1);
  arbol_insertar(arbol_bb, &dato2);
  arbol_insertar(arbol_bb, &dato3);
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->elemento == 1, "El nodo RAIZ tiene valor 1");

  pa2m_afirmar(arbol_bb->nodo_raiz->izquierda == NULL, "El nodo RAIZ->HIJO_IZQ es NULL");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->elemento == 2, "El nodo RAIZ->HIJO_DER tiene valor 2");

  pa2m_afirmar(arbol_bb->nodo_raiz->derecha->izquierda == NULL, "El nodo RAIZ->HIJO_DER->HIJO_IZQ es NULL");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->derecha->elemento == 3, "El nodo RAIZ->HIJO_DER->HIJO_DER tiene valor 3");

  pa2m_afirmar(arbol_bb->nodo_raiz->derecha->derecha->izquierda == NULL, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_IZQ es NULL");
  pa2m_afirmar(arbol_bb->nodo_raiz->derecha->derecha->derecha == NULL, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_DER es NULL");

  arbol_destruir(arbol_bb);
}

void dadoUnABBVacio_SiInsertoDatosEnOrdenACB_LosDatosSeInsertanEnElOrdenCorrecto() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int dato1 = 1;
  int dato2 = 2;
  int dato3 = 3;
  arbol_insertar(arbol_bb, &dato1);
  arbol_insertar(arbol_bb, &dato3);
  arbol_insertar(arbol_bb, &dato2);
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->elemento == 1, "El nodo RAIZ tiene valor 1");

  pa2m_afirmar(arbol_bb->nodo_raiz->izquierda == NULL, "El nodo RAIZ->HIJO_IZQ es NULL");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->elemento == 3, "El nodo RAIZ->HIJO_DER tiene valor 3");

  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->izquierda->elemento == 2, "El nodo RAIZ->HIJO_DER->HIJO_IZQ tiene valor 2");
  pa2m_afirmar(arbol_bb->nodo_raiz->derecha->derecha == NULL, "El nodo RAIZ->HIJO_DER->HIJO_DER es NULL");

  pa2m_afirmar(arbol_bb->nodo_raiz->derecha->izquierda->izquierda == NULL, "El nodo RAIZ->HIJO_DER->HIJO_IZQ->HIJO_IZQ es NULL");
  pa2m_afirmar(arbol_bb->nodo_raiz->derecha->izquierda->derecha == NULL, "El nodo RAIZ->HIJO_DER->HIJO_IZQ->HIJO_DER es NULL");

  arbol_destruir(arbol_bb);
}

void dadoUnABBVacio_SiInsertoDatosEnOrdenCBA_LosDatosSeInsertanEnElOrdenCorrecto() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int dato1 = 1;
  int dato2 = 2;
  int dato3 = 3;
  arbol_insertar(arbol_bb, &dato3);
  arbol_insertar(arbol_bb, &dato2);
  arbol_insertar(arbol_bb, &dato1);
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->elemento == 3, "El nodo RAIZ tiene valor 3");

  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->izquierda->elemento == 2, "El nodo RAIZ->HIJO_IZQ tiene valor 2");
  pa2m_afirmar(arbol_bb->nodo_raiz->derecha == NULL, "El nodo RAIZ->HIJO_DER es NULL");

  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->izquierda->izquierda->elemento == 1, "El nodo RAIZ->HIJO_IZQ->HIJO_IZQ tiene valor 1");
  pa2m_afirmar(arbol_bb->nodo_raiz->izquierda->derecha == NULL, "El nodo RAIZ->HIJO_IZQ->HIJO_DER es NULL");

  pa2m_afirmar(arbol_bb->nodo_raiz->izquierda->izquierda->izquierda == NULL, "El nodo RAIZ->HIJO_IZQ->HIJO_IZQ->HIJO_IZQ es NULL");
  pa2m_afirmar(arbol_bb->nodo_raiz->izquierda->izquierda->derecha == NULL, "El nodo RAIZ->HIJO_IZQ->HIJO_IZQ->HIJO_DER es NULL");

  arbol_destruir(arbol_bb);
}

void dadoUnABBVacio_SiInsertoDatosEnOrdenCAB_LosDatosSeInsertanEnElOrdenCorrecto() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int dato1 = 1;
  int dato2 = 2;
  int dato3 = 3;
  arbol_insertar(arbol_bb, &dato3);
  arbol_insertar(arbol_bb, &dato1);
  arbol_insertar(arbol_bb, &dato2);
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->elemento == 3, "El nodo RAIZ tiene valor 3");

  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->izquierda->elemento == 1, "El nodo RAIZ->HIJO_IZQ tiene valor 1");
  pa2m_afirmar(arbol_bb->nodo_raiz->derecha == NULL, "El nodo RAIZ->HIJO_DER es NULL");

  pa2m_afirmar(arbol_bb->nodo_raiz->izquierda->izquierda == NULL, "El nodo RAIZ->HIJO_IZQ->HIJO_IZQ es NULL");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->izquierda->derecha->elemento == 2, "El nodo RAIZ->HIJO_IZQ->HIJO_DER tiene valor 2");

  pa2m_afirmar(arbol_bb->nodo_raiz->izquierda->derecha->izquierda == NULL, "El nodo RAIZ->HIJO_IZQ->HIJO_DER->HIJO_IZQ es NULL");
  pa2m_afirmar(arbol_bb->nodo_raiz->izquierda->derecha->derecha == NULL, "El nodo RAIZ->HIJO_IZQ->HIJO_DER->HIJO_DER es NULL");

  arbol_destruir(arbol_bb);
}

void dadoUnABBVacio_SiInsertoDatosEnOrdenBAC_LosDatosSeInsertanEnElOrdenCorrecto() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int dato1 = 1;
  int dato2 = 2;
  int dato3 = 3;
  arbol_insertar(arbol_bb, &dato2);
  arbol_insertar(arbol_bb, &dato1);
  arbol_insertar(arbol_bb, &dato3);
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->elemento == 2, "El nodo RAIZ tiene valor 2");

  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->izquierda->elemento == 1, "El nodo RAIZ->HIJO_IZQ tiene valor 1");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->elemento == 3, "El nodo RAIZ->HIJO_DER tiene valor 3");

  pa2m_afirmar(arbol_bb->nodo_raiz->izquierda->izquierda == NULL, "El nodo RAIZ->HIJO_IZQ->HIJO_IZQ es NULL");
  pa2m_afirmar(arbol_bb->nodo_raiz->izquierda->derecha == NULL, "El nodo RAIZ->HIJO_IZQ->HIJO_DER es NULL");

  pa2m_afirmar(arbol_bb->nodo_raiz->derecha->izquierda == NULL, "El nodo RAIZ->HIJO_DER->HIJO_IZQ es NULL");
  pa2m_afirmar(arbol_bb->nodo_raiz->derecha->derecha == NULL, "El nodo RAIZ->HIJO_DER->HIJO_DER es NULL");

  arbol_destruir(arbol_bb);
}

void dadoUnABBVacio_SiInsertoDatosEnOrdenBCA_LosDatosSeInsertanEnElOrdenCorrecto() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int dato1 = 1;
  int dato2 = 2;
  int dato3 = 3;
  arbol_insertar(arbol_bb, &dato2);
  arbol_insertar(arbol_bb, &dato3);
  arbol_insertar(arbol_bb, &dato1);
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->elemento == 2, "El nodo RAIZ tiene valor 2");

  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->izquierda->elemento == 1, "El nodo RAIZ->HIJO_IZQ tiene valor 1");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->elemento == 3, "El nodo RAIZ->HIJO_DER tiene valor 3");

  pa2m_afirmar(arbol_bb->nodo_raiz->izquierda->izquierda == NULL, "El nodo RAIZ->HIJO_IZQ->HIJO_IZQ es NULL");
  pa2m_afirmar(arbol_bb->nodo_raiz->izquierda->derecha == NULL, "El nodo RAIZ->HIJO_IZQ->HIJO_DER es NULL");

  pa2m_afirmar(arbol_bb->nodo_raiz->derecha->izquierda == NULL, "El nodo RAIZ->HIJO_DER->HIJO_IZQ es NULL");
  pa2m_afirmar(arbol_bb->nodo_raiz->derecha->derecha == NULL, "El nodo RAIZ->HIJO_DER->HIJO_DER es NULL");

  arbol_destruir(arbol_bb);
}

void dadoUnABBNull_SiSolicitoBuscarUnElemento_RetornaNullPorqueNoExisteElElemento(){
  abb_t* arbol_bb = NULL;
  int elemento_buscado = 4;
  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado), "Buscar en un ABB NULL devuelve como resultado NULL");
  arbol_destruir(arbol_bb);
}

void dadoUnABBVacio_SiSolicitoBuscarUnElemento_RetornaNullPorqueNoExisteElElemento(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int elemento_buscado = 4;
  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado), "Buscar en un ABB Vacio devuelve como resultado NULL");
  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoBuscarUnElementoQueNoExisteEnElArbol_RetornaNullPorqueNoExisteElElemento(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int elemento_buscado = 4;

  int dato1 = 1;
  int dato2 = 2;
  int dato3 = 3;
  int dato4 = 4;
  int dato5 = 5;
  int dato6 = 6;

  arbol_insertar(arbol_bb, &dato2);
  arbol_insertar(arbol_bb, &dato3);
  arbol_insertar(arbol_bb, &dato1);
  arbol_insertar(arbol_bb, &dato5);
  arbol_insertar(arbol_bb, &dato6);
  arbol_insertar(arbol_bb, &dato4);

  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado), "Buscar un elemento que no existe en el ABB retorna NULL");
  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoBuscarUnElementoQueExisteEnElArbol_DevuelveElValorDelElementoCorrectamente(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int elemento_buscado = 4;

  int dato1 = 1;
  int dato2 = 2;
  int dato3 = 3;
  int dato4 = 4;
  int dato5 = 5;
  int dato6 = 6;

  arbol_insertar(arbol_bb, &dato2);
  arbol_insertar(arbol_bb, &dato3);
  arbol_insertar(arbol_bb, &dato1);
  arbol_insertar(arbol_bb, &dato5);
  arbol_insertar(arbol_bb, &dato6);
  arbol_insertar(arbol_bb, &dato4);

  pa2m_afirmar(*(int*)arbol_buscar(arbol_bb, &elemento_buscado) == 4, "Se puede buscar el elemento 4 en el ABB y lo retorna correctamente");
  arbol_destruir(arbol_bb);
}


int main(){
  pa2m_nuevo_grupo("Pruebas Creacion ABB");
  dadoUnABBNull_SiCreoUnABBSinComparador_ElABBSigueSiendoNull();
  dadoUnABBNull_SiCreoUnABB_ResultaUnABBNoNullYVacio();
  pa2m_nuevo_grupo("Pruebas Insertar Datos en ABB");
  dadoUnABBNull_SiInsertoDatos_NoPermiteInsertarDatosEnUnABBNull();
  dadoUnABBVacio_SiInsertoDatos_ElABBYaNoEstaVacio();
  pa2m_nuevo_grupo("Pruebas Insertar Datos en ABB. Se inserta en el siguiente orden: 1, 2 y 3");
  dadoUnABBVacio_SiInsertoDatosEnOrdenABC_LosDatosSeInsertanEnElOrdenCorrecto();
  pa2m_nuevo_grupo("Pruebas Insertar Datos en ABB. Se inserta en el siguiente orden: 1, 3 y 2");
  dadoUnABBVacio_SiInsertoDatosEnOrdenACB_LosDatosSeInsertanEnElOrdenCorrecto();
  pa2m_nuevo_grupo("Pruebas Insertar Datos en ABB. Se inserta en el siguiente orden: 3, 2 y 1");
  dadoUnABBVacio_SiInsertoDatosEnOrdenCBA_LosDatosSeInsertanEnElOrdenCorrecto();
  pa2m_nuevo_grupo("Pruebas Insertar Datos en ABB. Se inserta en el siguiente orden: 3, 1 y 2");
  dadoUnABBVacio_SiInsertoDatosEnOrdenCAB_LosDatosSeInsertanEnElOrdenCorrecto();
  pa2m_nuevo_grupo("Pruebas Insertar Datos en ABB. Se inserta en el siguiente orden: 2, 1 y 3");
  dadoUnABBVacio_SiInsertoDatosEnOrdenBAC_LosDatosSeInsertanEnElOrdenCorrecto();
  pa2m_nuevo_grupo("Pruebas Insertar Datos en ABB. Se inserta en el siguiente orden: 2, 3 y 1");
  dadoUnABBVacio_SiInsertoDatosEnOrdenBCA_LosDatosSeInsertanEnElOrdenCorrecto();
  pa2m_nuevo_grupo("Pruebas busqueda de datos en ABB NULL");
  dadoUnABBNull_SiSolicitoBuscarUnElemento_RetornaNullPorqueNoExisteElElemento();
  pa2m_nuevo_grupo("Pruebas busqueda de datos en ABB Vacio");
  dadoUnABBVacio_SiSolicitoBuscarUnElemento_RetornaNullPorqueNoExisteElElemento();
  pa2m_nuevo_grupo("Pruebas busqueda de datos en ABB con elementos - El elemento no existe en el arbol");
  dadoUnABBConElementos_SiSolicitoBuscarUnElementoQueNoExisteEnElArbol_RetornaNullPorqueNoExisteElElemento();
  pa2m_nuevo_grupo("Pruebas busqueda de datos en ABB con elementos - El elemento existe en el arbol");
  dadoUnABBConElementos_SiSolicitoBuscarUnElementoQueExisteEnElArbol_DevuelveElValorDelElementoCorrectamente();
  return pa2m_mostrar_reporte();
}
