#include "salon.h"
#include <stdlib.h>
#include <stdio.h>
#include "abb.h"
#include "menu.h"
#include "reglas.h"
#include "gimnasios.h"
#include "utils.h"
#include <string.h>

#define ES_POKEMON (vtrlen(campos) == 6)
#define ES_ENTRENADOR (vtrlen(campos) == 2)

const int SALON_EXITO = 0;
const int SALON_ERROR = -1;

struct _salon_t
{
    abb_t *entrenadores;
    menu_t *menu_salon;
    menu_reglas_t *reglas;
    gimnasio_t **gimnasios;
};

int comparar_por_nombre(void *elemento1, void *elemento2)
{
    return strcmp(entrenador_obtener_nombre((entrenador_t *)elemento1), entrenador_obtener_nombre((entrenador_t *)elemento2));
}

int comparar_por_victorias(void *elemento1, void *elemento2)
{
    return entrenador_obtener_victorias((entrenador_t *)elemento1) - entrenador_obtener_victorias((entrenador_t *)elemento2);
}

/**
   * Creo el salon. Guardará un arbol de entrenadores por cantidad de victorias.
   * Para liberar a los entrenadores, uso su funcion de destruccion.
   **/
salon_t *salon_crear()
{
    salon_t *salon = calloc(1, sizeof(salon_t));
    if (!salon)
        return NULL;
    salon->entrenadores = arbol_crear(comparar_por_nombre, entrenador_destruir);
    if (!salon->entrenadores)
    {
        free(salon);
        return NULL;
    }
    // salon->menu_salon = salon_crear_menu();
    // if (!salon->menu_salon)
    // {
    //     arbol_destruir(salon->entrenadores);
    //     free(salon);
    //     return NULL;
    // }

    // salon->reglas = salon_crear_menu_reglas();
    // if (!salon->reglas)
    // {
    //     arbol_destruir(salon->entrenadores);
    //     menu_destruir(salon->menu_salon);
    //     free(salon);
    //     return NULL;
    // }

    // salon->gimnasios = gimnasio_inicializar_gimnasios();
    // if (!salon->gimnasios)
    // {
    //     arbol_destruir(salon->entrenadores);
    //     menu_destruir(salon->menu_salon);
    //     menu_reglas_destruir(salon->reglas);
    //     free(salon);
    //     return NULL;
    // }

    return salon;
}

bool validar_entrenadores(void *entrenador, void *extra)
{
    if (entrenador)
    {
        if (lista_vacia(entrenador_obtener_equipo((entrenador_t *)entrenador)))
        {
            *(bool *)extra = true;
            return true;
        }
    }
    return false;
}

pokemon_t *parsear_pokemon(char **campos)
{
    if (!campos || !ES_POKEMON)
        return NULL;

    char *nombre = campos[0];
    int nvl = atoi(campos[1]);
    int def = atoi(campos[2]);
    int fuer = atoi(campos[3]);
    int intl = atoi(campos[4]);
    int vel = atoi(campos[5]);

    pokemon_t *pokemon = pokemon_crear(nombre, nvl, fuer, intl, vel, def);
    return pokemon;
}

entrenador_t *parsear_entrenador(char **campos)
{
    if (!campos || !ES_ENTRENADOR)
        return NULL;
    char *nombre = campos[0];
    int victorias = atoi(campos[1]);
    entrenador_t *entrenador = entrenador_crear(nombre, victorias);
    return entrenador;
}

bool agregar_entrenador_o_destruir(salon_t *salon, entrenador_t *entrenador)
{
    if (!salon || !entrenador)
        return true;
    entrenador_t *entrenador_auxiliar = entrenador;
    int resultado = SALON_ERROR;

    if ((resultado = arbol_insertar(salon->entrenadores, entrenador)) == SALON_ERROR)
    {
        entrenador_destruir(entrenador_auxiliar);
        return true;
    }
    return false;
}

bool agregar_pokemon_o_destruir(entrenador_t *entrenador, pokemon_t *pokemon)
{
    if (!entrenador || !pokemon)
    {
        pokemon_destruir(pokemon);
        return true;
    }
    pokemon_t *pokemon_auxiliar = pokemon;
    int resultado = SALON_ERROR;
    if ((resultado = lista_encolar(entrenador_obtener_equipo(entrenador), pokemon)) == SALON_ERROR)
    {
        pokemon_destruir(pokemon_auxiliar);
        return true;
    }
    return false;
}

bool cargar_archivo(salon_t *salon, FILE *archivo)
{
    if (!salon || !archivo)
        return true;

    char *linea = NULL;
    bool error = false;
    size_t *cant_lineas_leidas = 0;
    entrenador_t *ult_entrenador = NULL;

    while (!error && (linea = fgets_alloc(archivo)) != NULL)
    {
        char **campos = split(linea, ';');

        pokemon_t *pokemon = parsear_pokemon(campos);

        entrenador_t *entrenador = parsear_entrenador(campos);

        if (pokemon != NULL)
        {

            error = agregar_pokemon_o_destruir(ult_entrenador, pokemon);
        }

        else if (entrenador != NULL)
        {
            error = agregar_entrenador_o_destruir(salon, entrenador);
            if (!error)
                ult_entrenador = entrenador;
        }
        else
        {
            error = true;
        }

        vtrfree(campos);
        free(linea);
        cant_lineas_leidas++;
    }
    if (cant_lineas_leidas == 0)
        error = true;

    return error;
}

salon_t *salon_leer_archivo(const char *nombre_archivo)
{
    if (!nombre_archivo)
        return NULL;

    FILE *archivo = fopen(nombre_archivo, "r");
    salon_t *salon = salon_crear();

    bool error = cargar_archivo(salon, archivo);

    fclosen(archivo);

    if (!error)
        abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, validar_entrenadores, &error);

    if (error)
    {
        salon_destruir(salon);
        return NULL;
    }

    return salon;
}

/**
 * Guarda el salón a un archivo (reescribiendo el archivo si existe).
 * Devuelve la cantidad de entrenadores guardados o -1 en caso de error.
 */
int salon_guardar_archivo(salon_t *salon, const char *nombre_archivo)
{
    return 0;
}

/*
 * Agrega un entrenador al salón. Devuelve el salón o NULL en caso de error.
 */
salon_t *salon_agregar_entrenador(salon_t *salon, entrenador_t *entrenador)
{
    return NULL;
}

/*
 * Obtiene una lista (a liberar por el usuario) con los entrenadores que cumplen con la función de filtro provista.
 * En caso de error devuelve NULL.
 */
lista_t *salon_filtrar_entrenadores(salon_t *salon, bool (*f)(entrenador_t *, void *), void *extra)
{
    return NULL;
}

/*
 * Recibe un string con un comando a ejecutar. 
 * Ver comandos.txt para el listado y formato de los comandos.
 * Devuelve un string a liberar por el usuario con free o NULL en caso de error.
 */
char *salon_ejecutar_comando(salon_t *salon, const char *comando)
{
    return NULL;
}

/*
 * Destruye un salón liberando toda la memoria asociada.
 */
void salon_destruir(salon_t *salon)
{
}