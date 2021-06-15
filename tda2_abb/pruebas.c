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
  int elemento_buscado_2 = 2;
  int elemento_buscado_5 = 5;
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

  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->elemento == 2, "El nodo RAIZ tiene valor 2");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->izquierda->elemento == 1, "El nodo RAIZ->HIJO_IZQ tiene valor 1");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->elemento == 3, "El nodo RAIZ->HIJO_DER tiene valor 3");
  pa2m_afirmar(!arbol_bb->nodo_raiz->izquierda->izquierda, "El nodo RAIZ->HIJO_IZQ->HIJO_IZQ es NULL");
  pa2m_afirmar(!arbol_bb->nodo_raiz->izquierda->derecha, "El nodo RAIZ->HIJO_IZQ->HIJO_DER es NULL");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->izquierda, "El nodo RAIZ->HIJO_DER->HIJO_IZQ es NULL");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->derecha->elemento == 6, "El nodo RAIZ->HIJO_DER->HIJO_DER tiene valor 6");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->derecha->izquierda->elemento == 5, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_IZQ tiene valor 5");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->derecha->derecha->elemento == 8, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_DER tiene valor 8");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->derecha->izquierda->izquierda->elemento == 4, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_IZQ->HIJO_IZQ tiene valor 4");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->derecha->izquierda->derecha, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_IZQ->HIJO_DER es NULL");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->derecha->izquierda->izquierda->izquierda, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_IZQ->HIJO_IZQ->HIJO_IZQ es NULL");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->derecha->izquierda->izquierda->derecha, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_IZQ->HIJO_IZQ->HIJO_DER es NULL");

  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_6) == 0, "Se solicito borrar el elemento 6 en el ABB. Como el mismo existia, lo borra correctamente");
  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado_6), "Ya no se encuentra el elemento 6 en el ABB");
  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_6) == -1, "Se solicito borrar el elemento 6 en el ABB. Como el mismo ya no existia, retorna -1");

  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->elemento == 2, "El nodo RAIZ tiene valor 2");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->izquierda->elemento == 1, "El nodo RAIZ->HIJO_IZQ tiene valor 1");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->elemento == 3, "El nodo RAIZ->HIJO_DER tiene valor 3");
  pa2m_afirmar(!arbol_bb->nodo_raiz->izquierda->izquierda, "El nodo RAIZ->HIJO_IZQ->HIJO_IZQ es NULL");
  pa2m_afirmar(!arbol_bb->nodo_raiz->izquierda->derecha, "El nodo RAIZ->HIJO_IZQ->HIJO_DER es NULL");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->izquierda, "El nodo RAIZ->HIJO_DER->HIJO_IZQ es NULL");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->derecha->elemento == 5, "El nodo RAIZ->HIJO_DER->HIJO_DER tiene valor 5");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->derecha->izquierda->elemento == 4, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_IZQ tiene valor 4");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->derecha->derecha->elemento == 8, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_DER tiene valor 8");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->derecha->derecha->izquierda, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_IZQ->HIJO_IZQ es NULL");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->derecha->derecha->derecha, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_IZQ->HIJO_DER es NULL");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->derecha->derecha->izquierda, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_DER->HIJO_IZQ es NULL");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->derecha->derecha->derecha, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_DER->HIJO_DER es NULL");

  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_5) == 0, "Se solicito borrar el elemento 5 en el ABB. Como el mismo existia, lo borra correctamente");
  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado_5), "Ya no se encuentra el elemento 5 en el ABB");
  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_5) == -1, "Se solicito borrar el elemento 5 en el ABB. Como el mismo ya no existia, retorna -1");

  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->elemento == 2, "El nodo RAIZ tiene valor 2");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->izquierda->elemento == 1, "El nodo RAIZ->HIJO_IZQ tiene valor 1");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->elemento == 3, "El nodo RAIZ->HIJO_DER tiene valor 3");
  pa2m_afirmar(!arbol_bb->nodo_raiz->izquierda->izquierda, "El nodo RAIZ->HIJO_IZQ->HIJO_IZQ es NULL");
  pa2m_afirmar(!arbol_bb->nodo_raiz->izquierda->derecha, "El nodo RAIZ->HIJO_IZQ->HIJO_DER es NULL");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->izquierda, "El nodo RAIZ->HIJO_DER->HIJO_IZQ es NULL");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->derecha->elemento == 4, "El nodo RAIZ->HIJO_DER->HIJO_DER tiene valor 4");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->derecha->izquierda, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_IZQ tiene es NULL");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->derecha->derecha->elemento == 8, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_DER tiene valor 8");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->derecha->derecha->izquierda, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_DER->HIJO_IZQ es NULL");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->derecha->derecha->derecha, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_DER->HIJO_DER es NULL");


  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_2) == 0, "Se solicito borrar el elemento 2 en el ABB. Como el mismo existia, lo borra correctamente");
  pa2m_afirmar(!arbol_buscar(arbol_bb, &elemento_buscado_2), "Ya no se encuentra el elemento 2 en el ABB");
  pa2m_afirmar(arbol_borrar(arbol_bb, &elemento_buscado_2) == -1, "Se solicito borrar el elemento 2 en el ABB. Como el mismo ya no existia, retorna -1");

  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->elemento == 1, "El nodo RAIZ tiene valor 1");
  pa2m_afirmar(!arbol_bb->nodo_raiz->izquierda, "El nodo RAIZ->HIJO_IZQ es NULL");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->elemento == 3, "El nodo RAIZ->HIJO_DER tiene valor 3");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->izquierda, "El nodo RAIZ->HIJO_DER->HIJO_IZQ es NULL");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->derecha->elemento == 4, "El nodo RAIZ->HIJO_DER->HIJO_DER tiene valor 4");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->derecha->izquierda, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_IZQ tiene es NULL");
  pa2m_afirmar(*(int*)arbol_bb->nodo_raiz->derecha->derecha->derecha->elemento == 8, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_DER tiene valor 8");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->derecha->derecha->izquierda, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_DER->HIJO_IZQ es NULL");
  pa2m_afirmar(!arbol_bb->nodo_raiz->derecha->derecha->derecha->derecha, "El nodo RAIZ->HIJO_DER->HIJO_DER->HIJO_DER->HIJO_DER es NULL");

  arbol_destruir(arbol_bb);
}

void dadoUnABBNull_SiSolicitoVerRaiz_RetornaNull() {
  abb_t* arbol_bb = NULL;
  pa2m_afirmar(!arbol_raiz(arbol_bb), "Ver raiz en un ABB NULL retorna NULL");

  arbol_destruir(arbol_bb);
}

void dadoUnABBVacio_SiSolicitoVerRaiz_RetornaNull() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  pa2m_afirmar(!arbol_raiz(arbol_bb), "Ver raiz en un ABB Vacio retorna NULL");

  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoVerRaiz_RetornaElElementoDeLaRaiz() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);

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

  pa2m_afirmar(*(int*)arbol_raiz(arbol_bb) == 2, "Ver raiz en un ABB Con Elementos retorna correctamente la Raiz");

  arbol_destruir(arbol_bb);
}

void dadoUnABBNull_SiSolicitoRecorrerInOrden_RetornaCorrectamenteLaCantidadDeElementosRecorridos(){
  abb_t* arbol_bb = NULL;

  int* array[8];
  size_t cantidad = arbol_recorrido_inorden(arbol_bb,(void**)array, 8);
  pa2m_afirmar(cantidad == 0, "El ABB NULL se recorre 0 veces");

  arbol_destruir(arbol_bb);
}

void dadoUnABBVacio_SiSolicitoRecorrerInOrden_RetornaCorrectamenteLaCantidadDeElementosRecorridos(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);;

  int* array[8];
  size_t cantidad = arbol_recorrido_inorden(arbol_bb,(void**)array, 8);
  pa2m_afirmar(cantidad == 0, "El ABB Vacio se recorre 0 veces");

  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoRecorrerInOrdenConUnArrayNULL_RetornaCorrectamenteLaCantidadDeElementosRecorridos(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);

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

  int* array = NULL;
  size_t cantidad = arbol_recorrido_inorden(arbol_bb,(void**)array, 8);
  pa2m_afirmar(cantidad == 0, "El ABB se recorre 0 veces porque el array es NULL");

  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoRecorrerInOrdenConUnArrayPasandoTamanioCero_RetornaCorrectamenteLaCantidadDeElementosRecorridos() {
    abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);

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

  int* array[8];
  size_t cantidad = arbol_recorrido_inorden(arbol_bb,(void**)array, 0);
  pa2m_afirmar(cantidad == 0, "El ABB se recorre 0 veces porque se pasa un tamanio 0");

  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoRecorrerInOrdenConArrayDelMismoTamanioQueElABB_GuardaCorrectamenteLosElementos() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);

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

  int* array[8];
  size_t cantidad = arbol_recorrido_inorden(arbol_bb,(void**)array, 8);
  pa2m_afirmar(cantidad == 8, "Se recorre el arbol completo");
  for(size_t i = 0; i < cantidad; i++) {
    pa2m_afirmar(*array[i] == i + 1, "El elemento del array es correcto");
  }

  arbol_destruir(arbol_bb);

}


void dadoUnABBConElementos_SiSolicitoRecorrerInOrdenConArrayDeMayorTamanioQueElABB_GuardaCorrectamenteLosElementos() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);

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

  int* array[20];
  size_t cantidad = arbol_recorrido_inorden(arbol_bb,(void**)array, 20);
  pa2m_afirmar(cantidad == 8, "Se recorren todos los elementos del arbol");
  for(size_t i = 0; i < cantidad; i++) {
    pa2m_afirmar(*array[i] == i + 1, "El elemento del array es correcto");
  }

  arbol_destruir(arbol_bb);
}


void dadoUnABBConElementos_SiSolicitoRecorrerInOrdenConArrayDeMenorTamanioQueElABB_GuardaCorrectamenteLosElementos() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);

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

  int* array[3];
  size_t cantidad = arbol_recorrido_inorden(arbol_bb,(void**)array, 3);
  pa2m_afirmar(cantidad == 3, "Se recorren tres elementos del arbol");
  for(size_t i = 0; i < cantidad; i++) {
    pa2m_afirmar(*array[i] == i + 1, "El elemento del array es correcto");
  }

  arbol_destruir(arbol_bb);
}


void dadoUnABBNull_SiSolicitoRecorrerPreOrden_RetornaCorrectamenteLaCantidadDeElementosRecorridos(){
  abb_t* arbol_bb = NULL;

  int* array[8];
  size_t cantidad = arbol_recorrido_preorden(arbol_bb,(void**)array, 8);
  pa2m_afirmar(cantidad == 0, "El ABB NULL se recorre 0 veces");

  arbol_destruir(arbol_bb);
}

void dadoUnABBVacio_SiSolicitoRecorrerPreOrden_RetornaCorrectamenteLaCantidadDeElementosRecorridos(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);;

  int* array[8];
  size_t cantidad = arbol_recorrido_preorden(arbol_bb,(void**)array, 8);
  pa2m_afirmar(cantidad == 0, "El ABB Vacio se recorre 0 veces");

  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoRecorrerPreOrdenConUnArrayNULL_RetornaCorrectamenteLaCantidadDeElementosRecorridos(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);

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

  int* array = NULL;
  size_t cantidad = arbol_recorrido_preorden(arbol_bb,(void**)array, 8);
  pa2m_afirmar(cantidad == 0, "El ABB se recorre 0 veces porque el array es NULL");

  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoRecorrerPreOrdenConUnArrayPasandoTamanioCero_RetornaCorrectamenteLaCantidadDeElementosRecorridos() {
    abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);

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

  int* array[8];
  size_t cantidad = arbol_recorrido_preorden(arbol_bb,(void**)array, 0);
  pa2m_afirmar(cantidad == 0, "El ABB se recorre 0 veces porque se pasa un tamanio 0");

  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoRecorrerPreOrdenConArrayDelMismoTamanioQueElABB_GuardaCorrectamenteLosElementos() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);

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

  int* array[8];
  int array_esperado[] = {2,1,3,7,5,4,6,8};

  size_t cantidad = arbol_recorrido_preorden(arbol_bb,(void**)array, 8);
  pa2m_afirmar(cantidad == 8, "Se recorre el arbol completo");
  for(size_t i = 0; i < cantidad; i++) {
    pa2m_afirmar(*array[i] == array_esperado[i], "El elemento del array es correcto");
  }

  arbol_destruir(arbol_bb);

}

void dadoUnABBConElementos_SiSolicitoRecorrerPreOrdenConArrayDeMayorTamanioQueElABB_GuardaCorrectamenteLosElementos() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);

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

  int* array[20];
  int array_esperado[] = {2,1,3,7,5,4,6,8};
  size_t cantidad = arbol_recorrido_preorden(arbol_bb,(void**)array, 20);
  pa2m_afirmar(cantidad == 8, "Se recorren todos los elementos del arbol");
  for(size_t i = 0; i < cantidad; i++) {
    pa2m_afirmar(*array[i] == array_esperado[i], "El elemento del array es correcto");
  }

  arbol_destruir(arbol_bb);
}


void dadoUnABBConElementos_SiSolicitoRecorrerPreOrdenConArrayDeMenorTamanioQueElABB_GuardaCorrectamenteLosElementos() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);

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

  int* array[3];
  int array_esperado[] = {2,1,3};
  size_t cantidad = arbol_recorrido_preorden(arbol_bb,(void**)array, 3);
  pa2m_afirmar(cantidad == 3, "Se recorren tres elementos del arbol");
  for(size_t i = 0; i < cantidad; i++) {
    pa2m_afirmar(*array[i] == array_esperado[i] , "El elemento del array es correcto");
  }

  arbol_destruir(arbol_bb);
}

void dadoUnABBNull_SiSolicitoRecorrerPostOrden_RetornaCorrectamenteLaCantidadDeElementosRecorridos(){
  abb_t* arbol_bb = NULL;

  int* array[8];
  size_t cantidad = arbol_recorrido_postorden(arbol_bb,(void**)array, 8);
  pa2m_afirmar(cantidad == 0, "El ABB NULL se recorre 0 veces");

  arbol_destruir(arbol_bb);
}

void dadoUnABBVacio_SiSolicitoRecorrerPostOrden_RetornaCorrectamenteLaCantidadDeElementosRecorridos(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);;

  int* array[8];
  size_t cantidad = arbol_recorrido_postorden(arbol_bb,(void**)array, 8);
  pa2m_afirmar(cantidad == 0, "El ABB Vacio se recorre 0 veces");

  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoRecorrerPostOrdenConUnArrayNULL_RetornaCorrectamenteLaCantidadDeElementosRecorridos(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);

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

  int* array = NULL;
  size_t cantidad = arbol_recorrido_postorden(arbol_bb,(void**)array, 8);
  pa2m_afirmar(cantidad == 0, "El ABB se recorre 0 veces porque el array es NULL");

  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoRecorrerPostOrdenConUnArrayPasandoTamanioCero_RetornaCorrectamenteLaCantidadDeElementosRecorridos() {
    abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);

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

  int* array[8];
  size_t cantidad = arbol_recorrido_postorden(arbol_bb,(void**)array, 0);
  pa2m_afirmar(cantidad == 0, "El ABB se recorre 0 veces porque se pasa un tamanio 0");

  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoRecorrerPostOrdenConArrayDelMismoTamanioQueElABB_GuardaCorrectamenteLosElementos() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);

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

  int* array[8];
  int array_esperado[] = {1,4,6,5,8,7,3,2};

  size_t cantidad = arbol_recorrido_postorden(arbol_bb,(void**)array, 8);
  pa2m_afirmar(cantidad == 8, "Se recorre el arbol completo");
  for(size_t i = 0; i < cantidad; i++) {
    pa2m_afirmar(*array[i] == array_esperado[i], "El elemento del array es correcto");
  }

  arbol_destruir(arbol_bb);

}

void dadoUnABBConElementos_SiSolicitoRecorrerPostOrdenConArrayDeMayorTamanioQueElABB_GuardaCorrectamenteLosElementos() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);

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

  int* array[20];
  int array_esperado[] = {1,4,6,5,8,7,3,2};
  size_t cantidad = arbol_recorrido_postorden(arbol_bb,(void**)array, 20);
  pa2m_afirmar(cantidad == 8, "Se recorren todos los elementos del arbol");
  for(size_t i = 0; i < cantidad; i++) {
    pa2m_afirmar(*array[i] == array_esperado[i], "El elemento del array es correcto");
  }

  arbol_destruir(arbol_bb);
}


void dadoUnABBConElementos_SiSolicitoRecorrerPostOrdenConArrayDeMenorTamanioQueElABB_GuardaCorrectamenteLosElementos() {
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);

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

  int* array[3];
  int array_esperado[] = {1,4,6};
  size_t cantidad = arbol_recorrido_postorden(arbol_bb,(void**)array, 3);
  pa2m_afirmar(cantidad == 3, "Se recorren tres elementos del arbol");
  for(size_t i = 0; i < cantidad; i++) {
    pa2m_afirmar(*array[i] == array_esperado[i] , "El elemento del array es correcto");
  }

  arbol_destruir(arbol_bb);
}

bool visitar_todo(void* elemento, void* extra) {
    if(elemento)
        (*(int*)extra)++;
    return false;
}

bool visitar_hasta_cinco(void* elemento, void* extra) {
    (*(int*)extra)++;
    if(*(int*)extra >= 5) {
      return true;
    }
    return false;
}

bool visitar_con_corte(void* elemento, void* extra) {
  (*(int*)extra)++;
  if(*(int*)elemento == 5)
    return true;
  return false;
}

void dadoUnABBNull_SiSolicitoIterarInternamenteTodosLosElementosEnTodosLosOrdenesPosibles_RetornaElResultadoCorrecto(){
  abb_t* arbol_bb = NULL;
  int contador = 0;
  pa2m_afirmar(abb_con_cada_elemento(arbol_bb, ABB_RECORRER_INORDEN, visitar_todo, &contador) == 0, "Recorrer in orden un ABB NULL retorna 0");
  pa2m_afirmar(abb_con_cada_elemento(arbol_bb, ABB_RECORRER_PREORDEN, visitar_todo, &contador) == 0, "Recorrer pre orden un ABB NULL retorna 0");
  pa2m_afirmar(abb_con_cada_elemento(arbol_bb, ABB_RECORRER_POSTORDEN, visitar_todo, &contador) == 0, "Recorrer post orden un ABB NULL retorna 0");

  arbol_destruir(arbol_bb);
}

void dadoUnABBVacio_SiSolicitoIterarInternamenteTodosLosElementosEnTodosLosOrdenesPosibles_RetornaElResultadoCorrecto(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int contador = 0;
  pa2m_afirmar(abb_con_cada_elemento(arbol_bb, ABB_RECORRER_INORDEN, visitar_todo, &contador) == 0, "Recorrer in orden un ABB Vacio retorna 0");
  pa2m_afirmar(abb_con_cada_elemento(arbol_bb, ABB_RECORRER_PREORDEN, visitar_todo, &contador) == 0, "Recorrer pre orden un ABB Vacio retorna 0");
  pa2m_afirmar(abb_con_cada_elemento(arbol_bb, ABB_RECORRER_POSTORDEN, visitar_todo, &contador) == 0, "Recorrer post orden un ABB Vacio retorna 0");

  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoIterarInternamenteTodosLosElementosEnTodosLosOrdenesPosiblesSinUnaFuncionVisitar_RetornaElResultadoCorrecto(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int contador = 0;

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

  pa2m_afirmar(abb_con_cada_elemento(arbol_bb, ABB_RECORRER_INORDEN, NULL, &contador) == 0, "Recorrer in orden un ABB con elementos pero sin funcion visitar retorna 0");
  pa2m_afirmar(abb_con_cada_elemento(arbol_bb, ABB_RECORRER_PREORDEN, NULL, &contador) == 0, "Recorrer pre orden un ABB con elementos pero sin funcion visitar retorna 0");
  pa2m_afirmar(abb_con_cada_elemento(arbol_bb, ABB_RECORRER_POSTORDEN, NULL, &contador) == 0, "Recorrer post orden un ABB con elementos pero sin funcion visitar retorna 0");

  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoIterarInternamenteTodosLosElementosEnTodosLosOrdenesPosiblesConUnaFuncionVisitar_RetornaElResultadoCorrecto(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int contador_1 = 0;
  int contador_2 = 0;
  int contador_3 = 0;

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

  size_t cuenta_1 = abb_con_cada_elemento(arbol_bb, ABB_RECORRER_INORDEN, visitar_todo, &contador_1);
  pa2m_afirmar(cuenta_1 == 8, "Recorrer in orden un ABB con elementos y con funcion visitar retorna 8");
  pa2m_afirmar(contador_1 == 8, "Recorrer in orden un ABB con elementos y con funcion visitar actualiza correctamente el valor extra a 8");

  size_t cuenta_2 = abb_con_cada_elemento(arbol_bb, ABB_RECORRER_PREORDEN, visitar_todo, &contador_2);
  pa2m_afirmar(cuenta_2 == 8, "Recorrer pre orden un ABB con elementos y con funcion visitar retorna 8");
  pa2m_afirmar(contador_2 == 8, "Recorrer pre orden un ABB con elementos y con funcion visitar actualiza correctamente el valor extra a 8");

  size_t cuenta_3 = abb_con_cada_elemento(arbol_bb, ABB_RECORRER_POSTORDEN, visitar_todo, &contador_3);
  pa2m_afirmar(cuenta_3 == 8, "Recorrer post orden un ABB con elementos y con funcion visitar retorna 8");
  pa2m_afirmar(contador_3 == 8, "Recorrer post orden un ABB con elementos y con funcion visitar actualiza correctamente el valor extra a 8");

  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoIterarInternamenteCincoElementosEnTodosLosOrdenesPosiblesConUnaFuncionVisitar_RetornaElResultadoCorrecto(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int contador_1 = 0;
  int contador_2 = 0;
  int contador_3 = 0;

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

  size_t cuenta_2 = abb_con_cada_elemento(arbol_bb, ABB_RECORRER_PREORDEN, visitar_hasta_cinco, &contador_2);
  pa2m_afirmar(cuenta_2 == 5, "Recorrer pre orden un ABB con elementos y con funcion visitar hasta 5 retorna 5");
  pa2m_afirmar(contador_2 == 5, "Recorrer pre orden un ABB con elementos y con funcion visitar actualiza correctamente el valor extra a 5");

  size_t cuenta_1 = abb_con_cada_elemento(arbol_bb, ABB_RECORRER_INORDEN, visitar_hasta_cinco, &contador_1);
  pa2m_afirmar(cuenta_1 == 5, "Recorrer in orden un ABB con elementos y con funcion visitar hasta 5 retorna 5");
  pa2m_afirmar(contador_1 == 5, "Recorrer in orden un ABB con elementos y con funcion visitar actualiza correctamente el valor extra a 5");


  size_t cuenta_3 = abb_con_cada_elemento(arbol_bb, ABB_RECORRER_POSTORDEN, visitar_hasta_cinco, &contador_3);
  pa2m_afirmar(cuenta_3 == 5, "Recorrer post orden un ABB con elementos y con funcion visitar hasta 5 retorna 5");
  pa2m_afirmar(contador_3 == 5, "Recorrer post orden un ABB con elementos y con funcion visitar actualiza correctamente el valor extra a 5");

  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoIterarInternamenteHastaEncontrarUnElementoQueExisteEnElABBEnTodosLosOrdenesPosiblesConUnaFuncionVisitar_RetornaElResultadoCorrecto(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int contador_1 = 0;
  int contador_2 = 0;
  int contador_3 = 0;

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

  size_t cuenta_2 = abb_con_cada_elemento(arbol_bb, ABB_RECORRER_PREORDEN, visitar_con_corte, &contador_2);
  pa2m_afirmar(cuenta_2 == 5, "Recorrer pre orden un ABB con elementos y con funcion visitar que corta cuando encuentra un elemento, retorna 5 porque encuentra el elemento");
  pa2m_afirmar(contador_2 == 5, "Recorrer pre orden un ABB con elementos y con funcion visitar actualiza correctamente el valor extra a 5");

  size_t cuenta_1 = abb_con_cada_elemento(arbol_bb, ABB_RECORRER_INORDEN, visitar_con_corte, &contador_1);
  pa2m_afirmar(cuenta_1 == 5, "Recorrer in orden un ABB con elementos y con funcion visitar que corta cuando encuentra un elemento, retorna 5 porque encuentra el elemento");
  pa2m_afirmar(contador_1 == 5, "Recorrer in orden un ABB con elementos y con funcion visitar actualiza correctamente el valor extra a 5");

  size_t cuenta_3 = abb_con_cada_elemento(arbol_bb, ABB_RECORRER_POSTORDEN, visitar_con_corte, &contador_3);
  pa2m_afirmar(cuenta_3 == 4, "Recorrer post orden un ABB con elementos y con funcion visitar que corta cuando encuentra un elemento, retorna 4 porque encuentra el elemento");
  pa2m_afirmar(contador_3 == 4, "Recorrer post orden un ABB con elementos y con funcion visitar actualiza correctamente el valor extra a 4");

  arbol_destruir(arbol_bb);
}

void dadoUnABBConElementos_SiSolicitoIterarInternamenteHastaEncontrarUnElementoQueNoExisteEnElABBEnTodosLosOrdenesPosiblesConUnaFuncionVisitar_RetornaElResultadoCorrecto(){
  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_int, NULL);
  int contador_1 = 0;
  int contador_2 = 0;
  int contador_3 = 0;

  int dato1 = 1;
  int dato2 = 2;
  int dato3 = 3;
  int dato4 = 4;
  int dato5 = 6;
  int dato6 = 7;
  int dato7 = 8;
  int dato8 = 9;

  arbol_insertar(arbol_bb, &dato2);
  arbol_insertar(arbol_bb, &dato3);
  arbol_insertar(arbol_bb, &dato1);
  arbol_insertar(arbol_bb, &dato7);
  arbol_insertar(arbol_bb, &dato5);
  arbol_insertar(arbol_bb, &dato6);
  arbol_insertar(arbol_bb, &dato4);
  arbol_insertar(arbol_bb, &dato8);

  size_t cuenta_2 = abb_con_cada_elemento(arbol_bb, ABB_RECORRER_PREORDEN, visitar_con_corte, &contador_2);
  pa2m_afirmar(cuenta_2 == 8, "Recorrer pre orden un ABB con elementos y con funcion visitar que corta cuando encuentra un elemento, retorna 8 porque no existe el elemento.");
  pa2m_afirmar(contador_2 == 8, "Recorrer pre orden un ABB con elementos y con funcion visitar actualiza correctamente el valor extra a 8");

  size_t cuenta_1 = abb_con_cada_elemento(arbol_bb, ABB_RECORRER_INORDEN, visitar_con_corte, &contador_1);
  pa2m_afirmar(cuenta_1 == 8, "Recorrer in orden un ABB con elementos y con funcion visitar que corta cuando encuentra un elemento, retorna 8 porque no existe el elemento.");
  pa2m_afirmar(contador_1 == 8, "Recorrer in orden un ABB con elementos y con funcion visitar actualiza correctamente el valor extra a 8");

  size_t cuenta_3 = abb_con_cada_elemento(arbol_bb, ABB_RECORRER_POSTORDEN, visitar_con_corte, &contador_3);
  pa2m_afirmar(cuenta_3 == 8, "Recorrer post orden un ABB con elementos y con funcion visitar que corta cuando encuentra un elemento, retorna 8 porque no existe el elemento.");
  pa2m_afirmar(contador_3 == 8, "Recorrer post orden un ABB con elementos y con funcion visitar actualiza correctamente el valor extra a 8");

  arbol_destruir(arbol_bb);
}


int comparar_elementos_tipo_string(void* elemento1, void* elemento2) {
  return strcmp(*(char**)elemento1, *(char**)elemento2);
}

void dadoUnABBConElementosDeTipoStringCreadosEnElHeap_SiSolicitoOperarSobreLosElementosYLuegoDestruirElArbolSinFuncionDestruccion_PermiteOperarSobreLosElementosYLuegoDestruirElArbolCorrectamente() {
  char** dato1 = calloc(1, sizeof(char) * 10);
  char** dato2 = calloc(1, sizeof(char) * 10);
  char** dato3 = calloc(1, sizeof(char) * 10);
  char** dato4 = calloc(1, sizeof(char) * 10);
  char** dato5 = calloc(1, sizeof(char) * 10);
  char** dato6 = calloc(1, sizeof(char) * 10);
  char** dato7 = calloc(1, sizeof(char) * 10);
  char** dato8 = calloc(1, sizeof(char) * 10);

  *dato1 = "aleph";
  *dato2 = "bifurcacion";
  *dato3 = "circulo";
  *dato4 = "daneri";
  *dato5 = "ermita";
  *dato6 = "fisura";
  *dato7 = "gondola";
  *dato8 = "hipotenusa";

  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_string, NULL);

  arbol_insertar(arbol_bb, dato2);
  arbol_insertar(arbol_bb, dato3);
  arbol_insertar(arbol_bb, dato1);
  arbol_insertar(arbol_bb, dato7);
  arbol_insertar(arbol_bb, dato5);
  arbol_insertar(arbol_bb, dato6);
  arbol_insertar(arbol_bb, dato4);
  arbol_insertar(arbol_bb, dato8);

  char* esperado_inorden[]   = {"aleph", "bifurcacion", "circulo", "daneri", "ermita", "fisura", "gondola", "hipotenusa"};
  char* esperado_preorden[]  = {"bifurcacion", "aleph", "circulo", "gondola", "ermita", "daneri", "fisura", "hipotenusa"};
  char* esperado_postorden[] = {"aleph", "daneri", "fisura", "ermita", "hipotenusa", "gondola", "circulo", "bifurcacion"};

  char** array_inorden[8];
  char** array_preorden[8];
  char** array_postorden[8];


  size_t cantidad_1 = arbol_recorrido_inorden(arbol_bb,(void**)array_inorden, 8);
  size_t cantidad_2 = arbol_recorrido_preorden(arbol_bb,(void**)array_preorden, 8);
  size_t cantidad_3 = arbol_recorrido_postorden(arbol_bb,(void**)array_postorden, 8);

  pa2m_afirmar(cantidad_1 == 8, "Se recorre el arbol completo inorden");
  pa2m_afirmar(cantidad_2 == 8, "Se recorre el arbol completo preorden");
  pa2m_afirmar(cantidad_3 == 8, "Se recorre el arbol completo postorden");

  for(size_t i = 0; i < cantidad_1; i++) {
    pa2m_afirmar(strcmp(*(char**)array_inorden[i],esperado_inorden[i]) == 0, "El elemento del array inorden es correcto");
    pa2m_afirmar(strcmp(*(char**)array_preorden[i], esperado_preorden[i]) == 0, "El elemento del array preorden es correcto");
    pa2m_afirmar(strcmp(*(char**)array_postorden[i], esperado_postorden[i]) == 0, "El elemento del array postorden es correcto");
  }

  free(dato1);
  free(dato2);
  free(dato3);
  free(dato4);
  free(dato5);
  free(dato6);
  free(dato7);
  free(dato8);

  arbol_destruir(arbol_bb);

}

void dadoUnABBConElementosDeTipoStringCreadosEnElHeap_SiSolicitoOperarSobreLosElementosYLuegoDestruirElArbolConFuncionDestruccion_PermiteOperarSobreLosElementosYLuegoDestruirElArbolCorrectamente() {
  char** dato1 = calloc(1, sizeof(char) * 10);
  char** dato2 = calloc(1, sizeof(char) * 10);
  char** dato3 = calloc(1, sizeof(char) * 10);
  char** dato4 = calloc(1, sizeof(char) * 10);
  char** dato5 = calloc(1, sizeof(char) * 10);
  char** dato6 = calloc(1, sizeof(char) * 10);
  char** dato7 = calloc(1, sizeof(char) * 10);
  char** dato8 = calloc(1, sizeof(char) * 10);

  *dato1 = "aleph";
  *dato2 = "bifurcacion";
  *dato3 = "circulo";
  *dato4 = "daneri";
  *dato5 = "ermita";
  *dato6 = "fisura";
  *dato7 = "gondola";
  *dato8 = "hipotenusa";

  abb_t* arbol_bb = arbol_crear(comparar_elementos_tipo_string, free);

  arbol_insertar(arbol_bb, dato2);
  arbol_insertar(arbol_bb, dato3);
  arbol_insertar(arbol_bb, dato1);
  arbol_insertar(arbol_bb, dato7);
  arbol_insertar(arbol_bb, dato5);
  arbol_insertar(arbol_bb, dato6);
  arbol_insertar(arbol_bb, dato4);
  arbol_insertar(arbol_bb, dato8);

  char* esperado_inorden[]   = {"aleph", "bifurcacion", "circulo", "daneri", "ermita", "fisura", "gondola", "hipotenusa"};
  char* esperado_preorden[]  = {"bifurcacion", "aleph", "circulo", "gondola", "ermita", "daneri", "fisura", "hipotenusa"};
  char* esperado_postorden[] = {"aleph", "daneri", "fisura", "ermita", "hipotenusa", "gondola", "circulo", "bifurcacion"};

  char** array_inorden[8];
  char** array_preorden[8];
  char** array_postorden[8];


  size_t cantidad_1 = arbol_recorrido_inorden(arbol_bb,(void**)array_inorden, 8);
  size_t cantidad_2 = arbol_recorrido_preorden(arbol_bb,(void**)array_preorden, 8);
  size_t cantidad_3 = arbol_recorrido_postorden(arbol_bb,(void**)array_postorden, 8);

  pa2m_afirmar(cantidad_1 == 8, "Se recorre el arbol completo inorden");
  pa2m_afirmar(cantidad_2 == 8, "Se recorre el arbol completo preorden");
  pa2m_afirmar(cantidad_3 == 8, "Se recorre el arbol completo postorden");

  for(size_t i = 0; i < cantidad_1; i++) {
    pa2m_afirmar(strcmp(*(char**)array_inorden[i],esperado_inorden[i]) == 0, "El elemento del array inorden es correcto");
    pa2m_afirmar(strcmp(*(char**)array_preorden[i], esperado_preorden[i]) == 0, "El elemento del array preorden es correcto");
    pa2m_afirmar(strcmp(*(char**)array_postorden[i], esperado_postorden[i]) == 0, "El elemento del array postorden es correcto");
  }

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
  pa2m_nuevo_grupo("Pruebas busqueda de datos en ABB con elementos [2, 3, 1, 5, 6, 4] - El elemento no existe en el ABB");
  dadoUnABBConElementos_SiSolicitoBuscarUnElementoQueNoExisteEnElArbol_RetornaNullPorqueNoExisteElElemento();
  pa2m_nuevo_grupo("Pruebas busqueda de datos en ABB con elementos [2, 3, 1, 5, 6, 4] - El elemento existe en el ABB");
  dadoUnABBConElementos_SiSolicitoBuscarUnElementoQueExisteEnElArbol_DevuelveElValorDelElementoCorrectamente();
  pa2m_nuevo_grupo("Pruebas Eliminar Datos en ABB NULL");
  dadoUnABBNull_SiSolicitoBorrarUnElemento_NoPermiteBorrarPorqueElABBEsNull();
  pa2m_nuevo_grupo("Pruebas Eliminar Datos en ABB Vacio");
  dadoUnABBVacio_SiSolicitoBorrarUnElemento_NoPermiteBorrarPorqueElABBEsVacio();
  pa2m_nuevo_grupo("Pruebas Eliminar datos en ABB con elementos [2, 3, 1, 5, 6, 4] - El elemento no existe en el ABB");
  dadoUnABBConElementos_SiSolicitoBorrarUnElementoQueNoExisteEnElArbol_NoPermiteBorrarPorqueNoExisteElElemento();
  pa2m_nuevo_grupo("Pruebas Eliminar datos en ABB con elementos [2, 3, 1, 5, 6, 4] - Los elementos existen en el ABB y no tienen hijos");
  dadoUnABBConElementos_SiSolicitoBorrarElementosQueExisteEnElArbolYNoTienenHijos_PermiteBorrarCorrectamente();
  pa2m_nuevo_grupo("Pruebas Eliminar datos en ABB con elementos [2, 3, 6, 5, 4, 7] - Los elementos existen en el ABB y tienen un hijo");
  dadoUnABBConElementos_SiSolicitoBorrarElementosQueExisteEnElArbolYTienenUnHijo_PermiteBorrarCorrectamente();
  pa2m_nuevo_grupo("Pruebas Eliminar datos en ABB con elementos [2, 3, 1, 7, 5, 6, 4, 8] - Los elementos existen en el ABB y tienen dos hijos");
  dadoUnABBConElementos_SiSolicitoBorrarElementosQueExisteEnElArbolYTienenDosHijos_PermiteBorrarCorrectamente();
  pa2m_nuevo_grupo("Pruebas consultar Raiz en ABB NULL");
  dadoUnABBNull_SiSolicitoVerRaiz_RetornaNull();
  pa2m_nuevo_grupo("Pruebas consultar Raiz en ABB Vacio");
  dadoUnABBVacio_SiSolicitoVerRaiz_RetornaNull();
  pa2m_nuevo_grupo("Pruebas consultar Raiz en ABB con datos");
  dadoUnABBConElementos_SiSolicitoVerRaiz_RetornaElElementoDeLaRaiz();
  pa2m_nuevo_grupo("Pruebas recorrido inorden en ABB NULL");
  dadoUnABBNull_SiSolicitoRecorrerInOrden_RetornaCorrectamenteLaCantidadDeElementosRecorridos();
  pa2m_nuevo_grupo("Pruebas recorrido inorden en ABB Vacio");
  dadoUnABBVacio_SiSolicitoRecorrerInOrden_RetornaCorrectamenteLaCantidadDeElementosRecorridos();
  pa2m_nuevo_grupo("Pruebas recorrido inorden en ABB con elementos pero con un array NULL");
  dadoUnABBConElementos_SiSolicitoRecorrerInOrdenConUnArrayNULL_RetornaCorrectamenteLaCantidadDeElementosRecorridos();
  pa2m_nuevo_grupo("Pruebas recorrido inorden en ABB con elementos pero solicitando recorrer 0 veces un array");
  dadoUnABBConElementos_SiSolicitoRecorrerInOrdenConUnArrayPasandoTamanioCero_RetornaCorrectamenteLaCantidadDeElementosRecorridos();
  pa2m_nuevo_grupo("Pruebas recorrido inorden ABB del mismo tamanio que el array");
  dadoUnABBConElementos_SiSolicitoRecorrerInOrdenConArrayDelMismoTamanioQueElABB_GuardaCorrectamenteLosElementos();
  pa2m_nuevo_grupo("Pruebas recorrido inorden ABB de mayor tamanio que el array");
  dadoUnABBConElementos_SiSolicitoRecorrerInOrdenConArrayDeMayorTamanioQueElABB_GuardaCorrectamenteLosElementos();
  pa2m_nuevo_grupo("Pruebas recorrido inorden ABB de menor tamanio que el array");
  dadoUnABBConElementos_SiSolicitoRecorrerInOrdenConArrayDeMenorTamanioQueElABB_GuardaCorrectamenteLosElementos();
  pa2m_nuevo_grupo("Pruebas recorrido preorden en ABB NULL");
  dadoUnABBNull_SiSolicitoRecorrerPreOrden_RetornaCorrectamenteLaCantidadDeElementosRecorridos();
  pa2m_nuevo_grupo("Pruebas recorrido preorden en ABB Vacio");
  dadoUnABBVacio_SiSolicitoRecorrerPreOrden_RetornaCorrectamenteLaCantidadDeElementosRecorridos();
  pa2m_nuevo_grupo("Pruebas recorrido preorden en ABB con elementos pero con un array NULL");
  dadoUnABBConElementos_SiSolicitoRecorrerPreOrdenConUnArrayNULL_RetornaCorrectamenteLaCantidadDeElementosRecorridos();
  pa2m_nuevo_grupo("Pruebas recorrido preorden en ABB con elementos pero solicitando recorrer 0 veces un array");
  dadoUnABBConElementos_SiSolicitoRecorrerPreOrdenConUnArrayPasandoTamanioCero_RetornaCorrectamenteLaCantidadDeElementosRecorridos();
  pa2m_nuevo_grupo("Pruebas recorrido preorden ABB del mismo tamanio que el array");
  dadoUnABBConElementos_SiSolicitoRecorrerPreOrdenConArrayDelMismoTamanioQueElABB_GuardaCorrectamenteLosElementos();
  pa2m_nuevo_grupo("Pruebas recorrido preorden ABB de mayor tamanio que el array");
  dadoUnABBConElementos_SiSolicitoRecorrerPreOrdenConArrayDeMayorTamanioQueElABB_GuardaCorrectamenteLosElementos();
  pa2m_nuevo_grupo("Pruebas recorrido preorden ABB de menor tamanio que el array");
  dadoUnABBConElementos_SiSolicitoRecorrerPreOrdenConArrayDeMenorTamanioQueElABB_GuardaCorrectamenteLosElementos();
  pa2m_nuevo_grupo("Pruebas recorrido postorden en ABB NULL");
  dadoUnABBNull_SiSolicitoRecorrerPostOrden_RetornaCorrectamenteLaCantidadDeElementosRecorridos();
  pa2m_nuevo_grupo("Pruebas recorrido postorden en ABB Vacio");
  dadoUnABBVacio_SiSolicitoRecorrerPostOrden_RetornaCorrectamenteLaCantidadDeElementosRecorridos();
  pa2m_nuevo_grupo("Pruebas recorrido postorden en ABB con elementos pero con un array NULL");
  dadoUnABBConElementos_SiSolicitoRecorrerPostOrdenConUnArrayNULL_RetornaCorrectamenteLaCantidadDeElementosRecorridos();
  pa2m_nuevo_grupo("Pruebas recorrido postorden en ABB con elementos pero solicitando recorrer 0 veces un array");
  dadoUnABBConElementos_SiSolicitoRecorrerPostOrdenConUnArrayPasandoTamanioCero_RetornaCorrectamenteLaCantidadDeElementosRecorridos();
  pa2m_nuevo_grupo("Pruebas recorrido postorden ABB del mismo tamanio que el array");
  dadoUnABBConElementos_SiSolicitoRecorrerPostOrdenConArrayDelMismoTamanioQueElABB_GuardaCorrectamenteLosElementos();
  pa2m_nuevo_grupo("Pruebas recorrido postorden ABB de mayor tamanio que el array");
  dadoUnABBConElementos_SiSolicitoRecorrerPostOrdenConArrayDeMayorTamanioQueElABB_GuardaCorrectamenteLosElementos();
  pa2m_nuevo_grupo("Pruebas recorrido postorden ABB de menor tamanio que el array");
  dadoUnABBConElementos_SiSolicitoRecorrerPostOrdenConArrayDeMenorTamanioQueElABB_GuardaCorrectamenteLosElementos();
  pa2m_nuevo_grupo("Pruebas iterador interno con ABB NULL");
  dadoUnABBNull_SiSolicitoIterarInternamenteTodosLosElementosEnTodosLosOrdenesPosibles_RetornaElResultadoCorrecto();
  pa2m_nuevo_grupo("Pruebas iterador interno con ABB Vacio");
  dadoUnABBVacio_SiSolicitoIterarInternamenteTodosLosElementosEnTodosLosOrdenesPosibles_RetornaElResultadoCorrecto();
  pa2m_nuevo_grupo("Pruebas iterador interno con ABB Con elementos, pero sin funcion Visitar");
  dadoUnABBConElementos_SiSolicitoIterarInternamenteTodosLosElementosEnTodosLosOrdenesPosiblesSinUnaFuncionVisitar_RetornaElResultadoCorrecto();
  pa2m_nuevo_grupo("Pruebas iterador interno con ABB Con elementos, informando funcion Visitar que recorre todos los elementos");
  dadoUnABBConElementos_SiSolicitoIterarInternamenteTodosLosElementosEnTodosLosOrdenesPosiblesConUnaFuncionVisitar_RetornaElResultadoCorrecto();
  pa2m_nuevo_grupo("Pruebas iterador interno con ABB Con elementos, informando funcion Visitar que recorre cinco elementos");
  dadoUnABBConElementos_SiSolicitoIterarInternamenteCincoElementosEnTodosLosOrdenesPosiblesConUnaFuncionVisitar_RetornaElResultadoCorrecto();
  pa2m_nuevo_grupo("Pruebas iterador interno con ABB Con elementos, informando funcion Visitar que recorre hasta encontrar el elemento de valor 5, Existiendo el elemento en el ABB");
  dadoUnABBConElementos_SiSolicitoIterarInternamenteHastaEncontrarUnElementoQueExisteEnElABBEnTodosLosOrdenesPosiblesConUnaFuncionVisitar_RetornaElResultadoCorrecto();
  pa2m_nuevo_grupo("Pruebas iterador interno con ABB Con elementos, informando funcion Visitar que recorre hasta encontrar el elemento de valor 5, No Existiendo el elemento en el ABB");
  dadoUnABBConElementos_SiSolicitoIterarInternamenteHastaEncontrarUnElementoQueNoExisteEnElABBEnTodosLosOrdenesPosiblesConUnaFuncionVisitar_RetornaElResultadoCorrecto();
  pa2m_nuevo_grupo("Pruebas ABB creacion con comparador de estructuras en Heap - Iteracion de datos y se deja destruccion a cargo del usuario");
  dadoUnABBConElementosDeTipoStringCreadosEnElHeap_SiSolicitoOperarSobreLosElementosYLuegoDestruirElArbolSinFuncionDestruccion_PermiteOperarSobreLosElementosYLuegoDestruirElArbolCorrectamente();
  pa2m_nuevo_grupo("Pruebas ABB creacion con comparador de estructuras en Heap - Iteracion de datos y se envia funcion destruccion");
  dadoUnABBConElementosDeTipoStringCreadosEnElHeap_SiSolicitoOperarSobreLosElementosYLuegoDestruirElArbolConFuncionDestruccion_PermiteOperarSobreLosElementosYLuegoDestruirElArbolCorrectamente();


  return pa2m_mostrar_reporte();
}
