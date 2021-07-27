#include "pa2mm.h"
#include "src/salon.h"

bool filtrar_entrenadores_por_victorias(entrenador_t* entrenador, void* cant_victorias) {
    if(!entrenador)
        return false;
    printf("entrenador: %s, victorias: %i\n", entrenador_obtener_nombre(entrenador), entrenador_obtener_victorias(entrenador));
    return entrenador_obtener_victorias(entrenador) > *(int*)cant_victorias;
}

void probarQueFuncioneMasoMeno() {
    salon_t* salon = salon_leer_archivo("salones/salon_estandar.txt");
    entrenador_t* entrenador = entrenador_crear("MAURO", 10);
    pokemon_t* pokemon = pokemon_crear("PIKACHU",10,10,10,10,10);
    entrenador_cargar_pokemon(entrenador, pokemon);
    salon_agregar_entrenador(salon, entrenador);

    int cant_entrenadores = salon_guardar_archivo(salon, "salones/salon_salida.txt");

    printf("se guardaron %i entrenadores en el archivo\n", cant_entrenadores);
    int cantidad_victorias = 10;
    lista_t* lista = salon_filtrar_entrenadores(salon, filtrar_entrenadores_por_victorias, &cantidad_victorias);
    printf("cantidad de entrenadores que cumplieron con esta condicion (10 victorias): %zu\n", lista_elementos(lista));

    lista_destruir(lista);

    cantidad_victorias = 50;
    lista = salon_filtrar_entrenadores(salon, filtrar_entrenadores_por_victorias, &cantidad_victorias);
    printf("cantidad de entrenadores que cumplieron con esta condicion (50 victorias): %zu\n", lista_elementos(lista));

    lista_destruir(lista);

    cantidad_victorias = 100;
    lista = salon_filtrar_entrenadores(salon, filtrar_entrenadores_por_victorias, &cantidad_victorias);
    printf("cantidad de entrenadores que cumplieron con esta condicion (100 victorias): %zu\n", lista_elementos(lista));

    char* resultado = salon_ejecutar_comando(salon, "ENTRENADORES");

    free(resultado);
    lista_destruir(lista);

    salon_destruir(salon);
}

int main(){

    pa2m_nuevo_grupo("Alguna prueba");
    probarQueFuncioneMasoMeno();

    return pa2m_mostrar_reporte();
}
