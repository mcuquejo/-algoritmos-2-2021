#include "hash_abierto.h"
#include "hash_cerrado.h"
#include <stdio.h>
#include "pa2mm.h"
#include <string.h>

void probarHashAbierto(){
  hash_t* hash = hash_crear(3);
  size_t i = 0;

  int padrones[] = {12312312,3123123,1212312,312,312312,1123123};

  hash_insertar(hash, "Lucas", padrones+ i++);
  hash_insertar(hash, "Mauro", padrones+ i++);
  hash_insertar(hash, "Eloy", padrones+ i++);
  hash_insertar(hash, "Julian", padrones+ i++);
  hash_insertar(hash, "Gabriel", padrones+ i++);
  hash_insertar(hash, "Daniel", padrones+ i++);

  pa2m_afirmar(*(int*)hash_buscar(hash, "Mauro") == 3123123, "El padron de mauro es 3123123");

}

void probarHashCerrado(){
  playa_t* playa = playa_crear();

  vacacionista_t vaca_1 = {.nombre = "Nicolas Sibicouske", .dni = 123456};
  vacacionista_t vaca_2 = {.nombre = "Puchi", .dni = 123456};
  vacacionista_t vaca_3 = {.nombre = "Dios", .dni = 1};
  vacacionista_t vaca_4 = {.nombre = "Julia", .dni = 709345934};
  vacacionista_t vaca_5 = {.nombre = "Lucia", .dni = 6453435};

  playa_alquilar_carpa(playa, vaca_1);
  playa_alquilar_carpa(playa, vaca_2);
  playa_alquilar_carpa(playa, vaca_3);
  playa_alquilar_carpa(playa, vaca_4);
  playa_alquilar_carpa(playa, vaca_5);
  playa_mostrar(playa);


  playa_destruir(playa);
}

int main(){
  pa2m_nuevo_grupo("Pruebas Creacion Hash");
  //probarHashAbierto();
  probarHashCerrado();
  return pa2m_mostrar_reporte();
}
