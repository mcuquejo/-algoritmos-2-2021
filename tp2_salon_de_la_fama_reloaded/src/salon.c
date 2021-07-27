#include "entrenador.h"
#include "salon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"
#include "utils.h"
#include "menu.h"

#define FORMATO_ESCRITURA_ENTRENADOR "%s;%i\n"
#define FORMATO_ESCRITURA_POKEMON "%s;%i;%i;%i;%i;%i\n"

#define ES_POKEMON vtrlen(split_linea_auxiliar) == 6
#define ES_ENTRENADOR vtrlen(split_linea_auxiliar) == 2
#define ERROR_EN_LECTURA (vtrlen(split_linea_auxiliar) < 2) || (vtrlen(split_linea_auxiliar) > 2 && vtrlen(split_linea_auxiliar) < 6) || vtrlen(split_linea_auxiliar) > 6

const int SALON_EXITO = 0;
const int SALON_ERROR = -1;

struct _salon_t{
    abb_t* entrenadores;
    menu_t* menu_salon;
};

int comparar_por_nombre(void* elemento1, void* elemento2) {
  return strcmp(entrenador_obtener_nombre((entrenador_t*)elemento1), entrenador_obtener_nombre((entrenador_t*)elemento2));
}

int comparar_por_victorias(void* elemento1, void* elemento2) {
  return entrenador_obtener_victorias((entrenador_t*)elemento1) - entrenador_obtener_victorias((entrenador_t*)elemento2);
}

//aca deberia ver si no falla
bool imprimir_pokemones(void* pokemon, void* archivo) {
    if(pokemon)
        fprintf(*(FILE**)archivo, FORMATO_ESCRITURA_POKEMON, pokemon_obtener_nombre((pokemon_t*)pokemon), pokemon_obtener_nivel((pokemon_t*)pokemon),pokemon_obtener_defensa((pokemon_t*)pokemon), pokemon_obtener_fuerza((pokemon_t*)pokemon), pokemon_obtener_inteligencia((pokemon_t*)pokemon), pokemon_obtener_velocidad((pokemon_t*)pokemon));
    return true;
}

//aca deberia ver si no falla
bool imprimir_entrenadores(void* entrenador, void* archivo) {
    if(entrenador) {
        fprintf(*(FILE**)archivo, FORMATO_ESCRITURA_ENTRENADOR, entrenador_obtener_nombre((entrenador_t*)entrenador), entrenador_obtener_victorias((entrenador_t*)entrenador));
        lista_con_cada_elemento((lista_t*)entrenador_obtener_equipo((entrenador_t*)entrenador), imprimir_pokemones, archivo);
    }
    return false;
}

bool recorrer_entrenadores(void* entrenador, void* extra) {
    if(entrenador) {
        printf("el entrenador es: %s\n", entrenador_obtener_nombre(entrenador));

        lista_encolar((lista_t*)extra, (entrenador_t*)entrenador);
    }
    return false;
}


bool salon_entrenadores(int argc, char* argv[], void* contexto) {
    salon_t* salon = contexto;

    //ESTO ESTA MAL. SOLO ES PARA MOSTRAR QUE SE EJECUTA ALGO CUANDO INVOCO AL COMANDO.
    printf("salon: %s\n", entrenador_obtener_nombre(*(entrenador_t**)salon->entrenadores->nodo_raiz->elemento));
    return false;
}

bool salon_equipo(int argc, char* argv[], void* contexto) {
    salon_t* salon = contexto;
    //ESTO ESTA MAL. SOLO ES PARA MOSTRAR QUE SE EJECUTA ALGO CUANDO INVOCO AL COMANDO.
    printf("salon: %s\n", entrenador_obtener_nombre(*(entrenador_t**)salon->entrenadores->nodo_raiz->elemento));
    return false;
}

bool salon_reglas(int argc, char* argv[], void* contexto) {
    salon_t* salon = contexto;
    //ESTO ESTA MAL. SOLO ES PARA MOSTRAR QUE SE EJECUTA ALGO CUANDO INVOCO AL COMANDO.
    printf("salon: %s\n", entrenador_obtener_nombre(*(entrenador_t**)salon->entrenadores->nodo_raiz->elemento));
    return false;
}

bool salon_comparar(int argc, char* argv[], void* contexto) {
    salon_t* salon = contexto;
    //ESTO ESTA MAL. SOLO ES PARA MOSTRAR QUE SE EJECUTA ALGO CUANDO INVOCO AL COMANDO.
    printf("salon: %s\n", entrenador_obtener_nombre(*(entrenador_t**)salon->entrenadores->nodo_raiz->elemento));
    return false;
}

bool salon_agregar_pokemon(int argc, char* argv[], void* contexto) {
    salon_t* salon = contexto;
    //ESTO ESTA MAL. SOLO ES PARA MOSTRAR QUE SE EJECUTA ALGO CUANDO INVOCO AL COMANDO.
    printf("salon: %s\n", entrenador_obtener_nombre(*(entrenador_t**)salon->entrenadores->nodo_raiz->elemento));
    return false;
}

bool salon_quitar_pokemon(int argc, char* argv[], void* contexto) {
    salon_t* salon = contexto;
    //ESTO ESTA MAL. SOLO ES PARA MOSTRAR QUE SE EJECUTA ALGO CUANDO INVOCO AL COMANDO.
    printf("salon: %s\n", entrenador_obtener_nombre(*(entrenador_t**)salon->entrenadores->nodo_raiz->elemento));
    return false;
}

bool salon_guardar(int argc, char* argv[], void* contexto) {
    salon_t* salon = contexto;
    //ESTO ESTA MAL. SOLO ES PARA MOSTRAR QUE SE EJECUTA ALGO CUANDO INVOCO AL COMANDO.
    printf("salon: %s\n", entrenador_obtener_nombre(*(entrenador_t**)salon->entrenadores->nodo_raiz->elemento));
    return false;
}


menu_t* salon_crear_menu() {
    menu_t* menu = menu_crear();
    if(!menu)
        return NULL;
    menu_agregar_comando(menu, "ENTRENADORES", "Mostrar Entrenadores. Se pueden agregar criterios de búsqueda", salon_entrenadores);
    menu_agregar_comando(menu, "EQUIPO", "Mostrar equipo de un entrenador", salon_equipo);
    menu_agregar_comando(menu, "REGLAS", "Mostrar Reglas disponibles de Combate", salon_reglas);
    menu_agregar_comando(menu, "COMPARAR", "Permite comparar equipos de dos entrenadores y definir, segun las reglas de Combate, quién ganaría un encuentro", salon_comparar);
    menu_agregar_comando(menu, "AGREGAR_POKEMON", "Permite agregar un pokemon al equipo de un Entrenador", salon_agregar_pokemon);
    menu_agregar_comando(menu, "QUITAR_POKEMON", "Permite quitar un pokemon al equipo de un Entrenador", salon_quitar_pokemon);
    menu_agregar_comando(menu, "GUARDAR", "Guarda el Salon de la Fama Pokemon a un Archivo", salon_guardar);
    return menu;
}

/**
 * Creo el salon. Guardará un arbol de entrenadores por cantidad de victorias.
 * Para liberar a los entrenadores, uso su funcion de destruccion.
 **/
salon_t* salon_crear() {
    salon_t* salon = malloc(sizeof(salon_t));
    if(!salon)
        return NULL;
    salon->entrenadores = arbol_crear(comparar_por_victorias, entrenador_destruir);
    if(!salon->entrenadores) {
        free(salon);
        return NULL;
    }
    salon->menu_salon = salon_crear_menu();
    if(!salon->menu_salon) {
        arbol_destruir(salon->entrenadores);
        free(salon);
        return NULL;
    }
    return salon;
}

/**
 * recibe un salon y un entrenador. Guardo en el arbol de entrenadores al entrenador nuevo.
 * Si se pudo guardar, retorna puntero al salon. Caso contrario retorna NULL.
 **/
salon_t* salon_cargar_entrenador(salon_t* salon, entrenador_t* entrenador) {
    int resultado = arbol_insertar(salon->entrenadores, entrenador);
    return (resultado == SALON_EXITO) ? salon : NULL;
}


/**
*  En general está bien, aunque salon_leer_archivo te quedó excesivamente larga.
*  ¿Quizas se podía estructurar de otra forma? Por ejemplo poner alguna variable de condición que te indique
*  si tenes que seguir o salir del loop y poner toda la liberación de datos afuera o algo similar
*  (las liberaciones de memoria se repiten muchas veces).
**/

salon_t* salon_leer_archivo(const char* nombre_archivo) {
    FILE* archivo = fopen(nombre_archivo, "r");
    if(!archivo)
        return NULL;

    salon_t* salon = salon_crear();
    if(!salon) {
        fclosen(archivo);
        return NULL;
    }

    //leo una linea
    char* linea = fgets_alloc(archivo);

    entrenador_t* ultimo_entrenador_insertado = NULL;
    while(linea) {
        if(!linea) {
            fclosen(archivo);
            return salon;
        }

        char** split_linea_auxiliar = split(linea, ';');
        if(!split_linea_auxiliar) {
            salon_destruir(salon);
            free(linea);
            fclosen(archivo);
            return NULL;
        }

        if(ERROR_EN_LECTURA) {
            free(linea);
            vtrfree(split_linea_auxiliar);
            fclosen(archivo);
            return salon;
        }

        if (ES_ENTRENADOR) {
            char* nombre = split_linea_auxiliar[0];
            int victorias = atoi(split_linea_auxiliar[1]);

            entrenador_t* entrenador = entrenador_crear(nombre, victorias);
            if (!entrenador) {
                vtrfree(split_linea_auxiliar);
                free(linea);
                salon_destruir(salon);
                fclosen(archivo);
            }

            salon_t* aux_salon = salon_cargar_entrenador(salon, entrenador);
            if(!aux_salon){
                entrenador_destruir(entrenador);
                vtrfree(split_linea_auxiliar);
                free(linea);
                salon_destruir(salon);
                fclosen(archivo);
                return NULL;
            }

            ultimo_entrenador_insertado = entrenador;

        } else if(ES_POKEMON) {
            char* nombre = split_linea_auxiliar[0];
            int nvl = atoi(split_linea_auxiliar[1]);
            int def = atoi(split_linea_auxiliar[2]);
            int fuer = atoi(split_linea_auxiliar[3]);
            int intl = atoi(split_linea_auxiliar[4]);
            int vel = atoi(split_linea_auxiliar[5]);

            pokemon_t* pokemon = pokemon_crear(nombre, nvl, fuer, intl, vel, def);

            if (!pokemon) {
                vtrfree(split_linea_auxiliar);
                free(linea);
                salon_destruir(salon);
                fclosen(archivo);
                return NULL;
            }

            entrenador_t* entrenador_en_arbol = arbol_buscar(salon->entrenadores, ultimo_entrenador_insertado);
            if(!entrenador_en_arbol) {
                vtrfree(split_linea_auxiliar);
                free(linea);
                salon_destruir(salon);
                fclosen(archivo);
                return NULL;
            }

            entrenador_t* entrenador_aux = entrenador_cargar_pokemon(entrenador_en_arbol, pokemon);

            if(!entrenador_aux){
                free(pokemon);
                vtrfree(split_linea_auxiliar);
                free(linea);
                salon_destruir(salon);
                fclosen(archivo);
                return NULL;
            }
        }

        free(linea);
        vtrfree(split_linea_auxiliar);

        linea = fgets_alloc(archivo);
    }

    free(linea);
    fclosen(archivo);
    return salon;
}



int salon_guardar_archivo(salon_t* salon, const char* nombre_archivo){
    if(!salon)
        return -1;
    FILE* archivo_nuevo = fopen(nombre_archivo, "w");
    if(!archivo_nuevo)
        return -1;

    int cant_entrenadores_guardados = (int)abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, imprimir_entrenadores, &archivo_nuevo);

    fclosen(archivo_nuevo);
    return (cant_entrenadores_guardados) ? cant_entrenadores_guardados : -1;
}


salon_t* salon_agregar_entrenador(salon_t* salon, entrenador_t* entrenador){
    if(!salon || !entrenador)
        return NULL;

    int resultado = arbol_insertar(salon->entrenadores, entrenador);

    if(resultado == SALON_ERROR){
        entrenador_destruir(entrenador);
        return NULL;
    }

    return salon;
}

lista_t* salon_filtrar_entrenadores(salon_t* salon , bool (*f)(entrenador_t*, void*), void* extra){
    if(!salon || !f)
        return NULL;

    lista_t* lista_aux = lista_crear(NULL);
    if(!lista_aux)
        return NULL;

    int cant = (int)abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, recorrer_entrenadores, lista_aux);
    printf("recorri %i elementos\n", cant);

    lista_iterador_t* iterador_lista = lista_iterador_crear(lista_aux);
    lista_t* lista_final = lista_crear(NULL);
    while(lista_iterador_tiene_siguiente(iterador_lista)) {
        if(f(lista_iterador_elemento_actual(iterador_lista), extra)) {
            lista_encolar(lista_final, lista_iterador_elemento_actual(iterador_lista));
        }
        lista_iterador_avanzar(iterador_lista);
    }
    lista_iterador_destruir(iterador_lista);
    lista_destruir(lista_aux);
    return lista_final;
}

char* salon_ejecutar_comando(salon_t* salon, const char* comando) {
    if(!salon || !comando)
        return NULL;

    printf("se ejecutó el comando: %s\n", comando);

    char* resultado = calloc(1, sizeof(char) * 100);
    if(!resultado)
        return NULL;

    //funcion de prueba. Tengo que ajustar el comando para que reciba un puntero char (extra), donde voy a ir concatenando los resultados
    menu_procesar_opcion(salon->menu_salon, comando, &salon);
    return resultado;
}


void salon_destruir(salon_t* salon) {
    if(salon) {
        arbol_destruir(salon->entrenadores);
        menu_destruir(salon->menu_salon);
        free(salon);
    }

}