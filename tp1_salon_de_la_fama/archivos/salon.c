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

    // salon->entrenadores = NULL;

    return salon;
}

void liberar_equipo(entrenador_t* entrenador) {
    if (!entrenador->equipo)
        return;

    //entiendo que no deberia fallar, si el vtrlen es igual a 0
    for(size_t i  = 0; i < vtrlen(entrenador->equipo); i++) {
        //libero el nombre del pokemon
        //free(entrenador->equipo[i]->nombre);
        //libero al pokemon
        free(entrenador->equipo[i]);
    }
    //libero el array que contenia a los pokemones
    free(entrenador->equipo);
}

void liberar_entrenadores(salon_t* salon) {
    if (!salon->entrenadores)
        return;
    //entiendo que no deberia fallar, si el vtrlen es igual a 0
    for(size_t i = 0; i < vtrlen(salon->entrenadores); i++) {
        //libero los pokemones del entrenador
        liberar_equipo(salon->entrenadores[i]);
        //libero el nombre del entrenador
        //free(salon->entrenadores[i]->nombre);
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
    //leo una linea del archivo
    char* linea = fgets_alloc(archivo);
    if(!linea) {
            fclosen(archivo);
            return salon;
        }

    //mientras el archivo no haya llegado al final
    while(linea) {
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
            free(linea);
            fclosen(archivo);
            return NULL;
        }

        //ya tengo mi array. Segun la cantidad de elementos, se si es un entrenador o un pokemon.
        //si tiene menos de dos elementos o mas de dos y menos de seis, o mas de seis, el formato del texto es incorrecto y corto la ejecucion
        if((vtrlen(auxiliar) < 2) || (vtrlen(auxiliar) > 2 && vtrlen(auxiliar) < 6) || vtrlen(auxiliar) > 6) {
            free(linea);
            vtrfree(auxiliar);
            fclosen(archivo);
            return salon;
        }

        //el primer elemento siempre deberia ser un entrenador. mientras haya entrenadores, recorro el texto
        if (vtrlen(auxiliar) == 2) {
            //si es un entrenador, lo creo, sin pokemones
            char* nombre = auxiliar[0];
            int victorias = atoi(auxiliar[1]);
            entrenador_t* entrenador = crear_entrenador_vacio(nombre, victorias);

            if (!entrenador) {
                vtrfree(auxiliar);
                free(linea);
                liberar_salon(salon);
                fclosen(archivo);
                return NULL;
            }

            //ahora lo agrego al salon. Desde ahora voy a poder referenciar al entrenador desde el mismo salon
            salon_t* aux_salon = cargar_entrenador(salon, entrenador);

            //si falla la carga del entrenador, libero todo y retorno NULL
            if(!aux_salon){
                vtrfree(auxiliar);
                free(linea);
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
                vtrfree(auxiliar);
                free(linea);
                liberar_salon(salon);
                fclosen(archivo);
                return NULL;
            }

            size_t pos_entrenador = vtrlen(salon->entrenadores) - 1;

            salon_t* aux_salon = cargar_pokemon(salon, salon->entrenadores[pos_entrenador], pokemon);

            //si falla la carga del entrenador, libero todo y retorno NULL
            if(!aux_salon){
                vtrfree(auxiliar);
                free(linea);
                liberar_salon(salon);
                fclosen(archivo);
                return NULL;
            }
            //sino, actualizo la referencia. No creo que esta linea sea necesaria.
            salon = aux_salon;
        }
        free(linea);
        vtrfree(auxiliar);
        linea = fgets_alloc(archivo);
    }

    fclosen(archivo);
    return salon;
}


int salon_guardar_archivo(salon_t* salon, const char* nombre_archivo){
    FILE* archivo_nuevo = fopen(nombre_archivo, "w");
    if(!archivo_nuevo)
        return -1;

    int cant_entrenadores_guardados = 0;
    for(size_t i = 0; i < vtrlen(salon->entrenadores); i++) {
        entrenador_t* entrenador = salon->entrenadores[i];

        int linea_escrita = fprintf(archivo_nuevo, FORMATO_ESCRITURA_ENTRENADOR, entrenador->nombre, entrenador->victorias);

        if (linea_escrita < 0) {
            fclosen(archivo_nuevo);
            return -1;
        }

        for(size_t j = 0; j < vtrlen(entrenador->equipo); j++) {
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


salon_t* salon_agregar_entrenador(salon_t* salon, entrenador_t* entrenador){
    if(!salon){
        liberar_equipo(entrenador);
        return NULL;
        }
    if(!entrenador){
        liberar_salon(salon);
        return NULL;
    }

    //si no hay entrenadores, directamente agrego el entrenador nuevo.
    if (vtrlen(salon->entrenadores) == 0) {
        void* entrenador_aux = vtradd(salon->entrenadores, entrenador);

        if(!entrenador_aux){
            //si fallo libero el entrenador pasado por argumento
            liberar_equipo(entrenador);
            //si falla el proceso, se va a devolver null, por lo que destruyo el salon
            liberar_salon(salon);
            return NULL;
        }

        salon->entrenadores = entrenador_aux;

    //si ya hay entrenadores, debería pasar por aca
    } else {
        size_t posicion = 0;
        bool continuar = true;
        void* entrenador_aux = NULL;
        void* vtr_dinamico_auxiliar_entrenadores = NULL;
        //mientras me encuentre dentor del vector de entrenadores
        while (posicion < vtrlen(salon->entrenadores) && continuar) {
            //comparo las victorias del entrenador agregado contra el de la posicion actual. Inserto el menor.
            if(entrenador->victorias >= salon->entrenadores[posicion]->victorias ){
                //si el valor del archivo era menor al que estoy insertando, lo inserto primero en un vector dinamico auxiliar.
                entrenador_aux = vtradd(vtr_dinamico_auxiliar_entrenadores, salon->entrenadores[posicion]);
                if(!entrenador_aux) {
                    //probablemente acá tenga que liberar algo. Por ahora solo hago un return NULL
                    liberar_equipo(entrenador);
                    liberar_salon(salon);
                    vtrfree(vtr_dinamico_auxiliar_entrenadores);
                    return NULL;
                }

                vtr_dinamico_auxiliar_entrenadores = entrenador_aux;
                //ya que inserté el dato, me muevo a la siguiente posicion.
                posicion++;
            } else {
                //como el campo original no es mayor, continuar será false. No actualizo la posicion. Si quedan registros, quiero continuar desde el actual para insertarlo luego del nuevo entrenador.
                continuar = false;
            }
            //actualizo la posicion
        }

        //si sali del vector, es porque el siguiente elemento (si existe, es mayor o igual a mi). inserto el entrenador.
        entrenador_aux = vtradd(vtr_dinamico_auxiliar_entrenadores, entrenador);
        if(!entrenador_aux) {
            //probablemente acá tenga que liberar algo. Por ahora solo hago un return NULL
            liberar_equipo(entrenador);
            liberar_salon(salon);
            vtrfree(vtr_dinamico_auxiliar_entrenadores);
            return NULL;
        }

        vtr_dinamico_auxiliar_entrenadores = entrenador_aux;

        //ahora, si quedan, puedo insertar el resto de los entrenadores.
        while (posicion < vtrlen(salon->entrenadores)) {
            entrenador_aux = vtradd(vtr_dinamico_auxiliar_entrenadores, salon->entrenadores[posicion]);
            if(!entrenador_aux) {
                //probablemente acá tenga que liberar algo. Por ahora solo hago un return NULL
                liberar_equipo(entrenador);
                liberar_salon(salon);
                vtrfree(vtr_dinamico_auxiliar_entrenadores);
                return NULL;
            }

            vtr_dinamico_auxiliar_entrenadores = entrenador_aux;
            posicion++;
        }

        //ya tengo mi vector auxiliar completo. Libero el vector original y luego apunto a mi nuevo vector.
        // vtrfree(salon->entrenadores);

        salon->entrenadores = vtr_dinamico_auxiliar_entrenadores;
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
        //esto esta mal porque cada vez que ejecuto la funcion, podria recibir un null y perder la referencia a todos los datos...
        if(salon->entrenadores[i]->victorias >= cantidad_minima_victorias){
            entrenador_aux = vtradd(entrenador_aux, salon->entrenadores[i]);
        }
    }

    entrenador_t** mejores_entrenadores = (entrenador_t**)entrenador_aux;
    return mejores_entrenadores;
}

void salon_mostrar_entrenador(entrenador_t* entrenador){

}

void salon_destruir(salon_t* salon){
    liberar_salon(salon);
}
