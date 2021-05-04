#include "salon.h"
#include "util.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


#define FORMATO_ESCRITURA_ENTRENADOR "%s;%i\n"
#define FORMATO_ESCRITURA_POKEMON "%s;%i;%i;%i;%i;%i\n"

salon_t* crear_salon_vacio(){
    salon_t* salon = calloc(1, sizeof(salon_t));
    if(!salon)
        return NULL;

    return salon;
}


void liberar_equipo(entrenador_t* entrenador) {
    if (entrenador->equipo){
        size_t tam = vtrlen(entrenador->equipo);
        for(size_t i  = 0; i < tam; i++) {
            free(entrenador->equipo[i]);
        }
    }
    free(entrenador->equipo);
}


void liberar_entrenadores(salon_t* salon) {
    if (salon->entrenadores){
        size_t tam = vtrlen(salon->entrenadores);
        for(size_t i = 0; i < tam; i++) {
            liberar_equipo(salon->entrenadores[i]);
            free(salon->entrenadores[i]);
        }
    }
    free(salon->entrenadores);
}


salon_t* cargar_entrenador(salon_t* salon, entrenador_t* entrenador) {
    void* entrenador_aux = vtradd(salon->entrenadores, entrenador);
    if (!entrenador_aux) {
        return NULL;
    }

    salon->entrenadores = (entrenador_t**)entrenador_aux;
    return salon;
}

entrenador_t* crear_entrenador_vacio(char* nombre, int victorias) {
    entrenador_t* entrenador = calloc(1, sizeof(entrenador_t));
    if(!entrenador)
        return NULL;

    strcpy(entrenador->nombre, nombre);

    entrenador->victorias = victorias;

    return entrenador;
}

salon_t* cargar_pokemon(salon_t* salon, entrenador_t* entrenador, pokemon_t* pokemon) {
    void* pokemon_aux = vtradd(entrenador->equipo, pokemon);
    if(!pokemon_aux) {
        free(pokemon);
        salon_destruir(salon);
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

    salon_t* salon = crear_salon_vacio();
    if(!salon) {
        fclosen(archivo);
        return NULL;
    }

    char* linea = fgets_alloc(archivo);

    while(linea) {
        if(!linea) {
            fclosen(archivo);
            return salon;
        }

        char** vtr_linea_aux = split(linea, ';');
        if(!vtr_linea_aux) {
            salon_destruir(salon);
            free(linea);
            fclosen(archivo);
            return NULL;
        }

        if((vtrlen(vtr_linea_aux) < 2) || (vtrlen(vtr_linea_aux) > 2 && vtrlen(vtr_linea_aux) < 6) || vtrlen(vtr_linea_aux) > 6) {
            free(linea);
            vtrfree(vtr_linea_aux);
            fclosen(archivo);
            return salon;
        }

        if (vtrlen(vtr_linea_aux) == 2) {
            char* nombre = vtr_linea_aux[0];
            int victorias = atoi(vtr_linea_aux[1]);

            entrenador_t* entrenador = crear_entrenador_vacio(nombre, victorias);
            if (!entrenador) {
                vtrfree(vtr_linea_aux);
                free(linea);
                salon_destruir(salon);
                fclosen(archivo);
                return NULL;
            }

            salon_t* aux_salon = cargar_entrenador(salon, entrenador);
            if(!aux_salon){
                liberar_equipo(entrenador);
                free(entrenador);
                vtrfree(vtr_linea_aux);
                free(linea);
                salon_destruir(salon);
                fclosen(archivo);
                return NULL;
            }
        } else if(vtrlen(vtr_linea_aux) == 6) {
            char* nombre = vtr_linea_aux[0];
            int nvl = atoi(vtr_linea_aux[1]);
            int def = atoi(vtr_linea_aux[2]);
            int fuer = atoi(vtr_linea_aux[3]);
            int intl = atoi(vtr_linea_aux[4]);
            int vel = atoi(vtr_linea_aux[5]);

            pokemon_t* pokemon = crear_pokemon(nombre, nvl, fuer, intl, vel, def);

            if (!pokemon) {
                vtrfree(vtr_linea_aux);
                free(linea);
                salon_destruir(salon);
                fclosen(archivo);
                return NULL;
            }

            size_t pos_entrenador = vtrlen(salon->entrenadores) - 1;

            salon_t* aux_salon = cargar_pokemon(salon, salon->entrenadores[pos_entrenador], pokemon);

            if(!aux_salon){
                free(pokemon);
                vtrfree(vtr_linea_aux);
                free(linea);
                salon_destruir(salon);
                fclosen(archivo);
                return NULL;
            }
        }

        free(linea);
        vtrfree(vtr_linea_aux);

        linea = fgets_alloc(archivo);
    }

    free(linea);
    fclosen(archivo);
    return salon;
}


int salon_guardar_archivo(salon_t* salon, const char* nombre_archivo) {
    if(!salon)
        return -1;
    FILE* archivo_nuevo = fopen(nombre_archivo, "w");
    if(!archivo_nuevo)
        return -1;

    int cant_entrenadores_guardados = 0;

    size_t cant_entrenadores_salon = vtrlen(salon->entrenadores);
    if(cant_entrenadores_salon == 0){
        fclosen(archivo_nuevo);
        return -1;
    }

    for(size_t i = 0; i < cant_entrenadores_salon; i++) {
        entrenador_t* entrenador = salon->entrenadores[i];

        int linea_escrita = fprintf(archivo_nuevo, FORMATO_ESCRITURA_ENTRENADOR, entrenador->nombre, entrenador->victorias);

        if (linea_escrita < 0) {
            fclosen(archivo_nuevo);
            return -1;
        }

        size_t cant_pokemon_entrenador = vtrlen(entrenador->equipo);
        for(size_t j = 0; j < cant_pokemon_entrenador; j++) {
            pokemon_t* pokemon = entrenador->equipo[j];

            int linea_escrita = fprintf(archivo_nuevo, FORMATO_ESCRITURA_POKEMON, pokemon->nombre, pokemon->nivel,pokemon->defensa, pokemon->fuerza, pokemon->inteligencia, pokemon->velocidad);

            if (linea_escrita < 0) {
                fclosen(archivo_nuevo);
                return -1;
            }
        }
        cant_entrenadores_guardados++;
    }
    fclosen(archivo_nuevo);
    return cant_entrenadores_guardados;
}


salon_t* ordenar_entrenadores(salon_t* salon) {
    size_t tam = vtrlen(salon->entrenadores);
    entrenador_t** vtr_aux_entrenadores = calloc(tam + 1, sizeof(entrenador_t*));

    for (size_t i = 0; i <=  tam; i++) {
        vtr_aux_entrenadores[i] = (entrenador_t*)salon->entrenadores[i];
    }

    entrenador_t* entrenador_aux = vtr_aux_entrenadores[tam - 1];

    bool continuar = true;
    size_t pos = 0;
    while(vtr_aux_entrenadores[pos] && continuar && pos < tam - 1) {
        if (entrenador_aux->victorias >= vtr_aux_entrenadores[pos]->victorias) {
            salon->entrenadores[pos] = vtr_aux_entrenadores[pos];
            pos++;
        } else {
            continuar = false;
        }
    }

    salon->entrenadores[pos] = entrenador_aux;
    pos++;

    while(pos < tam) {
        salon->entrenadores[pos] = vtr_aux_entrenadores[pos - 1];
        pos++;
    }

    free(vtr_aux_entrenadores);

    return salon;
}

salon_t* salon_agregar_entrenador(salon_t* salon, entrenador_t* entrenador){
    if(!salon){
        return NULL;
        }
    if(!entrenador){
        return NULL;
    }

    void* entrenador_aux = vtradd(salon->entrenadores, entrenador);

    if(!entrenador_aux){
        liberar_equipo(entrenador);
        free(entrenador);
        return NULL;
    }

    salon->entrenadores = (entrenador_t**)entrenador_aux;

    if (vtrlen(salon->entrenadores) > 1) {
        salon_t* aux  = ordenar_entrenadores(salon);
        if(!aux){
            liberar_equipo(entrenador);
            free(entrenador);
            return NULL;
        }
    }


    return salon;
}

entrenador_t** salon_obtener_entrenadores_mas_ganadores(salon_t* salon, int cantidad_minima_victorias){
    if(!salon)
        return NULL;
    if(!salon->entrenadores)
        return NULL;

    void* entrenador_aux = NULL;
    for(size_t i = 0; i < vtrlen(salon->entrenadores); i++) {
        if(salon->entrenadores[i]->victorias >= cantidad_minima_victorias){
            entrenador_aux = vtradd(entrenador_aux, salon->entrenadores[i]);
        }
    }

    entrenador_t** mejores_entrenadores = (entrenador_t**)entrenador_aux;
    return mejores_entrenadores;
}

void salon_mostrar_entrenador(entrenador_t* entrenador){

    printf("------------------------------------------------------------------------------\n");
    if(!entrenador){
        printf("No hay entrenadores para mostrar\n");
        printf("------------------------------------------------------------------------------\n");
        return;
    }

    printf("NOMBRE ENTRENADOR: %s, CANT. VICTORIAS: %d\n", entrenador->nombre, entrenador->victorias);
    printf("------------------------------------------------------------------------------\n");
    if(entrenador->equipo) {
        printf("----EQUIPO UTILIZADO:\n");
        for (size_t i = 0; i < vtrlen(entrenador->equipo); i++) {
            pokemon_t* pokemon = entrenador->equipo[i];
            printf("----NOMBRE: %s, NIV: %d, DEF: %d, FUER: %d, VEL: %d, INT: %d\n", pokemon->nombre, pokemon->nivel, pokemon->defensa, pokemon->fuerza, pokemon->velocidad, pokemon->inteligencia);
        }

        printf("------------------------------------------------------------------------------\n");
    }

}

void salon_destruir(salon_t* salon){
    liberar_entrenadores(salon);
    free(salon);
}