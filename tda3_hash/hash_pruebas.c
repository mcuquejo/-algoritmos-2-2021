#include "hash.h"
#include <stdio.h>
#include "pa2mm.h"
#include <string.h>

#define CANTIDAD_MINIMA 3
#define CANTIDAD 10

void dadoUnHashNull_SiCreoUnHashDeUnElemento_ElHashSeCreaConTresElementos() {
  hash_t* hash = hash_crear(NULL, 1);
  pa2m_afirmar(hash, "El hash no es NULL. Se creo correctamente");
  pa2m_afirmar(hash_cantidad(hash) == 0, "El hash se crea vacio");
  hash_destruir(hash);
}

void dadoUnHashNull_SiCreoUnHash_ElHashSeCreaCorrectamente() {
  hash_t* hash = hash_crear(NULL, CANTIDAD);
  pa2m_afirmar(hash, "El hash no es NULL. Se creo correctamente");
  pa2m_afirmar(hash_cantidad(hash) == 0, "El hash se crea vacio");
  hash_destruir(hash);
}

void dadoUnHashNull_SiIntentoRealizarOperacionesSobreElHash_NoPermiteRealizarOperaciones() {
  hash_t* hash = NULL;
  const char* clave = "102624";
  const char* valor = "MAURO CUQUEJO";
  pa2m_afirmar(hash_cantidad(hash) == 0, "El hash NULL retorna 0 elementos");
  pa2m_afirmar(!hash_obtener(hash, clave), "No se puede obtener una clave en un Hash NULL");
  pa2m_afirmar(!hash_contiene(hash, clave), "El hash NULL no contiene claves");
  pa2m_afirmar(hash_insertar(hash, clave, &valor) == -1, "No se puede insertar una clave en un Hash NULL");
  pa2m_afirmar(hash_quitar(hash, clave) == -1, "No se puede quitar una clave en un Hash NULL");
  hash_destruir(hash);
}

void dadoUnHashVacio_SiIntentoRealizarOperacionesSobreElHash_NoPermiteRealizarOperaciones() {
  hash_t* hash = hash_crear(NULL, CANTIDAD);
  const char* clave = "102624";
  pa2m_afirmar(hash_cantidad(hash) == 0, "El hash vacio retorna 0 elementos");
  pa2m_afirmar(!hash_obtener(hash, clave), "No se puede obtener una clave en un Hash vacio");
  pa2m_afirmar(!hash_contiene(hash, clave), "El hash vacio no contiene claves");
  pa2m_afirmar(hash_quitar(hash, clave) == -1, "No se puede quitar una clave en un Hash vacio");
  hash_destruir(hash);
}

void dadoUnHashVacio_SiInsertoElementos_ElHashYaNoEstaVacio() {
  hash_t* hash = hash_crear(NULL, CANTIDAD);
  const char* clave = "102624";
  const char* valor = "MAURO CUQUEJO";
  const char* clave_2 = "102625";
  const char* valor_2 = "JORGITO PEREZ";
  hash_insertar(hash, clave, &valor);
  pa2m_afirmar(hash_cantidad(hash) == 1, "El hash ahora contiene un elemento");
  hash_insertar(hash, clave_2, &valor_2);
  pa2m_afirmar(hash_cantidad(hash) == 2, "El hash ahora contiene dos elementos");
  hash_destruir(hash);
}

void dadoUnHashNULL_SiVerificoExistenciaElementosEnElHash_NoEncuentroLosElementos() {
  hash_t* hash = NULL;
  const char* clave_1 = "102624";
  pa2m_afirmar(!hash_contiene(hash, clave_1), "No se encuentra la clave 1 en el hash. Porque el hash es NULL");
}

void dadoUnHashSinElementos_SiVerificoExistenciaElementosEnElHash_NoEncuentroLosElementos() {
  hash_t* hash = hash_crear(NULL, CANTIDAD);
  const char* clave_1 = "102624";
  pa2m_afirmar(!hash_contiene(hash, clave_1), "No se encuentra la clave 1 en el hash. Porque el hash no tiene elementos");
  hash_destruir(hash);

}

void dadoUnHashConElementos_SiVerificoExistenciaElementosQueSiExistenEnElHash_EncuentroLosElementos() {
  hash_t* hash = hash_crear(NULL, CANTIDAD);
  const char* clave_1 = "102624";
  const char* valor_1 = "MAURO CUQUEJO";
  const char* clave_2 = "102625";
  const char* valor_2 = "JORGITO PEREZ";
  const char* clave_3 = "102626";
  const char* valor_3 = "MAXIMO COSSETTI";

  hash_insertar(hash, clave_1, &valor_1);
  hash_insertar(hash, clave_2, &valor_2);
  hash_insertar(hash, clave_3, &valor_3);

  pa2m_afirmar(hash_contiene(hash, clave_1), "Se encuentra la clave 1 en el hash");
  pa2m_afirmar(hash_contiene(hash, clave_2), "Se encuentra la clave 2 en el hash");
  pa2m_afirmar(hash_contiene(hash, clave_3), "Se encuentra la clave 3 en el hash");

  hash_destruir(hash);
}

void dadoUnHashConElementos_SiObtengoValorDeElementosQueSiExistenEnElHash_ReciboElValorCorrectoDeLosElementos() {
  hash_t* hash = hash_crear(NULL, CANTIDAD);

  const char* clave_1 = "102624";
  const char* valor_1 = "MAURO CUQUEJO";
  const char* clave_2 = "102625";
  const char* valor_2 = "JORGITO PEREZ";
  const char* clave_3 = "102626";
  const char* valor_3 = "MAXIMO COSSETTI";

  hash_insertar(hash, clave_1, &valor_1);
  hash_insertar(hash, clave_2, &valor_2);
  hash_insertar(hash, clave_3, &valor_3);

  pa2m_afirmar(strcmp(*(char**)hash_obtener(hash, clave_1), valor_1) == 0, "Se obtiene correctamente el valor de la clave 1");
  pa2m_afirmar(strcmp(*(char**)hash_obtener(hash, clave_2), valor_2) == 0, "Se obtiene correctamente el valor de la clave 2");
  pa2m_afirmar(strcmp(*(char**)hash_obtener(hash, clave_3), valor_3) == 0, "Se obtiene correctamente el valor de la clave 3");

  const char* valor_1_modificado = "FRANCO MILAZZO";

  hash_insertar(hash, clave_1, &valor_1_modificado);
  pa2m_afirmar(strcmp(*(char**)hash_obtener(hash, clave_1), valor_1) != 0, "Se modifico valor de clave 1. Ahora el valor del hash es distinto al del valor 1");
  pa2m_afirmar(strcmp(*(char**)hash_obtener(hash, clave_1), valor_1_modificado) == 0, "Al haber modificado el valor de clave 1, ahora el valor del hash es igual al del valor 1 modificado");

  hash_destruir(hash);
}

void dadoUnHashConElementos_SiInsertoElementosEnElHashQueColisionen_SeInsertanCorrectamente() {
  hash_t* hash = hash_crear(NULL, CANTIDAD_MINIMA);

  const char* clave_1 = "pepe";
  const char* valor_1 = "MAURO CUQUEJO";
  const char* clave_2 = "pepa";
  const char* valor_2 = "JORGITO PEREZ";
  const char* clave_3 = "pepo";
  const char* valor_3 = "MAXIMO COSSETTI";
  const char* clave_4 = "pipo";
  const char* valor_4 = "PEDRO ROSEMBLAT";

  hash_insertar(hash, clave_1, &valor_1);
  hash_insertar(hash, clave_2, &valor_2);
  hash_insertar(hash, clave_3, &valor_3);
  hash_insertar(hash, clave_4, &valor_4);

  pa2m_afirmar(strcmp(*(char**)hash_obtener(hash, clave_1), valor_1) == 0, "Se obtiene correctamente el valor de la clave 1");
  pa2m_afirmar(strcmp(*(char**)hash_obtener(hash, clave_2), valor_2) == 0, "Se obtiene correctamente el valor de la clave 2");
  pa2m_afirmar(strcmp(*(char**)hash_obtener(hash, clave_3), valor_3) == 0, "Se obtiene correctamente el valor de la clave 3");
  pa2m_afirmar(strcmp(*(char**)hash_obtener(hash, clave_4), valor_4) == 0, "Se obtiene correctamente el valor de la clave 4");


  const char* valor_1_modificado = "FRANCO MILAZZO";

  hash_insertar(hash, clave_1, &valor_1_modificado);
  pa2m_afirmar(strcmp(*(char**)hash_obtener(hash, clave_1), valor_1) != 0, "Se modifico valor de clave 1. Ahora el valor del hash es distinto al del valor 1");
  pa2m_afirmar(strcmp(*(char**)hash_obtener(hash, clave_1), valor_1_modificado) == 0, "Al haber modificado el valor de clave 1, ahora el valor del hash es igual al del valor 1 modificado");

  hash_destruir(hash);
}

void dadoUnHashConElementos_SiEliminoElementos_LosElementosSeEliminanCorrectamente() {
  hash_t* hash = hash_crear(NULL, 8);

  const char* clave_1 = "pepe";
  const char* valor_1 = "MAURO CUQUEJO";
  const char* clave_2 = "pepa";
  const char* valor_2 = "JORGITO PEREZ";
  const char* clave_3 = "pepo";
  const char* valor_3 = "MAXIMO COSSETTI";
  const char* clave_4 = "pipo";
  const char* valor_4 = "PEDRO ROSEMBLAT";
  const char* clave_5 = "zapato";
  const char* valor_5 = "ERNESTO SABATO";
  const char* clave_6 = "joya";
  const char* valor_6 = "ERIK LONROT";
  const char* clave_7 = "cera";
  const char* valor_7 = "ANASTASIA NIKOLAYEVNA";

  hash_insertar(hash, clave_1, &valor_1);
  hash_insertar(hash, clave_2, &valor_2);
  hash_insertar(hash, clave_3, &valor_3);
  hash_insertar(hash, clave_4, &valor_4);
  hash_insertar(hash, clave_5, &valor_5);
  hash_insertar(hash, clave_6, &valor_6);
  hash_insertar(hash, clave_7, &valor_7);

  pa2m_afirmar(hash_quitar(hash,clave_7) == 0, "La clave se cera elimina correctamente");
  pa2m_afirmar(!hash_contiene(hash, clave_7), "La clave cera ya no existe en el hash");

  hash_insertar(hash, clave_7, &valor_7);
  pa2m_afirmar(hash_contiene(hash, clave_7), "La clave cera vuelve a insertarse en el hash");

  pa2m_afirmar(hash_quitar(hash, clave_6) == 0, "La clave joya se elimina correctamente");

  pa2m_afirmar(!hash_contiene(hash, clave_6), "La clave joya ya no existe en el hash");
  pa2m_afirmar(hash_contiene(hash, clave_7), "La clave cera sigue pudiendose encontrar en el hash");
  hash_insertar(hash, clave_6, &valor_6);
  pa2m_afirmar(hash_contiene(hash, clave_6), "La clave joya se vuelve a insertar en el hash en el hash");

  pa2m_afirmar(hash_quitar(hash,clave_7) == 0, "La clave se cera elimina correctamente");
  pa2m_afirmar(!hash_contiene(hash, clave_7), "La clave cera ya no existe en el hash");

  pa2m_afirmar(hash_contiene(hash, clave_6), "La clave joya sigue pudiendose encontrar en el hash");
  hash_insertar(hash, clave_7, &valor_7);
  pa2m_afirmar(hash_contiene(hash, clave_7), "La clave cera vuelve a insertarse en el hash");

  pa2m_afirmar(hash_quitar(hash,clave_7) == 0, "La clave se cera elimina correctamente");
  pa2m_afirmar(!hash_contiene(hash, clave_7), "La clave cera ya no existe en el hash");
  pa2m_afirmar(hash_contiene(hash, clave_6), "La clave joya sigue pudiendose encontrar en el hash");



  hash_destruir(hash);
}

bool recorrer_todos_los_elementos(hash_t* hash, const char* clave, void* aux) {
  (*(size_t*)aux)++;
  return false;
}

bool recorrer_algunos_elementos(hash_t* hash, const char* clave, void* aux) {
  (*(size_t*)aux)++;
  if((*(size_t*)aux) == 3)
    return true;
  return false;
}

void dadoUnHashNull_SiIteroElHash_DevuelveCero(){
  hash_t* hash = NULL;
  size_t contador = 0;
  pa2m_afirmar(hash_con_cada_clave(hash, recorrer_todos_los_elementos, &contador) == 0, "El resultado de recorrer un hash NULL es 0");
  pa2m_afirmar(contador == 0, "El resultado del contador al recorrer un hash NULL es 0");
  hash_destruir(hash);
}

void dadoUnHashVacio_SiIteroElHash_DevuelveCero(){
  hash_t* hash = hash_crear(NULL, 8);
  size_t contador = 0;
  pa2m_afirmar(hash_con_cada_clave(hash, recorrer_todos_los_elementos, &contador) == 0, "El resultado de recorrer un hash sin elementos es 0");
  pa2m_afirmar(contador == 0, "El resultado del contador al recorrer un hash sin elementos es 0");
  hash_destruir(hash);
}

void dadoUnHashConElementos_SiIteroSinFuncionVisitar_NoPermiteIterar(){
  hash_t* hash = hash_crear(NULL, 8);

  const char* clave_1 = "pepe";
  const char* valor_1 = "MAURO CUQUEJO";
  const char* clave_2 = "pepa";
  const char* valor_2 = "JORGITO PEREZ";
  const char* clave_3 = "pepo";
  const char* valor_3 = "MAXIMO COSSETTI";
  const char* clave_4 = "pipo";
  const char* valor_4 = "PEDRO ROSEMBLAT";
  const char* clave_5 = "zapato";
  const char* valor_5 = "ERNESTO SABATO";
  const char* clave_6 = "joya";
  const char* valor_6 = "ERIK LONROT";
  const char* clave_7 = "cera";
  const char* valor_7 = "ANASTASIA NIKOLAYEVNA";

  hash_insertar(hash, clave_1, &valor_1);
  hash_insertar(hash, clave_2, &valor_2);
  hash_insertar(hash, clave_3, &valor_3);
  hash_insertar(hash, clave_4, &valor_4);
  hash_insertar(hash, clave_5, &valor_5);
  hash_insertar(hash, clave_6, &valor_6);
  hash_insertar(hash, clave_7, &valor_7);

  size_t contador = 0;

  pa2m_afirmar(hash_con_cada_clave(hash, NULL, &contador) == 0, "No recorre ningun elemento porque no se paso funcion visitar");
  pa2m_afirmar(contador == 0, "El contador sigue siendo 0 porque no se itero ningun elemento");
  hash_destruir(hash);
}

void dadoUnHashConElementos_SiIteroTodosLosElementos_IteraCorrectamente(){
  hash_t* hash = hash_crear(NULL, 8);

  const char* clave_1 = "pepe";
  const char* valor_1 = "MAURO CUQUEJO";
  const char* clave_2 = "pepa";
  const char* valor_2 = "JORGITO PEREZ";
  const char* clave_3 = "pepo";
  const char* valor_3 = "MAXIMO COSSETTI";
  const char* clave_4 = "pipo";
  const char* valor_4 = "PEDRO ROSEMBLAT";
  const char* clave_5 = "zapato";
  const char* valor_5 = "ERNESTO SABATO";
  const char* clave_6 = "joya";
  const char* valor_6 = "ERIK LONROT";
  const char* clave_7 = "cera";
  const char* valor_7 = "ANASTASIA NIKOLAYEVNA";

  hash_insertar(hash, clave_1, &valor_1);
  hash_insertar(hash, clave_2, &valor_2);
  hash_insertar(hash, clave_3, &valor_3);
  hash_insertar(hash, clave_4, &valor_4);
  hash_insertar(hash, clave_5, &valor_5);
  hash_insertar(hash, clave_6, &valor_6);
  hash_insertar(hash, clave_7, &valor_7);

  size_t contador = 0;

  pa2m_afirmar(hash_con_cada_clave(hash, recorrer_todos_los_elementos, &contador) == 7, "Recorre 7 elementos");
  pa2m_afirmar(contador == 7, "El puntero a funcion actualizo correctamente el contador");
  hash_destruir(hash);
}

void dadoUnHashConElementos_SiIteroAlgunosLosElementos_IteraCorrectamente(){
  hash_t* hash = hash_crear(NULL, 8);

  const char* clave_1 = "pepe";
  const char* valor_1 = "MAURO CUQUEJO";
  const char* clave_2 = "pepa";
  const char* valor_2 = "JORGITO PEREZ";
  const char* clave_3 = "pepo";
  const char* valor_3 = "MAXIMO COSSETTI";
  const char* clave_4 = "pipo";
  const char* valor_4 = "PEDRO ROSEMBLAT";
  const char* clave_5 = "zapato";
  const char* valor_5 = "ERNESTO SABATO";
  const char* clave_6 = "joya";
  const char* valor_6 = "ERIK LONROT";
  const char* clave_7 = "cera";
  const char* valor_7 = "ANASTASIA NIKOLAYEVNA";

  hash_insertar(hash, clave_1, &valor_1);
  hash_insertar(hash, clave_2, &valor_2);
  hash_insertar(hash, clave_3, &valor_3);
  hash_insertar(hash, clave_4, &valor_4);
  hash_insertar(hash, clave_5, &valor_5);
  hash_insertar(hash, clave_6, &valor_6);
  hash_insertar(hash, clave_7, &valor_7);

  size_t contador = 0;

  pa2m_afirmar(hash_con_cada_clave(hash, recorrer_algunos_elementos, &contador) == 3, "Recorre 3 elementos");
  pa2m_afirmar(contador == 3, "El puntero a funcion actualizo correctamente el contador");
  hash_destruir(hash);
}

char* dup_string(const char* s){
  if(!s)
    return NULL;

  char* p = malloc(strlen(s)+1);
  strcpy(p,s);
  return p;
}

void dadoUnHashConElementosEnHeap_SiSolicitoRealizarOperacionesSobreElHash_PermiteOperarCorrectamente() {
  hash_t* hash = hash_crear(free, 8);

  const char* clave_1 = "pepe";
  const char* valor_1 = "MAURO CUQUEJO";
  const char* clave_2 = "pepa";
  const char* valor_2 = "JORGITO PEREZ";
  const char* clave_3 = "pepo";
  const char* valor_3 = "MAXIMO COSSETTI";
  const char* clave_4 = "pipo";
  const char* valor_4 = "PEDRO ROSEMBLAT";
  const char* clave_5 = "zapato";
  const char* valor_5 = "ERNESTO SABATO";
  const char* clave_6 = "joya";
  const char* valor_6 = "ERIK LONROT";
  const char* clave_7 = "cera";
  const char* valor_7 = "ANASTASIA NIKOLAYEVNA";

  hash_insertar(hash, clave_1, dup_string(valor_1));
  hash_insertar(hash, clave_2, dup_string(valor_2));
  hash_insertar(hash, clave_3, dup_string(valor_3));
  hash_insertar(hash, clave_4, dup_string(valor_4));
  hash_insertar(hash, clave_5, dup_string(valor_5));
  hash_insertar(hash, clave_6, dup_string(valor_6));
  hash_insertar(hash, clave_7, dup_string(valor_7));


  pa2m_afirmar(hash_contiene(hash, clave_7), "La clave cera existe en el hash");
  pa2m_afirmar(hash_quitar(hash,clave_7) == 0, "La clave se cera elimina correctamente");
  pa2m_afirmar(!hash_contiene(hash, clave_7), "La clave cera ya no existe en el hash");

  hash_insertar(hash, clave_7, dup_string(valor_7));
  pa2m_afirmar(hash_contiene(hash, clave_7), "La clave cera vuelve a insertarse en el hash");

  pa2m_afirmar(hash_quitar(hash, clave_6) == 0, "La clave joya se elimina correctamente");

  pa2m_afirmar(!hash_contiene(hash, clave_6), "La clave joya ya no existe en el hash");
  pa2m_afirmar(hash_contiene(hash, clave_7), "La clave cera sigue pudiendose encontrar en el hash");
  hash_insertar(hash, clave_6, dup_string(valor_6));
  pa2m_afirmar(hash_contiene(hash, clave_6), "La clave joya se vuelve a insertar en el hash en el hash");

  pa2m_afirmar(hash_quitar(hash,clave_7) == 0, "La clave se cera elimina correctamente");
  pa2m_afirmar(!hash_contiene(hash, clave_7), "La clave cera ya no existe en el hash");

  pa2m_afirmar(hash_contiene(hash, clave_6), "La clave joya sigue pudiendose encontrar en el hash");
  hash_insertar(hash, clave_7, dup_string(valor_7));
  pa2m_afirmar(hash_contiene(hash, clave_7), "La clave cera vuelve a insertarse en el hash");

  pa2m_afirmar(hash_quitar(hash,clave_7) == 0, "La clave se cera elimina correctamente");
  pa2m_afirmar(!hash_contiene(hash, clave_7), "La clave cera ya no existe en el hash");
  pa2m_afirmar(hash_contiene(hash, clave_6), "La clave joya sigue pudiendose encontrar en el hash");

  size_t contador = 0;

  pa2m_afirmar(hash_con_cada_clave(hash, recorrer_algunos_elementos, &contador) == 3, "Recorre 3 elementos");
  pa2m_afirmar(contador == 3, "El puntero a funcion actualizo correctamente el contador");

  contador = 0;
  pa2m_afirmar(hash_con_cada_clave(hash, recorrer_todos_los_elementos, &contador) == 6, "Recorre 6 elementos");
  pa2m_afirmar(contador == 6, "El puntero a funcion actualizo correctamente el contador");
  hash_destruir(hash);
}

void dadoUnHashVacio_SiSeInsertanElementosDeFormaMasiva_LosElementosSeInsertanDeFormaCorrecta(){
  hash_t* hash = hash_crear(free, 8);

  char clave_string[20];
  for(int clave=1; clave <= 500; clave++) {
    sprintf(clave_string, "%i", clave);
    hash_insertar(hash, clave_string, dup_string(clave_string));
  }

  bool comparacion_exitosa = true;
  int clave = 1;
  while (comparacion_exitosa && clave <= 500) {
    sprintf(clave_string, "%i", clave);
    comparacion_exitosa = strcmp((char*)hash_obtener(hash, clave_string), clave_string) == 0;
    clave++;
  }
  pa2m_afirmar(comparacion_exitosa, "Las 500 claves se obtuvieron correctamente");

  size_t contador = 0;
  pa2m_afirmar(hash_con_cada_clave(hash, recorrer_todos_los_elementos, &contador) == 500, "se recorrieron correctamente los 500 elementos con el iterador");
  pa2m_afirmar(contador == 500, "El contador se actualizo correctamente");

  int eliminacion_exitosa = 0;
  clave = 1;
  while (eliminacion_exitosa != -1 && clave <= 200) {
    sprintf(clave_string, "%i", clave);
    eliminacion_exitosa = hash_quitar(hash, clave_string);
    clave++;
  }
  pa2m_afirmar(eliminacion_exitosa != -1, "Se eliminaron correctamente 200 claves");

  contador = 0;
  pa2m_afirmar(hash_cantidad(hash) == 300, "El hash contiene 300 elementos");
  pa2m_afirmar(hash_con_cada_clave(hash, recorrer_todos_los_elementos, &contador) == 300, "se recorrieron correctamente los 300 elementos con el iterador");
  pa2m_afirmar(contador == 300, "El contador se actualizo correctamente");

  hash_destruir(hash);
}

int main(){

  pa2m_nuevo_grupo("Pruebas Creacion Hash");
  dadoUnHashNull_SiCreoUnHash_ElHashSeCreaCorrectamente();
  dadoUnHashNull_SiCreoUnHashDeUnElemento_ElHashSeCreaConTresElementos();
  pa2m_nuevo_grupo("Pruebas Operar sobre Hash NULL o Hash sin elementos");
  dadoUnHashNull_SiIntentoRealizarOperacionesSobreElHash_NoPermiteRealizarOperaciones();
  dadoUnHashVacio_SiIntentoRealizarOperacionesSobreElHash_NoPermiteRealizarOperaciones();
  pa2m_nuevo_grupo("Pruebas Insertar elementos en Hash sin funcion destruccion");
  dadoUnHashVacio_SiInsertoElementos_ElHashYaNoEstaVacio();
  pa2m_nuevo_grupo("Pruebas verificar existencia elementos en Hash NULL");
  dadoUnHashNULL_SiVerificoExistenciaElementosEnElHash_NoEncuentroLosElementos();
  pa2m_nuevo_grupo("Pruebas verificar existencia elementos en Hash Vacio");
  dadoUnHashSinElementos_SiVerificoExistenciaElementosEnElHash_NoEncuentroLosElementos();
  pa2m_nuevo_grupo("Pruebas verificar existencia elementos insertados en Hash");
  dadoUnHashConElementos_SiVerificoExistenciaElementosQueSiExistenEnElHash_EncuentroLosElementos();
  pa2m_nuevo_grupo("Pruebas valores de elementos insertados en Hash");
  dadoUnHashConElementos_SiObtengoValorDeElementosQueSiExistenEnElHash_ReciboElValorCorrectoDeLosElementos();
  pa2m_nuevo_grupo("Pruebas insercion con colision");
  dadoUnHashConElementos_SiInsertoElementosEnElHashQueColisionen_SeInsertanCorrectamente();
  pa2m_nuevo_grupo("Pruebas Eliminacion elementos del hash");
  dadoUnHashConElementos_SiEliminoElementos_LosElementosSeEliminanCorrectamente();
  pa2m_nuevo_grupo("Pruebas Iterar un hash NULL y un hash vacio");
  dadoUnHashNull_SiIteroElHash_DevuelveCero();
  dadoUnHashVacio_SiIteroElHash_DevuelveCero();
  pa2m_nuevo_grupo("Pruebas Iterar todos los elementos del hash");
  dadoUnHashConElementos_SiIteroTodosLosElementos_IteraCorrectamente();
  pa2m_nuevo_grupo("Pruebas Iterar algunos elementos del hash");
  dadoUnHashConElementos_SiIteroAlgunosLosElementos_IteraCorrectamente();
  pa2m_nuevo_grupo("Pruebas Iterar elementos del hash sin pasar funcion visitar");
  dadoUnHashConElementos_SiIteroSinFuncionVisitar_NoPermiteIterar();
  pa2m_nuevo_grupo("Pruebas operaciones Hash con elementos en Heap");
  dadoUnHashConElementosEnHeap_SiSolicitoRealizarOperacionesSobreElHash_PermiteOperarCorrectamente();
  pa2m_nuevo_grupo("Pruebas operaciones Hash insercion masiva con elementos en Heap");
  dadoUnHashVacio_SiSeInsertanElementosDeFormaMasiva_LosElementosSeInsertanDeFormaCorrecta();
  return pa2m_mostrar_reporte();
}
