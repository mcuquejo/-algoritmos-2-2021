#include "lista.h"
#include "pa2mm.h"
#include <string.h>

void dadaUnaListaNull_SiCreoUnaLista_ResultaUnaListaNoNullYLaListaEstaVacia(){

  lista_t* lista = NULL;

  lista = lista_crear();
  pa2m_afirmar(lista != NULL, "se crea la lista correctamente.");
  pa2m_afirmar(lista_vacia(lista), "la lista se crea vacia");


  lista_destruir(lista);
}

bool prueba_dummy_visitar_lista_null(void* lista, void* extra) {
  return false;
}

void dadaUnaListaNull_SiRealizoOperacionesSobreLaLista_ProcesaCorrectamenteLasOperaciones(){
  lista_t* lista = NULL;
  int elemento = 1;
  lista_iterador_t* iterador = lista_iterador_crear(lista);
  size_t extra = 0;

  pa2m_afirmar(lista_insertar(lista, &elemento) == -1, "no permite insertar al final de una lista NULL");
  pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento, 0) == -1, "no permite insertar en una posicion de una lista NULL");
  pa2m_afirmar(lista_borrar(lista) == -1, "no permite borrar al final de una lista NULL");
  pa2m_afirmar(lista_borrar_de_posicion(lista, 0) == -1, "no permite borrar una posicion de una lista NULL");
  pa2m_afirmar(!lista_elemento_en_posicion(lista, 0), "no permite buscar un elemento en una posicion de una lista NULL");
  pa2m_afirmar(lista_desapilar(lista), "no permite desapilar de una lista NULL");
  pa2m_afirmar(lista_apilar(lista, &elemento), "no permite apilar en una lista NULL");
  pa2m_afirmar(lista_desencolar(lista), "no permite desencolar de una lista NULL");
  pa2m_afirmar(lista_encolar(lista, &elemento), "no permite encolar en una lista NULL");
  pa2m_afirmar(lista_elementos(lista) == 0, "lista elementos retorna 0 para una lista NULL");
  pa2m_afirmar(!iterador, "No permite crear un iterador externo sobre una lista NULL");
  pa2m_afirmar(!lista_iterador_avanzar(iterador), "no permite avanzar en un iterador creado sobre una lista NULL, porque el iterador es NULL");
  pa2m_afirmar(!lista_iterador_tiene_siguiente(iterador), "Un iterador creado sobre una lista NULL no tiene siguiente elemento, porque el iterador es NULL");
  pa2m_afirmar(!lista_iterador_elemento_actual(iterador), "no permite ver elemento actual en un iterador creado sobre una lista NULL, porque el iterador es NULL");
  pa2m_afirmar(!lista_con_cada_elemento(lista, prueba_dummy_visitar_lista_null, &extra), "no permite avanzar en un iterador interno sobre una lista NULL");

  lista_destruir(lista);
}

void dadaUnaListaVacia_SiInsertoUnElemento_ResultaUnaListaConUnElementoYElElementoEsElInsertadoYSeAcualizanLosNodosDeLaListaConElElemento(){
  lista_t* lista = NULL;
  int elemento_a_insertar = 1;

  lista = lista_crear();
  int resultado = lista_insertar(lista, &elemento_a_insertar);
  pa2m_afirmar(resultado == 0, "la insercion finaliza correctamente");
  pa2m_afirmar(lista->cantidad == 1, "ahora la lista contiene un elemento");
  pa2m_afirmar(*(int*)lista->nodo_inicio->elemento == 1, "el primer elemento es el insertado");
  pa2m_afirmar(*(int*)lista->nodo_fin->elemento == 1, "el ultimo elemento es el insertado");
  pa2m_afirmar(lista->nodo_fin->siguiente == NULL, "el elemento insertado apunta a NULL");

  lista_destruir(lista);
}

void dadaUnaLista_SiInsertoElementosAlFinal_LaListaSeAgranda() {
  lista_t* lista = lista_crear();
  int elemento_1 = 1;
  int elemento_2 = 2;
  char elemento_3 = '3';

  lista_insertar(lista, &elemento_1);
  pa2m_afirmar(lista_elementos(lista) == 1, "ahora la lista contiene un elemento");

  lista_insertar(lista, &elemento_2);
  pa2m_afirmar(lista_elementos(lista) == 2, "ahora la lista contiene dos elementos");

  lista_insertar(lista, &elemento_3);
  pa2m_afirmar(lista_elementos(lista) == 3, "ahora la lista contiene tres elementos");

  lista_destruir(lista);

}

void dadaUnaLista_SiInsertoElementosAlFinal_LosElementosSeInsertanEnOrden() {
  lista_t* lista = lista_crear();
  int elemento_1 = 1;
  int elemento_2 = 2;
  char elemento_3 = '3';

  lista_insertar(lista, &elemento_1);
  pa2m_afirmar(*(int*)lista_primero(lista) == 1, "ahora el primer elemento es 1");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 1, "ahora el ultimo elemento es 1");

  lista_insertar(lista, &elemento_2);
  pa2m_afirmar(*(int*)lista_primero(lista) == 1, "el primer elemento sigue siendo 1");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 2, "ahora el ultimo elemento es 2");

  lista_insertar(lista, &elemento_3);
  pa2m_afirmar(*(int*)lista_primero(lista) == 1, "el primer elemento sigue siendo 1");
  pa2m_afirmar(*(char*)lista_ultimo(lista) == '3', "ahora el ultimo elemento es 3");

  lista_destruir(lista);

}

void dadaUnaLista_siInsertoElementoEnPosicion_LosElementosSeInsertanEnOrden(){
  lista_t* lista = lista_crear();
  int elemento_1 = 1;
  int elemento_2 = 2;
  char elemento_3 = '3';
  int elemento_4 = 4;
  int elemento_5 = 5;
  int elemento_6 = 6;


  lista_insertar_en_posicion(lista, &elemento_1, 1);
  pa2m_afirmar(*(int*)lista_primero(lista) == 1, "La lista estaba vacia. Inserte en posicion 1, pero inserto correctamente en la posicion 0. Ahora el primer elemento es 1");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 1, "ahora el ultimo elemento es 1");

  lista_insertar_en_posicion(lista, &elemento_2, 1);
  pa2m_afirmar(*(int*)lista_primero(lista) == 1, "el primer elemento sigue siendo 1");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 2, "ahora el ultimo elemento es 2");

  lista_insertar_en_posicion(lista, &elemento_3, 2);
  pa2m_afirmar(*(int*)lista_primero(lista) == 1, "el primer elemento sigue siendo 1");
  pa2m_afirmar(*(char*)lista_ultimo(lista) == '3', "ahora el ultimo elemento es 3");

  lista_insertar_en_posicion(lista, &elemento_4, 2);
  pa2m_afirmar(*(int*)lista_primero(lista) == 1, "el primer elemento sigue siendo 1");
  pa2m_afirmar(*(int*)lista->nodo_inicio->siguiente->siguiente->elemento == 4, "El elemento en la posicion 2 se inserto correctamente.");
  pa2m_afirmar(*(char*)lista->nodo_inicio->siguiente->siguiente->siguiente->elemento == '3', "Puedo acceder al elemento en la posicion 3 navegando desde el nuevo nodo insertado..");
  pa2m_afirmar(*(char*)lista_ultimo(lista) == '3', "El ultimo elemento sigue siendo 3");

  lista_insertar_en_posicion(lista, &elemento_5, 4);
  pa2m_afirmar(*(int*)lista_primero(lista) == 1, "el primer elemento sigue siendo 1");
  pa2m_afirmar(*(int*)lista->nodo_fin->elemento == 5, "El elemento se inserto correctamente al final.");

  lista_insertar_en_posicion(lista, &elemento_6, 0);
  pa2m_afirmar(*(int*)lista_primero(lista) == 6, "el primer elemento ahora es 6");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 5, "El elemento final sigue siendo 5.");
  pa2m_afirmar(*(int*)lista->nodo_inicio->siguiente->elemento == 1, "se puede acceder al elemento siguiente a partir del nuevo nodo insertado al principio de la lista");


  lista_destruir(lista);

}

void dadaUnaLista_siInsertoElementosNULL_LaListaSeInsertaCorrectamente(){
  lista_t* lista = lista_crear();
  int* elemento_nulo_1 = NULL;

  lista_insertar(lista, elemento_nulo_1);
  pa2m_afirmar((int*)lista_primero(lista) == NULL, "el primer elemento insertado tiene valor NULL");
  pa2m_afirmar((int*)lista_ultimo(lista) == NULL, "al haber un unico elemento, el ultimo elemento es igual al primer elemento");

  lista_borrar(lista);

  pa2m_afirmar((int*)lista_primero(lista) == NULL, "Luego de borrar el elemento, el primer elemento es NULL, pero porque esta vacia la lista.");
  pa2m_afirmar((int*)lista_ultimo(lista) == NULL, "Luego de borrar el elemento, el ultimo elemento es NULL, pero porque esta vacia la lista.");

  lista_destruir(lista);
}



void dadaUnaListaVacia_siAgregoElementosDeDistintasFormasYBorroElementosAlFinal_LaListaSeActualizaCorrectamente(){
  lista_t* lista = lista_crear();
  int* elemento_nulo_1 = NULL;
  int elemento_2 = 2;
  char elemento_3 = '3';
  char* elemento_4 = "cuatro";

  pa2m_afirmar(lista_borrar(lista) == -1, "corroboramos luego de crear la lista, no se pueden eliminar elementos porque esta vacia");

  lista_insertar(lista, &elemento_nulo_1);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "el primer elemento insertado tiene valor NULL");
  pa2m_afirmar(*(int**)lista_ultimo(lista) == NULL, "al haber un unico elemento, el ultimo elemento es igual al primer elemento");

  lista_borrar(lista);

  pa2m_afirmar((int*)lista_primero(lista) == NULL, "Luego de borrar el elemento, el primer elemento es NULL, pero porque esta vacia la lista.");
  pa2m_afirmar((int*)lista_ultimo(lista) == NULL, "Luego de borrar el elemento, el ultimo elemento es NULL, pero porque esta vacia la lista.");

  pa2m_afirmar(lista_vacia(lista), "corroboramos que efectivamente la lista se encuentra vacia");

  pa2m_afirmar(lista_borrar(lista) == -1, "corroboramos que una vez vacia la lista, no se pueden eliminar elementos");


  lista_insertar(lista, &elemento_nulo_1);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Vuelvo a insertar el primer elemento con valor NULL. Debe devolver correctamente NULL.");
  pa2m_afirmar(*(int**)lista_ultimo(lista) == NULL, "al haber un unico elemento, el ultimo elemento es igual al primer elemento");

  lista_insertar(lista, &elemento_2);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Al insertar un nuevo elemento en el final, el primer sigue siendo NULL.");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 2, "El elemento final ahora tiene valor 2");

  lista_borrar(lista);

  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Luego de borrar el segundo elemento, el primer elemento sigue teniendo valor NULL.");
  pa2m_afirmar(*(int**)lista_ultimo(lista) == NULL, "Luego de borrar el segundo elemento, el ultimo elemento ahora tiene valor NULL.");

  lista_insertar_en_posicion(lista, &elemento_2, 2);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Inserto nuevamente el elemento de valor 2 en el final, el primer sigue siendo NULL.");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 2, "El elemento final ahora tiene valor 2");
  pa2m_afirmar(lista_elementos(lista) == 2, "la lista contiene dos elementos");

  lista_insertar_en_posicion(lista, &elemento_3, 1);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Inserto el elemento de valor \'3\' entre el primero y el ultimo, el primer elemento sigue siendo NULL.");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 2, "El elemento final sigue teniendo valor 2");
  pa2m_afirmar(lista_elementos(lista) == 3, "la lista contiene 3 elementos");

  lista_borrar(lista);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Luego de borrar el tercer elemento, el primer elemento sigue teniendo valor NULL.");
  pa2m_afirmar(*(char*)lista_ultimo(lista) == '3', "Luego de borrar el tercer elemento, el ultimo elemento ahora tiene valor \'3\'.");

  lista_insertar_en_posicion(lista, &elemento_2, 2);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Inserto nuevamente el elemento de valor 2 en el final, el primer sigue siendo NULL.");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 2, "El elemento final ahora tiene valor 2");
  pa2m_afirmar(lista_elementos(lista) == 3, "la lista contiene tres elementos");

  lista_insertar(lista, &elemento_4);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Inserto el elemento de valor \"cuatro\" en el final, el primer sigue siendo NULL.");
  pa2m_afirmar(strcmp(*(char**)lista_ultimo(lista), "cuatro") == 0, "El elemento final ahora tiene valor \"cuatro\"");
  pa2m_afirmar(lista_elementos(lista) == 4, "la lista contiene cuatro elementos");

  lista_borrar(lista);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Luego de borrar el cuarto elemento, el primer elemento sigue teniendo valor NULL.");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 2, "Luego de borrar el cuarto elemento, el ultimo elemento ahora tiene valor 2.");

  lista_borrar(lista);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Luego de borrar el tercer elemento, el primer elemento sigue teniendo valor NULL.");
  pa2m_afirmar(*(char*)lista_ultimo(lista) == '3', "Luego de borrar el tercer elemento, el ultimo elemento ahora tiene valor \'3\'.");

  lista_borrar(lista);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Luego de borrar el segundo elemento, el primer elemento sigue teniendo valor NULL.");
  pa2m_afirmar(*(int**)lista_ultimo(lista) == NULL, "al haber un unico elemento, el ultimo elemento es igual al primer elemento");

  lista_borrar(lista);
  pa2m_afirmar((int*)lista_primero(lista) == NULL, "Luego de borrar el elemento, el primer elemento es NULL, pero porque esta vacia la lista.");
  pa2m_afirmar((int*)lista_ultimo(lista) == NULL, "Luego de borrar el elemento, el ultimo elemento es NULL, pero porque esta vacia la lista.");

  pa2m_afirmar(lista_vacia(lista), "corroboramos que efectivamente la lista se encuentra vacia");

  pa2m_afirmar(lista_borrar(lista) == -1, "corroboramos que una vez vacia la lista, no se pueden eliminar elementos");

  lista_destruir(lista);
}

void dadaUnaListaVacia_siAgregoElementosDeDistintasFormasYBorroElementosEnPosicionFinal_LaListaSeActualizaCorrectamente(){
  lista_t* lista = lista_crear();
  int* elemento_nulo_1 = NULL;
  int elemento_2 = 2;
  char elemento_3 = '3';
  char* elemento_4 = "cuatro";

  pa2m_afirmar(lista_borrar_de_posicion(lista, lista_elementos(lista)) == -1, "corroboramos luego de crear la lista, no se pueden eliminar elementos porque esta vacia");

  lista_insertar(lista, &elemento_nulo_1);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "el primer elemento insertado tiene valor NULL");
  pa2m_afirmar(*(int**)lista_ultimo(lista) == NULL, "al haber un unico elemento, el ultimo elemento es igual al primer elemento");

  lista_borrar_de_posicion(lista, lista_elementos(lista));

  pa2m_afirmar((int*)lista_primero(lista) == NULL, "Luego de borrar el elemento, el primer elemento es NULL, pero porque esta vacia la lista.");
  pa2m_afirmar((int*)lista_ultimo(lista) == NULL, "Luego de borrar el elemento, el ultimo elemento es NULL, pero porque esta vacia la lista.");

  pa2m_afirmar(lista_vacia(lista), "corroboramos que efectivamente la lista se encuentra vacia");

  pa2m_afirmar(lista_borrar_de_posicion(lista, lista_elementos(lista)) == -1, "corroboramos que una vez vacia la lista, no se pueden eliminar elementos");


  lista_insertar(lista, &elemento_nulo_1);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Vuelvo a insertar el primer elemento con valor NULL. Debe devolver correctamente NULL.");
  pa2m_afirmar(*(int**)lista_ultimo(lista) == NULL, "al haber un unico elemento, el ultimo elemento es igual al primer elemento");

  lista_insertar(lista, &elemento_2);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Al insertar un nuevo elemento en el final, el primer sigue siendo NULL.");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 2, "El elemento final ahora tiene valor 2");

  lista_borrar_de_posicion(lista, lista_elementos(lista));

  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Luego de borrar el segundo elemento, el primer elemento sigue teniendo valor NULL.");
  pa2m_afirmar(*(int**)lista_ultimo(lista) == NULL, "Luego de borrar el segundo elemento, el ultimo elemento ahora tiene valor NULL.");

  lista_insertar_en_posicion(lista, &elemento_2, 2);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Inserto nuevamente el elemento de valor 2 en el final, el primer sigue siendo NULL.");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 2, "El elemento final ahora tiene valor 2");
  pa2m_afirmar(lista_elementos(lista) == 2, "la lista contiene dos elementos");

  lista_insertar_en_posicion(lista, &elemento_3, 1);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Inserto el elemento de valor \'3\' entre el primero y el ultimo, el primer elemento sigue siendo NULL.");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 2, "El elemento final sigue teniendo valor 2");
  pa2m_afirmar(lista_elementos(lista) == 3, "la lista contiene 3 elementos");

  lista_borrar_de_posicion(lista, lista_elementos(lista));
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Luego de borrar el tercer elemento, el primer elemento sigue teniendo valor NULL.");
  pa2m_afirmar(*(char*)lista_ultimo(lista) == '3', "Luego de borrar el tercer elemento, el ultimo elemento ahora tiene valor \'3\'.");

  lista_insertar_en_posicion(lista, &elemento_2, 2);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Inserto nuevamente el elemento de valor 2 en el final, el primer sigue siendo NULL.");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 2, "El elemento final ahora tiene valor 2");
  pa2m_afirmar(lista_elementos(lista) == 3, "la lista contiene tres elementos");

  lista_insertar(lista, &elemento_4);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Inserto el elemento de valor \"cuatro\" en el final, el primer sigue siendo NULL.");
  pa2m_afirmar(strcmp(*(char**)lista_ultimo(lista), "cuatro") == 0, "El elemento final ahora tiene valor \"cuatro\"");
  pa2m_afirmar(lista_elementos(lista) == 4, "la lista contiene cuatro elementos");

  lista_borrar_de_posicion(lista, lista_elementos(lista));
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Luego de borrar el cuarto elemento, el primer elemento sigue teniendo valor NULL.");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 2, "Luego de borrar el cuarto elemento, el ultimo elemento ahora tiene valor 2.");

  lista_borrar_de_posicion(lista, lista_elementos(lista));
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Luego de borrar el tercer elemento, el primer elemento sigue teniendo valor NULL.");
  pa2m_afirmar(*(char*)lista_ultimo(lista) == '3', "Luego de borrar el tercer elemento, el ultimo elemento ahora tiene valor \'3\'.");

  lista_borrar_de_posicion(lista, lista_elementos(lista));
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Luego de borrar el segundo elemento, el primer elemento sigue teniendo valor NULL.");
  pa2m_afirmar(*(int**)lista_ultimo(lista) == NULL, "al haber un unico elemento, el ultimo elemento es igual al primer elemento");

  lista_borrar_de_posicion(lista, lista_elementos(lista));
  pa2m_afirmar((int*)lista_primero(lista) == NULL, "Luego de borrar el elemento, el primer elemento es NULL, pero porque esta vacia la lista.");
  pa2m_afirmar((int*)lista_ultimo(lista) == NULL, "Luego de borrar el elemento, el ultimo elemento es NULL, pero porque esta vacia la lista.");

  pa2m_afirmar(lista_vacia(lista), "corroboramos que efectivamente la lista se encuentra vacia");

  pa2m_afirmar(lista_borrar_de_posicion(lista, lista_elementos(lista)) == -1, "corroboramos que una vez vacia la lista, no se pueden eliminar elementos");

  lista_destruir(lista);
}

void dadaUnaListaVacia_siAgregoElementosDeDistintasFormasYBorroElementosEnPosicionInicial_LaListaSeActualizaCorrectamente(){
  lista_t* lista = lista_crear();
  int* elemento_nulo_1 = NULL;
  int elemento_2 = 2;
  char elemento_3 = '3';
  char* elemento_4 = "cuatro";

  pa2m_afirmar(lista_borrar_de_posicion(lista, 0) == -1, "corroboramos luego de crear la lista, no se pueden eliminar elementos porque esta vacia");

  lista_insertar(lista, &elemento_nulo_1);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "el primer elemento insertado tiene valor NULL");
  pa2m_afirmar(*(int**)lista_ultimo(lista) == NULL, "al haber un unico elemento, el ultimo elemento es igual al primer elemento");

  lista_borrar_de_posicion(lista, 0);

  pa2m_afirmar((int*)lista_primero(lista) == NULL, "Luego de borrar el elemento, el primer elemento es NULL, pero porque esta vacia la lista.");
  pa2m_afirmar((int*)lista_ultimo(lista) == NULL, "Luego de borrar el elemento, el ultimo elemento es NULL, pero porque esta vacia la lista.");

  pa2m_afirmar(lista_vacia(lista), "corroboramos que efectivamente la lista se encuentra vacia");

  pa2m_afirmar(lista_borrar_de_posicion(lista, 0) == -1, "corroboramos que una vez vacia la lista, no se pueden eliminar elementos");


  lista_insertar(lista, &elemento_nulo_1);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Vuelvo a insertar el primer elemento con valor NULL. Debe devolver correctamente NULL.");
  pa2m_afirmar(*(int**)lista_ultimo(lista) == NULL, "al haber un unico elemento, el ultimo elemento es igual al primer elemento");

  lista_insertar(lista, &elemento_2);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Al insertar un nuevo elemento en el final, el primer sigue siendo NULL.");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 2, "El elemento final ahora tiene valor 2");

  lista_borrar_de_posicion(lista, 0);

  pa2m_afirmar(*(int*)lista_primero(lista) == 2, "Luego de borrar el primer elemento, el primer elemento ahora tiene valor 2.");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 2, "Luego de borrar el primer elemento, el ultimo elemento ahora tiene valor 2.");

  lista_insertar_en_posicion(lista, &elemento_nulo_1, 2);
  pa2m_afirmar(*(int*)lista_primero(lista) == 2, "Vuelvo a insertar el elemento de valor NULL, esta vez en el final. El elemento inicial sigue teniendo valor 2");
  pa2m_afirmar(*(int**)lista_ultimo(lista) == NULL, "Ahora el elemento final tiene valor NULL.");
  pa2m_afirmar(lista_elementos(lista) == 2, "la lista contiene dos elementos");

  lista_insertar_en_posicion(lista, &elemento_3, 1);
  pa2m_afirmar(*(int*)lista_primero(lista) == 2, "Inserto el elemento de valor \'3\' entre el primero y el ultimo, el primer elemento sigue siendo 2.");
  pa2m_afirmar(*(int**)lista_ultimo(lista) == NULL, "El elemento final sigue teniendo valor NULL");
  pa2m_afirmar(lista_elementos(lista) == 3, "la lista contiene 3 elementos");

  lista_borrar_de_posicion(lista, 0);
  pa2m_afirmar(*(char*)lista_primero(lista) == '3', "Luego de borrar el primer elemento de valor 2, el nuevo primer elemento ahora tiene valor \'3\'.");
  pa2m_afirmar(*(int**)lista_ultimo(lista) == NULL, "Luego de borrar el primer elemento, el ultimo elemento sigue teniendo valor NULL.");

  lista_insertar_en_posicion(lista, &elemento_2, 2);
  pa2m_afirmar(*(char*)lista_primero(lista) == '3', "Inserto nuevamente el elemento de valor 2, esta vez en el final. El primer sigue siendo \'3\'.");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 2, "El elemento final ahora tiene valor 2");
  pa2m_afirmar(lista_elementos(lista) == 3, "la lista contiene tres elementos");

  lista_insertar(lista, &elemento_4);
  pa2m_afirmar(*(char*)lista_primero(lista) == '3', "Inserto el elemento de valor \"cuatro\" en el final, el primer elemento sigue siendo \'3\'.");
  pa2m_afirmar(strcmp(*(char**)lista_ultimo(lista), "cuatro") == 0, "El elemento final ahora tiene valor \"cuatro\"");
  pa2m_afirmar(lista_elementos(lista) == 4, "la lista contiene cuatro elementos");

  lista_borrar_de_posicion(lista, 0);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Luego de borrar el primer elemento, el nuevo primer elemento ahora tiene valor NULL.");
  pa2m_afirmar(strcmp(*(char**)lista_ultimo(lista), "cuatro") == 0, "Luego de borrar el primer elemento, el ultimo elemento sigue teniendo valor \"cuatro\".");

  lista_borrar_de_posicion(lista, 0);
  pa2m_afirmar(*(int*)lista_primero(lista) == 2, "Luego de borrar el primer elemento, el nuevo primer elemento ahora tiene valor 2.");
  pa2m_afirmar(strcmp(*(char**)lista_ultimo(lista), "cuatro") == 0, "Luego de borrar el primer elemento, el ultimo elemento sigue teniendo valor \"cuatro\".");

  lista_borrar_de_posicion(lista, 0);
  pa2m_afirmar(strcmp(*(char**)lista_primero(lista), "cuatro") == 0, "Luego de borrar el primer elemento, ahora el primer elemento tiene valor \"cuatro\".");
  pa2m_afirmar(strcmp(*(char**)lista_ultimo(lista), "cuatro") == 0, "Luego de borrar el primer elemento, el ultimo elemento sigue teniendo valor \"cuatro\".");

  lista_borrar_de_posicion(lista, 0);
  pa2m_afirmar((int*)lista_primero(lista) == NULL, "Luego de borrar el primer elemento, el primer elemento es NULL, pero porque esta vacia la lista.");
  pa2m_afirmar((int*)lista_ultimo(lista) == NULL, "Luego de borrar el primer elemento, el ultimo elemento es NULL, pero porque esta vacia la lista.");

  pa2m_afirmar(lista_vacia(lista), "corroboramos que efectivamente la lista se encuentra vacia");

  pa2m_afirmar(lista_borrar_de_posicion(lista, 0) == -1, "corroboramos que una vez vacia la lista, no se pueden eliminar elementos");

  lista_destruir(lista);
}

void dadaUnaListaVacia_siAgregoElementosDeDistintasFormasYBorroElementosEnDistintasPosiciones_LaListaSeActualizaCorrectamente(){
  lista_t* lista = lista_crear();
  int* elemento_nulo_1 = NULL;
  int elemento_2 = 2;
  char elemento_3 = '3';
  char* elemento_4 = "cuatro";

  lista_insertar(lista, &elemento_nulo_1);
  lista_insertar(lista, &elemento_2);
  lista_insertar(lista, &elemento_3);

  lista_borrar_de_posicion(lista, 1);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Luego de borrar el elemento del medio, el primer elemento sigue teniendo valor NULL.");
  pa2m_afirmar(*(char*)lista->nodo_inicio->siguiente->elemento == '3', "Al borrar el elemento del medio, el elemento siguiente al primero se actualizo correctamente.");
  pa2m_afirmar(*(char*)lista_ultimo(lista) == '3', "Luego de borrar el elemento del medio, el ultimo elemento sigue teniendo valor \'3\'.");

  lista_insertar_en_posicion(lista, &elemento_2, 1);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Inserto nuevamente el elemento de valor 2, en el medio. El primer elemento sigue siendo NULL.");
  pa2m_afirmar(*(char*)lista_ultimo(lista) == '3', "El elemento final sigue teniendo valor \'3\'");

  lista_insertar(lista, &elemento_4);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Inserto el elemento de valor \"cuatro\" en el final, el primer elemento sigue siendo NULL.");
  pa2m_afirmar(strcmp(*(char**)lista_ultimo(lista), "cuatro") == 0, "El elemento final ahora tiene valor \"cuatro\"");
  pa2m_afirmar(lista_elementos(lista) == 4, "la lista contiene cuatro elementos");

  lista_borrar_de_posicion(lista, 1);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Luego de borrar el elemento de la posicion 1 (de valor 2), el primer elemento sigue teniendo valor NULL.");
  pa2m_afirmar(strcmp(*(char**)lista_ultimo(lista), "cuatro") == 0, "Luego de borrar el elemento de la posicion 1 (de valor 2), el ultimo elemento sigue teniendo valor \"cuatro\".");
  pa2m_afirmar(*(char*)lista->nodo_inicio->siguiente->elemento == '3', "Se verifica que ahora el elemento de la posicion 1 tiene valor \'3\'");
  pa2m_afirmar(strcmp(*(char**)lista->nodo_inicio->siguiente->siguiente->elemento, "cuatro") == 0, "Se verifica que desde el elemento de la posicion 1 se puede acceder al elemento siguente de manera correcta. El mismo tiene valor \"cuatro\"");

  lista_borrar_de_posicion(lista, 1);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Luego de borrar el elemento del medio (de valor \'3\'), el primer elemento sigue teniendo valor NULL.");
  pa2m_afirmar(strcmp(*(char**)lista->nodo_inicio->siguiente->elemento, "cuatro") == 0, "Al borrar el elemento del medio, el elemento siguiente al primero se actualizo correctamente.");
  pa2m_afirmar(strcmp(*(char**)lista_ultimo(lista),"cuatro") == 0, "Luego de borrar el elemento del medio, el ultimo elemento sigue teniendo valor \"cuatro\".");

  lista_destruir(lista);
}

void dadaUnaListaConElementos_siBuscoElementoEnPosicion_ObtengoElElementoCorrecto() {
  lista_t* lista = lista_crear();
  int* elemento_nulo_1 = NULL;
  int elemento_2 = 2;
  char elemento_3 = '3';
  char* elemento_4 = "cuatro";

  pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL, "Como la lista esta vacia, obtener un elemento en la posicion 0 devuelve NULL");

  lista_insertar(lista, &elemento_nulo_1);
  lista_insertar(lista, &elemento_2);
  lista_insertar(lista, &elemento_3);
  lista_insertar(lista, &elemento_4);

  pa2m_afirmar(*(int**)lista_elemento_en_posicion(lista, 0) == NULL, "El elemento en la posicion 0 tiene valor NULL");
  pa2m_afirmar(*(int*)lista_elemento_en_posicion(lista, 1) == 2, "El elemento en la posicion 1 tiene valor 2");
  pa2m_afirmar(*(char*)lista_elemento_en_posicion(lista, 2) == '3', "El elemento en la posicion 2 tiene valor \'3\'");
  pa2m_afirmar(strcmp(*(char**)lista_elemento_en_posicion(lista, 3), "cuatro") == 0, "El elemento en la posicion 3 tiene valor \"cuatro\"");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 4) == NULL, "La lista tiene 4 elementos. No existe un elemento en la posicion 4, por lo que se retorna NULL");
  lista_destruir(lista);
}

void dadaUnaListaVacia_siApiloElementos_LosElementosSeApilanCorrectamente() {
  lista_t* lista = lista_crear();
  int* elemento_nulo_1 = NULL;
  int elemento_2 = 2;
  char elemento_3 = '3';
  char* elemento_4 = "cuatro";

  pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL, "Como la lista esta vacia, obtener un elemento en la posicion 0 devuelve NULL");

  lista_apilar(lista, &elemento_nulo_1);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Al apilar un elemento de valor NULL, El primer elemento tiene valor NULL");
  pa2m_afirmar(*(int**)lista_ultimo(lista) == NULL, "Como hay un solo elemento, el ultimo elemento tambien tiene valor NULL");
  pa2m_afirmar(*(int**)lista_tope(lista) == NULL, "El tope tiene valor NULL");

  lista_apilar(lista, &elemento_2);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Al apilar un elemento de valor 2, El primer elemento de la lista sigue teniendo valor NULL");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 2, "El ultimo elemento es el apilado. Tiene valor 2");
  pa2m_afirmar(*(int*)lista_tope(lista) == 2, "El tope tiene valor 2");

  lista_apilar(lista, &elemento_3);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Al apilar un elemento de valor \'3\', El primer elemento de la lista sigue teniendo valor NULL");
  pa2m_afirmar(*(char*)lista_ultimo(lista) == '3', "El ultimo elemento de la lista ahora tiene valor \'3\'");
  pa2m_afirmar(*(char*)lista_tope(lista) == '3', "El tope tiene valor \'3\'");

  lista_apilar(lista, &elemento_4);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Al apilar un elemento de valor \"cuatro\", El primer elemento de la lista sigue teniendo valor NULL");
  pa2m_afirmar(strcmp(*(char**)lista_ultimo(lista), "cuatro") == 0, "El ultimo elemento de la lista ahora tiene valor \"cuatro\"");
  pa2m_afirmar(strcmp(*(char**)lista_tope(lista), "cuatro") == 0, "El tope tiene valor \"cuatro\"");

  lista_destruir(lista);
}

void dadaUnaListaVacia_siDesapiloElementos_NoPermiteDesapilarEnLaLista(){
  lista_t* lista = lista_crear();

  pa2m_afirmar(lista_desapilar(lista) == -1, "No se pudo desapilar en una lista vacia.");

  lista_destruir(lista);
}

void dadaUnaListaConElementosApilados_siDesapiloElementos_LosElementosSeDesapilanCorrectamente() {
  lista_t* lista = lista_crear();
  int* elemento_nulo_1 = NULL;
  int elemento_2 = 2;
  char elemento_3 = '3';
  char* elemento_4 = "cuatro";

  pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL, "Como la lista esta vacia, obtener un elemento en la posicion 0 devuelve NULL");

  lista_apilar(lista, &elemento_nulo_1);
  lista_apilar(lista, &elemento_2);
  lista_apilar(lista, &elemento_3);
  lista_apilar(lista, &elemento_4);

  pa2m_afirmar(strcmp(*(char**)lista_tope(lista), "cuatro") == 0, "el tope de la pila es \"cuatro\"");
  pa2m_afirmar(lista_desapilar(lista) == 0, "Se pudo desapilar correctamente");
  pa2m_afirmar(*(char*)lista_tope(lista) == '3', "El tope ahora es \'3\'");
  pa2m_afirmar(lista_desapilar(lista) == 0, "Se pudo desapilar correctamente");
  pa2m_afirmar(*(int*)lista_tope(lista) == 2, "El tope ahora es 2");
  pa2m_afirmar(lista_desapilar(lista) == 0, "Se pudo desapilar correctamente");
  pa2m_afirmar(*(int**)lista_tope(lista) == NULL, "El tope ahora es NULL");
  pa2m_afirmar(lista_desapilar(lista) == 0, "Se pudo desapilar correctamente");

  pa2m_afirmar(lista_tope(lista) == NULL, "El tope ahora es NULL, pero porque la lista quedo vacia");

  pa2m_afirmar(lista_vacia(lista), "la lista ahora esta vacia");
  pa2m_afirmar(lista_desapilar(lista) == -1, "No se pudo desapilar porque la lista esta vacia");
  pa2m_afirmar((void*)lista_tope(lista) == NULL, "El tope sigue siendo NULL");


  lista_destruir(lista);
}

void dadaUnaListaVacia_siEncoloElementos_LosElementosSeEncolanCorrectamente() {
  lista_t* lista = lista_crear();
  int* elemento_nulo_1 = NULL;
  int elemento_2 = 2;
  char elemento_3 = '3';
  char* elemento_4 = "cuatro";

  pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL, "Como la lista esta vacia, obtener un elemento en la posicion 0 devuelve NULL");

  lista_encolar(lista, &elemento_nulo_1);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Al encolar un elemento de valor NULL, El primer elemento tiene valor NULL");
  pa2m_afirmar(*(int**)lista_ultimo(lista) == NULL, "Como hay un solo elemento, el ultimo elemento tambien tiene valor NULL");

  lista_encolar(lista, &elemento_2);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Al encolar un elemento de valor 2, El primer elemento de la lista sigue teniendo valor NULL");
  pa2m_afirmar(*(int*)lista_ultimo(lista) == 2, "El ultimo elemento es el encolado. Tiene valor 2");

  lista_encolar(lista, &elemento_3);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Al encolar un elemento de valor \'3\', El primer elemento de la lista sigue teniendo valor NULL");
  pa2m_afirmar(*(char*)lista_ultimo(lista) == '3', "El ultimo elemento de la lista ahora tiene valor \'3\'");

  lista_encolar(lista, &elemento_4);
  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "Al encolar un elemento de valor \"cuatro\", El primer elemento de la lista sigue teniendo valor NULL");
  pa2m_afirmar(strcmp(*(char**)lista_ultimo(lista), "cuatro") == 0, "El ultimo elemento de la lista ahora tiene valor \"cuatro\"");

  lista_destruir(lista);
}

void dadaUnaListaVacia_siDesencoloElementos_NoPermiteDesencolarEnLaLista(){
  lista_t* lista = lista_crear();

  pa2m_afirmar(lista_desencolar(lista) == -1, "No se pudo desencolar en una lista vacia.");

  lista_destruir(lista);
}

void dadaUnaListaConElementosEncolados_siDesencoloElementos_LosElementosSeDesencolanCorrectamente() {
  lista_t* lista = lista_crear();
  int* elemento_nulo_1 = NULL;
  int elemento_2 = 2;
  char elemento_3 = '3';
  char* elemento_4 = "cuatro";

  pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL, "Como la lista esta vacia, obtener un elemento en la posicion 0 devuelve NULL");

  lista_encolar(lista, &elemento_nulo_1);
  lista_encolar(lista, &elemento_2);
  lista_encolar(lista, &elemento_3);
  lista_encolar(lista, &elemento_4);

  pa2m_afirmar(*(int**)lista_primero(lista) == NULL, "El primer elemento de la cola es NULL");
  pa2m_afirmar(lista_desencolar(lista) == 0, "Se pudo desencolar correctamente");

  pa2m_afirmar(*(int*)lista_primero(lista) == 2, "El tope ahora es 2");
  pa2m_afirmar(lista_desencolar(lista) == 0, "Se pudo desencolar correctamente");

  pa2m_afirmar(*(char*)lista_primero(lista) == '3', "El tope ahora es \'3\'");
  pa2m_afirmar(lista_desencolar(lista) == 0, "Se pudo desencolar correctamente");

  pa2m_afirmar(strcmp(*(char**)lista_primero(lista), "cuatro") == 0, "el tope de la pila es \"cuatro\"");
  pa2m_afirmar(lista_desencolar(lista) == 0, "Se pudo desencolar correctamente");


  pa2m_afirmar(lista_primero(lista) == NULL, "al consultar el primer elemento de la cola ahora retorna valor NULL, pero porque la lista quedo vacia");

  pa2m_afirmar(lista_vacia(lista), "la lista ahora esta vacia");
  pa2m_afirmar(lista_desencolar(lista) == -1, "No se pudo desencolar porque la lista esta vacia");
  pa2m_afirmar((void*)lista_primero(lista) == NULL, "El primer elemento sigue siendo NULL");


  lista_destruir(lista);
}

void dadoUnIteradorExternoNull_SiSolicitoRealizarOperacionesSobreUnaLista_NoPermiteRealizarLasOperaciones(){
  lista_t* lista = lista_crear();
  int* elemento_nulo_1 = NULL;
  int elemento_2 = 2;
  char elemento_3 = '3';
  char* elemento_4 = "cuatro";

  lista_encolar(lista, &elemento_nulo_1);
  lista_encolar(lista, &elemento_2);
  lista_encolar(lista, &elemento_3);
  lista_encolar(lista, &elemento_4);

  lista_iterador_t* iterador = NULL;

  pa2m_afirmar(!lista_iterador_avanzar(iterador), "no permite avanzar en un iterador NULL");
  pa2m_afirmar(!lista_iterador_tiene_siguiente(iterador), "Un iterador NULL no tiene siguiente elemento");
  pa2m_afirmar(!lista_iterador_elemento_actual(iterador), "no permite ver elemento actual en un iterador NULL");

  lista_iterador_destruir(iterador);
  lista_destruir(lista);
}

void dadoUnIteradorExterno_SiSolicitoNavegarUnaListaVacia_NoPermiteIterarEnLaLista() {
  lista_t* lista = lista_crear();
  lista_iterador_t* iterador = lista_iterador_crear(lista);

  pa2m_afirmar(!lista_iterador_elemento_actual(iterador), "el iterador se creo sobre una lista vacia. El elemento actual es NULL");
  pa2m_afirmar(!lista_iterador_tiene_siguiente(iterador), "el iterador se creo sobre una lista vacia. No tiene siguiente");
  pa2m_afirmar(!lista_iterador_avanzar(iterador), "El iterador se creo sobre una lista vacia. No se puede avanzar");

  lista_iterador_destruir(iterador);
  lista_destruir(lista);
}

void dadoUnIteradorExterno_SiSolicitoNavegarUnaListaConElementos_PermiteRecorrerLaListaCorrectamente(){
  lista_t* lista = lista_crear();
  int* elemento_nulo_1 = NULL;
  int elemento_2 = 2;
  char elemento_3 = '3';
  char* elemento_4 = "cuatro";

  pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL, "Como la lista esta vacia, obtener un elemento en la posicion 0 devuelve NULL");

  lista_encolar(lista, &elemento_nulo_1);
  lista_encolar(lista, &elemento_2);
  lista_encolar(lista, &elemento_3);
  lista_encolar(lista, &elemento_4);

  lista_iterador_t* iterador = lista_iterador_crear(lista);

  pa2m_afirmar(lista_iterador_tiene_siguiente(iterador), "El iterador puede seguir avanzando en la lista");
  pa2m_afirmar(*(int**)lista_iterador_elemento_actual(iterador) == NULL, "El primer elemento de la lista tiene valor NULL");
  pa2m_afirmar(lista_iterador_avanzar(iterador), "el iterador avanzo correctamente");

  pa2m_afirmar(lista_iterador_tiene_siguiente(iterador), "El iterador puede seguir avanzando en la lista");
  pa2m_afirmar(*(int*)lista_iterador_elemento_actual(iterador) == 2, "El segundo elemento de la lista tiene valor 2");
  pa2m_afirmar(lista_iterador_avanzar(iterador), "el iterador avanzo correctamente");

  pa2m_afirmar(lista_iterador_tiene_siguiente(iterador), "El iterador puede seguir avanzando en la lista");
  pa2m_afirmar(*(char*)lista_iterador_elemento_actual(iterador) == '3', "El tercer elemento de la lista tiene valor \'3\'");
  pa2m_afirmar(lista_iterador_avanzar(iterador), "el iterador avanzo correctamente");

  pa2m_afirmar(lista_iterador_tiene_siguiente(iterador), "El iterador puede seguir avanzando en la lista");
  pa2m_afirmar(strcmp(*(char**)lista_iterador_elemento_actual(iterador), "cuatro") == 0, "El cuarto elemento de la lista tiene valor \"cuatro\"");
  pa2m_afirmar(!lista_iterador_avanzar(iterador), "el iterador pudo seguir avanzando. Pero como era el final de la lista, retorna false.");

  pa2m_afirmar(!lista_iterador_tiene_siguiente(iterador), "El iterador no puede seguir avanzando en la lista, ya que se encuentra al final");
  pa2m_afirmar(!lista_iterador_elemento_actual(iterador), "Al final de la lista, el elemento actual es NULL");
  pa2m_afirmar(!lista_iterador_avanzar(iterador), "el iterador no pudo seguir avanzando. Ahora esta en una posicion NULL al final de la lista");

  lista_iterador_destruir(iterador);
  lista_destruir(lista);
}

void dadoUnIteradorExterno_SiSeRecorreUnaListaConElementos_LaCantidadDeElementosRecorridosEsLaDeLaLista() {
  lista_t* lista = lista_crear();
  int elemento_1 = 1;
  int elemento_2 = 2;
  int elemento_3 = 3;
  int elemento_4 = 4;

  lista_encolar(lista, &elemento_1);
  lista_encolar(lista, &elemento_2);
  lista_encolar(lista, &elemento_3);
  lista_encolar(lista, &elemento_4);

  lista_iterador_t* iterador = lista_iterador_crear(lista);

  size_t cantidad_elementos_recorridos = 0;
  while(lista_iterador_tiene_siguiente(iterador)) {
    cantidad_elementos_recorridos++;
    pa2m_afirmar(*(int*)lista_iterador_elemento_actual(iterador) == cantidad_elementos_recorridos, "El dato del elemento actual es correcto");
    lista_iterador_avanzar(iterador);
  }

  pa2m_afirmar(cantidad_elementos_recorridos == 4, "El iterador proceso 4 elementos.");

  lista_iterador_destruir(iterador);
  lista_destruir(lista);
}

bool visitar (void* dato, void* extra) {
  size_t* contador = extra;
  (*contador)++;
  return true;
}

bool mostrar_elemento(void* elemento, void* contador){
    if(elemento && contador)
        printf("Elemento %i: %c \n", (*(int*)contador)++, *(char*)elemento);
    return true;
}

void dadoUnIteradorInterno_SiSolicitoNavegarUnaListaVacia_NoPermiteIterarEnLaLista(){
  lista_t* lista = lista_crear();
  size_t cant_elementos_recorridos = 0;
  size_t resultado = lista_con_cada_elemento(lista, visitar, &cant_elementos_recorridos);
  pa2m_afirmar(resultado == 0, "No pudo recorrer elementos con el iterador interno porque la lista esta vacia");
  lista_destruir(lista);
}

void dadoUnIteradorInterno_SiSolicitoNavegarUnaListaConElementosPeroSinPasarFuncionVisitar_NoPermiteIterarEnLaLista(){
  lista_t* lista = lista_crear();
  int elemento = 1;
  lista_insertar(lista, &elemento);
  size_t cant_elementos_recorridos = 0;
  size_t resultado = lista_con_cada_elemento(lista, NULL, &cant_elementos_recorridos);
  pa2m_afirmar(resultado == 0, "No pudo recorrer elementos con el iterador interno porque la no se paso una funcion de visita.");
  lista_destruir(lista);
}

void dadoUnIteradorInterno_SiSolicitoNavegarUnaListaConElementosPeroSinPasarDatoExtra_NoPermiteIterarEnLaLista() {

  lista_t* lista = lista_crear();
  int elemento = 1;
  lista_insertar(lista, &elemento);
  size_t resultado = lista_con_cada_elemento(lista, visitar, NULL);
  pa2m_afirmar(resultado == 0, "No pudo recorrer elementos con el iterador interno porque la no se paso el parametro extra.");
  lista_destruir(lista);

}
void dadoUnIteradorInterno_SiSolicitoNavegarUnaListaConElementos_PermiteRecorrerLaListaCorrectamente(){
  lista_t* lista = lista_crear();
  int* elemento_nulo_1 = NULL;
  int elemento_2 = 2;
  char elemento_3 = '3';
  char* elemento_4 = "cuatro";


  lista_encolar(lista, &elemento_nulo_1);
  lista_encolar(lista, &elemento_2);
  lista_encolar(lista, &elemento_3);
  lista_encolar(lista, &elemento_4);


  size_t cant_elementos_recorridos = 0;
  size_t resultado = lista_con_cada_elemento(lista, visitar, &cant_elementos_recorridos);
  pa2m_afirmar(resultado == 4, "Recorrio correctamente la lista, devolviendo un total de 4 elementos recorridos");
  lista_destruir(lista);
}

bool visitar_hasta_el_tercer_elemento(void* elemento, void* extra) {
  if(*(int*)elemento == 3)
    return false;

  size_t* contador = extra;
  (*contador)++;
  return true;
}

void dadoUnIteradorInterno_SiSolicitoNavegarHastaElTercerElementoEnUnaListaConElementos_PermiteRecorrerLaListaHastaElTercerElemento(){
  lista_t* lista = lista_crear();
  int elemento_1 = 1;
  int elemento_2 = 2;
  int elemento_3 = 3;
  int elemento_4 = 4;


  lista_encolar(lista, &elemento_1);
  lista_encolar(lista, &elemento_2);
  lista_encolar(lista, &elemento_3);
  lista_encolar(lista, &elemento_4);


  size_t cant_elementos_recorridos = 0;
  size_t resultado = lista_con_cada_elemento(lista, visitar_hasta_el_tercer_elemento, &cant_elementos_recorridos);
  pa2m_afirmar(resultado == 3, "Recorrio correctamente la lista, devolviendo un total de 3 elementos recorridos");
  lista_destruir(lista);

}

void dadoUnIteradorInterno_SiSolicitoMostrarConFuncionMinipruebas_PermiteRecorrerLaListaCorrectamente(){
  lista_t* lista = lista_crear();
  char elemento_1 = '1';
  char elemento_2 = '2';
  char elemento_3 = '3';
  char elemento_4 = '4';


  lista_encolar(lista, &elemento_1);
  lista_encolar(lista, &elemento_2);
  lista_encolar(lista, &elemento_3);
  lista_encolar(lista, &elemento_4);


  size_t cant_elementos_recorridos = 0;
  size_t resultado = lista_con_cada_elemento(lista, mostrar_elemento, &cant_elementos_recorridos);
  pa2m_afirmar(resultado == 4, "Recorrio correctamente la lista, devolviendo un total de 4 elementos recorridos");
  pa2m_afirmar(cant_elementos_recorridos == 4, "Recorrio correctamente la lista, la variable cant_elementos_recorridos sumo un total de 4 elementos recorridos");
  lista_destruir(lista);

}

int main() {

  pa2m_nuevo_grupo("Pruebas de creacion y destuccion de lista");
  dadaUnaListaNull_SiCreoUnaLista_ResultaUnaListaNoNullYLaListaEstaVacia();
  pa2m_nuevo_grupo("Pruebas de operaciones sobre una lista NULL.");
  dadaUnaListaNull_SiRealizoOperacionesSobreLaLista_ProcesaCorrectamenteLasOperaciones();
  pa2m_nuevo_grupo("Pruebas de agregar elemento al final");
  dadaUnaListaVacia_SiInsertoUnElemento_ResultaUnaListaConUnElementoYElElementoEsElInsertadoYSeAcualizanLosNodosDeLaListaConElElemento();
  dadaUnaLista_SiInsertoElementosAlFinal_LaListaSeAgranda();
  dadaUnaLista_SiInsertoElementosAlFinal_LosElementosSeInsertanEnOrden();
  dadaUnaLista_siInsertoElementoEnPosicion_LosElementosSeInsertanEnOrden();
  dadaUnaLista_siInsertoElementosNULL_LaListaSeInsertaCorrectamente();
  pa2m_nuevo_grupo("Pruebas de eliminar elementos al final");
  dadaUnaListaVacia_siAgregoElementosDeDistintasFormasYBorroElementosAlFinal_LaListaSeActualizaCorrectamente();
  pa2m_nuevo_grupo("Pruebas de eliminar elementos pasando posicion pero siempre eligiendo la posicion final");
  dadaUnaListaVacia_siAgregoElementosDeDistintasFormasYBorroElementosEnPosicionFinal_LaListaSeActualizaCorrectamente();
  pa2m_nuevo_grupo("Pruebas de eliminar elementos pasando posicion pero siempre eligiendo la posicion inicial");
  dadaUnaListaVacia_siAgregoElementosDeDistintasFormasYBorroElementosEnPosicionInicial_LaListaSeActualizaCorrectamente();
  pa2m_nuevo_grupo("Pruebas de eliminar elementos pasando posicion, eligiendo siempre que sea posible posiciones intermedias.");
  dadaUnaListaVacia_siAgregoElementosDeDistintasFormasYBorroElementosEnDistintasPosiciones_LaListaSeActualizaCorrectamente();
  pa2m_nuevo_grupo("Pruebas obtener elemento en cada posicion de una lista.");
  dadaUnaListaConElementos_siBuscoElementoEnPosicion_ObtengoElElementoCorrecto();
  pa2m_nuevo_grupo("Pruebas lista manejada como pila - Apilar elementos");
  dadaUnaListaVacia_siApiloElementos_LosElementosSeApilanCorrectamente();
  pa2m_nuevo_grupo("Pruebas lista manejada como pila - Desapilar elementos");
  dadaUnaListaVacia_siDesapiloElementos_NoPermiteDesapilarEnLaLista();
  dadaUnaListaConElementosApilados_siDesapiloElementos_LosElementosSeDesapilanCorrectamente();
  pa2m_nuevo_grupo("Pruebas lista manejada como cola - Encolar elementos");
  dadaUnaListaVacia_siEncoloElementos_LosElementosSeEncolanCorrectamente();
  pa2m_nuevo_grupo("Pruebas lista manejada como cola - Desencolar elementos");
  dadaUnaListaVacia_siDesencoloElementos_NoPermiteDesencolarEnLaLista();
  dadaUnaListaConElementosEncolados_siDesencoloElementos_LosElementosSeDesencolanCorrectamente();
  pa2m_nuevo_grupo("Pruebas iterador externo NULL sobre lista");
  dadoUnIteradorExternoNull_SiSolicitoRealizarOperacionesSobreUnaLista_NoPermiteRealizarLasOperaciones();
  pa2m_nuevo_grupo("Pruebas iterador externo sobre lista vacia");
  dadoUnIteradorExterno_SiSolicitoNavegarUnaListaVacia_NoPermiteIterarEnLaLista();
  pa2m_nuevo_grupo("Pruebas iterador externo sobre lista con elementos, verificando cantidad de elementos recorridos");
  dadoUnIteradorExterno_SiSeRecorreUnaListaConElementos_LaCantidadDeElementosRecorridosEsLaDeLaLista();
  pa2m_nuevo_grupo("Pruebas iterador externo sobre lista con elementos");
  dadoUnIteradorExterno_SiSolicitoNavegarUnaListaConElementos_PermiteRecorrerLaListaCorrectamente();
  pa2m_nuevo_grupo("Pruebas iterador interno sobre lista vacia");
  dadoUnIteradorInterno_SiSolicitoNavegarUnaListaVacia_NoPermiteIterarEnLaLista();
  pa2m_nuevo_grupo("Pruebas iterador interno sobre lista no vacia, pero sin pasar funcion de visita o sin pasar dato extra");
  dadoUnIteradorInterno_SiSolicitoNavegarUnaListaConElementosPeroSinPasarFuncionVisitar_NoPermiteIterarEnLaLista();
  dadoUnIteradorInterno_SiSolicitoNavegarUnaListaConElementosPeroSinPasarDatoExtra_NoPermiteIterarEnLaLista();
  pa2m_nuevo_grupo("Pruebas iterador interno sobre lista con elementos");
  dadoUnIteradorInterno_SiSolicitoNavegarUnaListaConElementos_PermiteRecorrerLaListaCorrectamente();
  pa2m_nuevo_grupo("Pruebas iterador interno con funcion visitar que corte antes de llegar al ultimo elemento");
  dadoUnIteradorInterno_SiSolicitoNavegarHastaElTercerElementoEnUnaListaConElementos_PermiteRecorrerLaListaHastaElTercerElemento();
  pa2m_nuevo_grupo("Pruebas iterador interno sobre lista con elementos utilizando funcion de archivo minipruebas");
  dadoUnIteradorInterno_SiSolicitoMostrarConFuncionMinipruebas_PermiteRecorrerLaListaCorrectamente();
  return pa2m_mostrar_reporte();
}
