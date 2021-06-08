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
  pa2m_afirmar(arbol_bb == NULL, "El ABB sigue siendo NULL porque no se puede crear sin pasar una funcion comparadora");
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
  int elemento_buscado = 7;

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

  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado), "Buscar el elemento 7 en el ABB. Como el mismo no existe, retorna NULL");
  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoBuscarUnElementoQueExisteEnElArbol_DevuelveElValorDelElementoCorrectamente(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int elemento_buscado_1 = 1;
  int elemento_buscado_2 = 2;
  int elemento_buscado_3 = 3;
  int elemento_buscado_4 = 4;
  int elemento_buscado_5 = 5;
  int elemento_buscado_6 = 6;

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

  pa2m_afirmar(*(int*)arbol_buscar(arbol_bb, &elemento_buscado_1) == 1, "Se puede buscar el elemento 1 en el ABB y lo retorna correctamente");
  pa2m_afirmar(*(int*)arbol_buscar(arbol_bb, &elemento_buscado_2) == 2, "Se puede buscar el elemento 2 en el ABB y lo retorna correctamente");
  pa2m_afirmar(*(int*)arbol_buscar(arbol_bb, &elemento_buscado_3) == 3, "Se puede buscar el elemento 3 en el ABB y lo retorna correctamente");
  pa2m_afirmar(*(int*)arbol_buscar(arbol_bb, &elemento_buscado_4) == 4, "Se puede buscar el elemento 4 en el ABB y lo retorna correctamente");
  pa2m_afirmar(*(int*)arbol_buscar(arbol_bb, &elemento_buscado_5) == 5, "Se puede buscar el elemento 5 en el ABB y lo retorna correctamente");
  pa2m_afirmar(*(int*)arbol_buscar(arbol_bb, &elemento_buscado_6) == 6, "Se puede buscar el elemento 6 en el ABB y lo retorna correctamente");
  arbol_destruir(arbol_bb);
}

void dadoUnABBNull_SiSolicitoBorrarUnElemento_NoPermiteBorrarPorqueElABBEsNull() {
  abb_t* arbol = NULL;
  int elemento_a_buscar = 5;
  pa2m_afirmar(arbol_borrar(arbol, &elemento_a_buscar) == -1, "No permite eliminar en un ABB NULL");

  arbol_destruir(arbol);
}

void dadoUnABBVacio_SiSolicitoBorrarUnElemento_NoPermiteBorrarPorqueElABBEsVacio() {
  abb_t* arbol = arbol_crear(comparar_elementos_tipo_int, NULL);
  int elemento_a_buscar = 5;
  pa2m_afirmar(arbol_borrar(arbol, &elemento_a_buscar) == -1, "No permite eliminar en un ABB Vacio");

  arbol_destruir(arbol);
}

void dadoUnABBConElementos_SiSolicitoBorrarUnElementoQueNoExisteEnElArbol_NoPermiteBorrarPorqueNoExisteElElemento(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int elemento_buscado = 7;

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

  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado) == -1, "Se solicito borrar el elemento 7 en el ABB. Como el mismo no existe, retorna -1");
  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoBorrarElementosQueExisteEnElArbolYNoTienenHijos_PermiteBorrarCorrectamente(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int elemento_buscado_1 = 1;
  int elemento_buscado_2 = 2;
  int elemento_buscado_3 = 3;
  int elemento_buscado_4 = 4;
  int elemento_buscado_5 = 5;
  int elemento_buscado_6 = 6;

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

  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_6) == 0, "Se solicito borrar el elemento 6 en el ABB. Como el mismo existia, lo borra correctamente");
  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado_6), "Ya no se encuentra el elemento 6 en el ABB");
  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_6) == -1, "Se solicito borrar el elemento 6 en el ABB. Como el mismo ya no existia, retorna -1");

  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_4) == 0, "Se solicito borrar el elemento 4 en el ABB. Como el mismo existia, lo borra correctamente");
  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado_4), "Ya no se encuentra el elemento 4 en el ABB");
  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_4) == -1, "Se solicito borrar el elemento 4 en el ABB. Como el mismo ya no existia, retorna -1");

  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_5) == 0, "Se solicito borrar el elemento 5 en el ABB. Como el mismo existia, lo borra correctamente");
  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado_5), "Ya no se encuentra el elemento 5 en el ABB");
  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_5) == -1, "Se solicito borrar el elemento 5 en el ABB. Como el mismo ya no existia, retorna -1");

  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_3) == 0, "Se solicito borrar el elemento 3 en el ABB. Como el mismo existia, lo borra correctamente");
  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado_3), "Ya no se encuentra el elemento 3 en el ABB");
  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_3) == -1, "Se solicito borrar el elemento 3 en el ABB. Como el mismo ya no existia, retorna -1");

  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_1) == 0, "Se solicito borrar el elemento 1 en el ABB. Como el mismo existia, lo borra correctamente");
  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado_1), "Ya no se encuentra el elemento 1 en el ABB");
  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_1) == -1, "Se solicito borrar el elemento 1 en el ABB. Como el mismo ya no existia, retorna -1");

  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_2) == 0, "Se solicito borrar el elemento 2 en el ABB. Como el mismo existia, lo borra correctamente");
  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado_2), "Ya no se encuentra el elemento 2 en el ABB");
  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_2) == -1, "Se solicito borrar el elemento 2 en el ABB. Como el mismo ya no existia, retorna -1");
  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoBorrarElementosQueExisteEnElArbolYTienenUnHijo_PermiteBorrarCorrectamente() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int elemento_buscado_2 = 2;
  int elemento_buscado_3 = 3;
  int elemento_buscado_5 = 5;

  int dato2 = 2;
  int dato3 = 3;
  int dato4 = 4;
  int dato5 = 5;
  int dato6 = 6;
  int dato7 = 7;

  arbol_insertar(arbol_bb, &dato2);
  arbol_insertar(arbol_bb, &dato3);

  arbol_insertar(arbol_bb, &dato6);
  arbol_insertar(arbol_bb, &dato5);
  arbol_insertar(arbol_bb, &dato4);
  arbol_insertar(arbol_bb, &dato7);

  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_5) == 0, "Se solicito borrar el elemento 5 en el ABB. Como el mismo existia, lo borra correctamente");
  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado_5), "Ya no se encuentra el elemento 5 en el ABB");
  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_5) == -1, "Se solicito borrar el elemento 5 en el ABB. Como el mismo ya no existia, retorna -1");

  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_3) == 0, "Se solicito borrar el elemento 3 en el ABB. Como el mismo existia, lo borra correctamente");
  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado_3), "Ya no se encuentra el elemento 3 en el ABB");
  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_3) == -1, "Se solicito borrar el elemento 3 en el ABB. Como el mismo ya no existia, retorna -1");

  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_2) == 0, "Se solicito borrar el elemento 2 en el ABB. Como el mismo existia, lo borra correctamente");
  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado_2), "Ya no se encuentra el elemento 2 en el ABB");
  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_2) == -1, "Se solicito borrar el elemento 2 en el ABB. Como el mismo ya no existia, retorna -1");

  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoBorrarElementosQueExisteEnElArbolYTienenDosHijos_PermiteBorrarCorrectamente() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  // int elemento_buscado_2 = 2;
  // int elemento_buscado_5 = 5;
  int elemento_buscado_6 = 6;
  int elemento_buscado_7 = 7;

  int dato1 = 1;
  int dato2 = 2;
  int dato3 = 3;
  int dato4 = 4;
  int dato5 = 5;
  int dato6 = 6;
  int dato7 = 7;
  int dato8 = 8;

  arbol_insertar(arbol_bb, &dato2);
  arbol_insertar(arbol_bb, &dato3);
  arbol_insertar(arbol_bb, &dato1);
  arbol_insertar(arbol_bb, &dato7);
  arbol_insertar(arbol_bb, &dato5);
  arbol_insertar(arbol_bb, &dato6);
  arbol_insertar(arbol_bb, &dato4);
  arbol_insertar(arbol_bb, &dato8);

  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_7) == 0, "Se solicito borrar el elemento 7 en el ABB. Como el mismo existia, lo borra correctamente");
  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado_7), "Ya no se encuentra el elemento 7 en el ABB");
  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_7) == -1, "Se solicito borrar el elemento 7 en el ABB. Como el mismo ya no existia, retorna -1");

  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_6) == 0, "Se solicito borrar el elemento 6 en el ABB. Como el mismo existia, lo borra correctamente");
  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado_6), "Ya no se encuentra el elemento 6 en el ABB");
  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_6) == -1, "Se solicito borrar el elemento 6 en el ABB. Como el mismo ya no existia, retorna -1");

  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->elemento == 2, "RAIZ = 2");

  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->izquierda->elemento == 1, "RAIZ-IZQ = 1");
  pa2m_afirmar(!arbol_bb->nodo_raiz->izquierda->izquierda && !arbol_bb->nodo_raiz->izquierda->derecha, "RAIZ-IZQ no tiene hijos");

  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->elemento == 3, "RAIZ-DER = 3");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->izquierda, "RAIZ-DER no tiene hijo IZQ");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->derecha->elemento == 5, "RAIZ-DER-DER = 5");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->derecha->izquierda->elemento == 4, "RAIZ-DER-DER-IZQ = 4");
  printf("el valor del elemento en realidad es: %i\n", *(int*)arbol_bb->nodo_raiz->derecha->derecha->izquierda->elemento);
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->derecha->derecha->elemento == 8, "RAIZ-DER-DER-DER = 8");
  printf("el valor del elemento en realidad es: %i\n", *(int*)arbol_bb->nodo_raiz->derecha->derecha->derecha->elemento);

  // pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_5) == 0, "Se solicito borrar el elemento 5 en el ABB. Como el mismo existia, lo borra correctamente");
  // pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado_5), "Ya no se encuentra el elemento 5 en el ABB");
  // pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_5) == -1, "Se solicito borrar el elemento 5 en el ABB. Como el mismo ya no existia, retorna -1");

  // pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_2) == 0, "Se solicito borrar el elemento 2 en el ABB. Como el mismo existia, lo borra correctamente");
  // pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado_2), "Ya no se encuentra el elemento 2 en el ABB");
  // pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_2) == -1, "Se solicito borrar el elemento 2 en el ABB. Como el mismo ya no existia, retorna -1");

  arbol_destruir(arbol_bb);
}

int main() {
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
  pa2m_nuevo_grupo("Pruebas busqueda de datos en ABB con elementos [1, 2, 3, 4, 5, 6] - El elemento no existe en el ABB");
  dadoUnABBConElementos_SiSolicitoBuscarUnElementoQueNoExisteEnElArbol_RetornaNullPorqueNoExisteElElemento();
  pa2m_nuevo_grupo("Pruebas busqueda de datos en ABB con elementos [1, 2, 3, 4, 5, 6] - El elemento existe en el ABB");
  dadoUnABBConElementos_SiSolicitoBuscarUnElementoQueExisteEnElArbol_DevuelveElValorDelElementoCorrectamente();
  pa2m_nuevo_grupo("Pruebas Eliminar Datos en ABB NULL");
  dadoUnABBNull_SiSolicitoBorrarUnElemento_NoPermiteBorrarPorqueElABBEsNull();
  pa2m_nuevo_grupo("Pruebas Eliminar Datos en ABB Vacio");
  dadoUnABBVacio_SiSolicitoBorrarUnElemento_NoPermiteBorrarPorqueElABBEsVacio();
  pa2m_nuevo_grupo("Pruebas Eliminar datos en ABB con elementos [1, 2, 3, 4, 5, 6] - El elemento no existe en el ABB");
  dadoUnABBConElementos_SiSolicitoBorrarUnElementoQueNoExisteEnElArbol_NoPermiteBorrarPorqueNoExisteElElemento();
  pa2m_nuevo_grupo("Pruebas Eliminar datos en ABB con elementos [1, 2, 3, 4, 5, 6] - Los elementos existen en el ABB y no tienen hijos");
  dadoUnABBConElementos_SiSolicitoBorrarElementosQueExisteEnElArbolYNoTienenHijos_PermiteBorrarCorrectamente();
  pa2m_nuevo_grupo("Pruebas Eliminar datos en ABB con elementos [1, 2, 3, 4, 5, 6, 7] - Los elementos existen en el ABB y tienen un hijo");
  dadoUnABBConElementos_SiSolicitoBorrarElementosQueExisteEnElArbolYTienenUnHijo_PermiteBorrarCorrectamente();
  pa2m_nuevo_grupo("Pruebas Eliminar datos en ABB con elementos [1, 2, 3, 4, 5, 6, 7, 8] - Los elementos existen en el ABB y tienen dos hijos");
  dadoUnABBConElementos_SiSolicitoBorrarElementosQueExisteEnElArbolYTienenDosHijos_PermiteBorrarCorrectamente();
  return pa2m_mostrar_reporte();
}
