#include "salon.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define FORMATO_ESCRITURA_ENTRENADOR "%s;%i\n"
#define FORMATO_ESCRITURA_POKEMON "%s;%i;%i;%i;%i;%i\n"

/**
 * Lee archivo y lo carga en memoria.
 *
 * Si no puede leer el archivo o hay un error, devuelve NULL.
 */

salon_t* crear_salon_vacio(){
    salon_t* salon = calloc(1, sizeof(salon_t));
    if(!salon)
        return NULL;

    // salon->entrenadores = NULL;

    return salon;
}

void liberar_equipo(entrenador_t* entrenador) {
    //entiendo que no deberia fallar, si el vtrlen es igual a 0
    for(size_t i  = 0; i <= vtrlen(entrenador->equipo); i++) {
        //libero el nombre del pokemon
        free(entrenador->equipo[i]->nombre);
        //libero al pokemon
        free(entrenador->equipo[i]);
    }
    //libero el array que contenia a los pokemones
    free(entrenador->equipo);
}

void liberar_entrenadores(salon_t* salon) {
    //entiendo que no deberia fallar, si el vtrlen es igual a 0
    for(size_t i = 0; i <= vtrlen(salon->entrenadores); i++) {
        //libero los pokemones del entrenador
        liberar_equipo(salon->entrenadores[i]);
        //libero el nombre del entrenador
        free(salon->entrenadores[i]->nombre);
    }
    //libero el array que contenia a los entrenadores
    free(salon->entrenadores);
}

void liberar_salon(salon_t* salon) {
    //libero entrenadores, junto con sus equipos.
    liberar_entrenadores(salon);
    //libero el salon
    free(salon);
}

salon_t* cargar_entrenador(salon_t* salon, entrenador_t* entrenador) {
    void* entrenador_aux = vtradd(salon->entrenadores, entrenador);
    if (!entrenador_aux) {
        //si falla la carga de un entrenador, libero el salon junto con los entrenadores previamente cargados y sus pokemones.
        liberar_salon(salon);
        return NULL;
    }

    //si no falló, apunto al nuevo vector dinamico de entrenadores
    salon->entrenadores = entrenador_aux;
    return salon;
}

entrenador_t* crear_entrenador_vacio(char* nombre, int victorias) {
    entrenador_t* entrenador = calloc(1, sizeof(entrenador_t));
    if(!entrenador)
        return NULL;

    strcpy(entrenador->nombre, nombre);
    entrenador->victorias = victorias;
    //entrenador->equipo = NULL;

    return entrenador;
}

salon_t* cargar_pokemon(salon_t* salon, entrenador_t* entrenador, pokemon_t* pokemon) {
    void* pokemon_aux = vtradd(entrenador->equipo, pokemon);
    if(!pokemon_aux) {
        liberar_salon(salon);
        return NULL;
    }

    entrenador->equipo = pokemon_aux;
    return salon;
}

pokemon_t* crear_pokemon(char* nombre,int nivel, int fuerza, int inteligencia, int velocidad, int defensa) {
    pokemon_t* pokemon = calloc(1, sizeof(pokemon_t));

    if(!pokemon)
        return NULL;

    strcpy(pokemon->nombre, nombre);
    pokemon->nivel = nivel;
    pokemon->fuerza = fuerza;
    pokemon->inteligencia = inteligencia;
    pokemon->velocidad = velocidad;
    pokemon->defensa = defensa;

    return pokemon;
}



salon_t* salon_leer_archivo(const char* nombre_archivo){

    FILE* archivo = fopen(nombre_archivo, "r");

    if(!archivo)
        return NULL;

    //si pude leer el archivo, ya puedo crear un salon:
    salon_t* salon = crear_salon_vacio();

    //mientras el archivo no haya llegado al final
    while(!feof(archivo)) {
        //leo una linea del archivo
        char* linea = fgets_alloc(archivo);

        //si retorna null, es porque esta leyendo una linea vacia, asi que cierro el archivo y retorno el salon creado.
        if(!linea) {
            fclosen(archivo);
            return salon;
        }

        //si lei algo, tengo que splitearlo, para convertirlo en un array dinamico.
        char** auxiliar = split(linea, ';');
        //si no pudo generar el vector dinamico, cierro el archivo, libero la linea y retorno NULL.
        //tener en cuenta que si leo más de una linea, acá seguramente tenga que liberar algo.
        if(!auxiliar) {
            fclosen(archivo);
            free(linea);
            return NULL;
        }

        //ya tengo mi array. Segun la cantidad de elementos, se si es un entrenador o un pokemon.
        //si tiene menos de dos elementos o mas de dos y menos de seis, o mas de seis, el formato del texto es incorrecto y corto la ejecucion
        if((vtrlen(auxiliar) < 2) || (vtrlen(auxiliar) > 2 && vtrlen(auxiliar) < 6) || vtrlen(auxiliar) > 6) {
            fclosen(archivo);
            free(linea);
            return NULL;
        }

        //el primer elemento siempre deberia ser un entrenador. mientras haya entrenadores, recorro el texto
        if (vtrlen(auxiliar) == 2) {
            //si es un entrenador, lo creo, sin pokemones
            char* nombre = auxiliar[0];
            int victorias = atoi(auxiliar[1]);
            entrenador_t* entrenador = crear_entrenador_vacio(nombre, victorias);

            if (!entrenador) {
                liberar_salon(salon);
                fclosen(archivo);
                return NULL;
            }

            //ahora lo agrego al salon. Desde ahora voy a poder referenciar al entrenador desde el mismo salon
            salon_t* aux_salon = cargar_entrenador(salon, entrenador);

            //si falla la carga del entrenador, libero todo y retorno NULL
            if(!aux_salon){
                liberar_salon(salon);
                fclosen(archivo);
                return NULL;
            }
            //sino, actualizo la referencia. No creo que esta linea sea necesaria.
            salon = aux_salon;

        }
        else if(vtrlen(auxiliar) == 6) {
            char* nombre = auxiliar[0];
            int nvl = atoi(auxiliar[1]);
            int def = atoi(auxiliar[2]);
            int fuer = atoi(auxiliar[3]);
            int intl = atoi(auxiliar[4]);
            int vel = atoi(auxiliar[5]);

            //si es un pokemon, lo creo.
            pokemon_t* pokemon = crear_pokemon(nombre, nvl, fuer, intl, vel, def);

            if (!pokemon) {
                liberar_salon(salon);
                fclosen(archivo);
                return NULL;
            }

            size_t pos_entrenador = vtrlen(salon->entrenadores) - 1;

            salon_t* aux_salon = cargar_pokemon(salon, salon->entrenadores[pos_entrenador], pokemon);

            //si falla la carga del entrenador, libero todo y retorno NULL
            if(!aux_salon){
                liberar_salon(salon);
                fclosen(archivo);
                return NULL;
            }
            //sino, actualizo la referencia. No creo que esta linea sea necesaria.
            salon = aux_salon;
        }
    }

    fclosen(archivo);
    return salon;
}


/**
 * Guarda el salon a un archivo.
 *
 * Devuelve la cantidad de entrenadores guardados o -1 en caso de error.
 */
int salon_guardar_archivo(salon_t* salon, const char* nombre_archivo){
    FILE* archivo_nuevo = fopen(nombre_archivo, "w");
    if(!archivo_nuevo)
        return -1;

    int cant_entrenadores_guardados = 0;
    for(size_t i = 0; i < vtrlen(salon->entrenadores); i++) {
        entrenador_t* entrenador = salon->entrenadores[i];

        int linea_escrita = fprintf(archivo_nuevo, FORMATO_ESCRITURA_ENTRENADOR, entrenador->nombre, entrenador->victorias);

        if (linea_escrita < 0) {
            return -1;
        }

        for(size_t j = 0; j < vtrlen(entrenador->equipo); j++) {
            pokemon_t* pokemon = entrenador->equipo[i];

            int linea_escrita = fprintf(archivo_nuevo, FORMATO_ESCRITURA_POKEMON, pokemon->nombre, pokemon->nivel,pokemon->defensa, pokemon->fuerza, pokemon->inteligencia, pokemon->velocidad);

            if (linea_escrita < 0) {
                return -1;
            }
        }
        cant_entrenadores_guardados++;
    }

    return cant_entrenadores_guardados;
}


/**
 * Agrega un entrenador al salon.
 *
 * El entrenador, como todos los pokemon del mismo, deben residir en memoria
 * dinámica y debe ser posible de liberar todo usando free. Una vez agregado al
 * salon, el salon toma posesión de dicha memoria y pasa a ser su
 * responsabilidad liberarla.
 *
 * Devuelve el salon o NULL en caso de error.
 */
salon_t* salon_agregar_entrenador(salon_t* salon, entrenador_t* entrenador){
    if(!salon || !entrenador)
        return NULL;

    void* entrenador_aux = vtradd(salon->entrenadores, entrenador);
    if(!entrenador_aux)
        return NULL;

    salon->entrenadores = entrenador_aux;

    return salon;
}

entrenador_t** salon_obtener_entrenadores_mas_ganadores(salon_t* salon, int cantidad_minima_victorias){
    return NULL;
}

void salon_mostrar_entrenador(entrenador_t* entrenador){

}

void salon_destruir(salon_t* salon){

}
