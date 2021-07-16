#include "hash.h"
#include <stdio.h>
#include "pa2mm.h"
#include <string.h>

#define CANTIDAD_MINIMA 3
#define CANTIDAD 10

void dadoUnHashNull_SiCreoUnHash_ElHashSeCreaCorrectamente() {
  hash_t* hash = hash_crear(NULL, CANTIDAD);
  pa2m_afirmar(hash, "El hash no es NULL. Se creo correctamente");
  pa2m_afirmar(hash_cantidad(hash) == 0, "El hash se crea vacio");
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

  hash_imprimir(hash);
  pa2m_afirmar(hash_quitar(hash,clave_7) == 0, "La clave se cera elimina correctamente");
  pa2m_afirmar(!hash_contiene(hash, clave_7), "La clave cera ya no existe en el hash");
  hash_imprimir(hash);
  hash_insertar(hash, clave_7, &valor_7);
  pa2m_afirmar(hash_contiene(hash, clave_7), "La clave cera vuelve a insertarse en el hash");
  hash_imprimir(hash);
  pa2m_afirmar(hash_quitar(hash, clave_6) == 0, "La clave joya se elimina correctamente");
  hash_imprimir(hash);
  pa2m_afirmar(!hash_contiene(hash, clave_6), "La clave joya ya no existe en el hash");
  pa2m_afirmar(hash_contiene(hash, clave_7), "La clave cera sigue pudiendose encontrar en el hash");
  hash_insertar(hash, clave_6, &valor_6);
  pa2m_afirmar(hash_contiene(hash, clave_6), "La clave joya se vuelve a insertar en el hash en el hash");
  hash_imprimir(hash);
  pa2m_afirmar(hash_quitar(hash,clave_7) == 0, "La clave se cera elimina correctamente");
  pa2m_afirmar(!hash_contiene(hash, clave_7), "La clave cera ya no existe en el hash");
  hash_imprimir(hash);
  pa2m_afirmar(hash_contiene(hash, clave_6), "La clave joya sigue pudiendose encontrar en el hash");
  hash_insertar(hash, clave_7, &valor_7);
  pa2m_afirmar(hash_contiene(hash, clave_7), "La clave cera vuelve a insertarse en el hash");
  hash_imprimir(hash);
  pa2m_afirmar(hash_quitar(hash,clave_7) == 0, "La clave se cera elimina correctamente");
  pa2m_afirmar(!hash_contiene(hash, clave_7), "La clave cera ya no existe en el hash");
  pa2m_afirmar(hash_contiene(hash, clave_6), "La clave joya sigue pudiendose encontrar en el hash");
  hash_imprimir(hash);


  hash_destruir(hash);
}

bool recorrer_todos_los_elementos(hash_t* hash, const char* clave, void* aux) {
  printf("la clave es -> %s\n",clave);
  (*(size_t*)aux)++;

  return true;
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

int main(){
  pa2m_nuevo_grupo("Pruebas Creacion Hash");
  dadoUnHashNull_SiCreoUnHash_ElHashSeCreaCorrectamente();
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
  return pa2m_mostrar_reporte();
}
