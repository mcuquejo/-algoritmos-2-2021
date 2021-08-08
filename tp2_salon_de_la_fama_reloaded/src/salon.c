#include "salon.h"
#include "abb.h"
#include "entrenador.h"
#include "menu.h"
#include "reglas.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define FORMATO_ESCRITURA_ENTRENADOR "%s;%i\n"
#define FORMATO_ESCRITURA_ARCH_ENTRENADOR "%s%s,%i\n"
#define FORMATO_ESCRITURA_ARCH_ENTRENADOR_SOLO_NOMBRE "%s%s\n"
#define FORMATO_ESCRITURA_POKEMON "%s;%i;%i;%i;%i;%i\n"
#define FORMATO_ESCRITURA_ARCH_POKEMON "%s%s,%i,%i,%i,%i,%i\n"

#define ES_POKEMON (vtrlen(campos) == 6)
#define ES_ENTRENADOR (vtrlen(campos) == 2)

const int SALON_EXITO = 0;
const int SALON_ERROR = -1;

struct _salon_t
{
    abb_t *entrenadores;
    menu_t *menu_salon;
    menu_reglas_t *reglas;
};

/****************************************************************************************************************************************
 * COMPARADORES ARBOL
 *****************************************************************************************************************************************/
int comparar_por_nombre(void *elemento1, void *elemento2)
{
    return strcmp(entrenador_obtener_nombre((entrenador_t *)elemento1), entrenador_obtener_nombre((entrenador_t *)elemento2));
}

int comparar_por_victorias(void *elemento1, void *elemento2)
{
    return entrenador_obtener_victorias((entrenador_t *)elemento1) - entrenador_obtener_victorias((entrenador_t *)elemento2);
}
/****************************************************************************************************************************************
 * COMPARADORES ARBOL
 *****************************************************************************************************************************************/

//voy a validar al momento de crear un salon leyendo un archivo que cada entrenador creado tenga al menos un pokemon
//su algun entrenador tiene 0 pokemones, extra (error), pasa a ser true y corto el recorrido por el arbol
bool validar_entrenadores(void *entrenador, void *extra)
{
    if (entrenador) {
        size_t cant_pokemon = lista_elementos(entrenador_obtener_equipo((entrenador_t *)entrenador));
        if (cant_pokemon == 0) {
            *(bool *)extra = true;
            return false;
        }
    }
    return true;
}

/****************************************************************************************************************************************
 * FUNCIONES PARA IMPRIMIR EN ARCHIVO (SALON GUARDAR ARCHIVO)
 *****************************************************************************************************************************************/
//aca deberia ver si no falla
bool imprimir_pokemones(void *pokemon, void *archivo)
{
    if (pokemon) {
        fprintf(*(FILE **)archivo, FORMATO_ESCRITURA_POKEMON, pokemon_obtener_nombre((pokemon_t *)pokemon), pokemon_obtener_nivel((pokemon_t *)pokemon), pokemon_obtener_defensa((pokemon_t *)pokemon), pokemon_obtener_fuerza((pokemon_t *)pokemon), pokemon_obtener_inteligencia((pokemon_t *)pokemon), pokemon_obtener_velocidad((pokemon_t *)pokemon));
        return true;
    }
    return false;
}

//aca deberia ver si no falla
bool imprimir_entrenadores(void *entrenador, void *archivo)
{
    if (entrenador) {
        fprintf(*(FILE **)archivo, FORMATO_ESCRITURA_ENTRENADOR, entrenador_obtener_nombre((entrenador_t *)entrenador), entrenador_obtener_victorias((entrenador_t *)entrenador));
        lista_con_cada_elemento((lista_t *)entrenador_obtener_equipo((entrenador_t *)entrenador), imprimir_pokemones, archivo);
        return false;
    }
    return true;
}
/****************************************************************************************************************************************
 * FUNCIONES PARA IMPRIMIR EN ARCHIVO (SALON GUARDAR ARCHIVO)
 *****************************************************************************************************************************************/

/****************************************************************************************************************************************
  * FUNCIONES PARA ARNAR STRINGS PARA LOS COMANDOS
  *****************************************************************************************************************************************/
bool imprimir_pokemones_en_pantalla(void *pokemon, void *buffer)
{
    if (pokemon) {
        char niv[10];
        sprintf(niv, "%i", pokemon_obtener_nivel((pokemon_t *)pokemon));
        char def[10];
        sprintf(def, "%i", pokemon_obtener_defensa((pokemon_t *)pokemon));
        char fue[10];
        sprintf(fue, "%i", pokemon_obtener_fuerza((pokemon_t *)pokemon));
        char intel[10];
        sprintf(intel, "%i", pokemon_obtener_inteligencia((pokemon_t *)pokemon));
        char vel[10];
        sprintf(vel, "%i", pokemon_obtener_velocidad((pokemon_t *)pokemon));
        size_t longitud = strlen(*(char **)buffer) + strlen(pokemon_obtener_nombre((pokemon_t *)pokemon)) + strlen(niv) + strlen(def) + strlen(fue) + strlen(intel) + strlen(vel) + 2; //longitud del "%s;%i\n\0"
        char texto_auxiliar[longitud];
        sprintf(texto_auxiliar, FORMATO_ESCRITURA_ARCH_POKEMON, *(char **)buffer, pokemon_obtener_nombre((pokemon_t *)pokemon), pokemon_obtener_nivel((pokemon_t *)pokemon), pokemon_obtener_defensa((pokemon_t *)pokemon), pokemon_obtener_fuerza((pokemon_t *)pokemon), pokemon_obtener_inteligencia((pokemon_t *)pokemon), pokemon_obtener_velocidad((pokemon_t *)pokemon));
        //*(char**)buffer = realloc(*(char**)buffer, longitud);
        strcpy(*(char **)buffer, texto_auxiliar);
    }
    return true;
}

bool imprimir_entrenadores_en_pantalla(void *entrenador, void *buffer)
{
    if (entrenador) {
        //paso a char* el nro de victorias
        char victorias[10];
        sprintf(victorias, "%i", entrenador_obtener_victorias((entrenador_t *)entrenador));
        size_t longitud = strlen(*(char **)buffer) + strlen(entrenador_obtener_nombre((entrenador_t *)entrenador)) + strlen(victorias) + 2; //longitud del "%s;%i\n\0"
        char texto_auxiliar[longitud];
        sprintf(texto_auxiliar, FORMATO_ESCRITURA_ARCH_ENTRENADOR, *(char **)buffer, entrenador_obtener_nombre((entrenador_t *)entrenador), entrenador_obtener_victorias((entrenador_t *)entrenador));
        //*(char**)buffer = realloc(*(char**)buffer, longitud);
        strcpy(*(char **)buffer, texto_auxiliar);
    }
    return false;
}

//el problema es que para lista necesito que retorne true, y para ABB, false. Sino, serían exactamente iguales!!!! (CAMBIAR)
bool imprimir_entrenadores_en_pantalla_lista(void *entrenador, void *buffer)
{
    if (entrenador) {
        //paso a char* el nro de victorias
        char victorias[10];
        sprintf(victorias, "%i", entrenador_obtener_victorias((entrenador_t *)entrenador));
        size_t longitud = strlen(*(char **)buffer) + strlen(entrenador_obtener_nombre((entrenador_t *)entrenador)) + strlen(victorias) + 2; //longitud del "%s;%i\n\0"
        char texto_auxiliar[longitud];
        sprintf(texto_auxiliar, FORMATO_ESCRITURA_ARCH_ENTRENADOR, *(char **)buffer, entrenador_obtener_nombre((entrenador_t *)entrenador), entrenador_obtener_victorias((entrenador_t *)entrenador));
        //*(char**)buffer = realloc(*(char**)buffer, longitud);
        strcpy(*(char **)buffer, texto_auxiliar);
    }
    return true;
}

bool imprimir_entrenadores_en_pantalla_lista_solo_nombre(void *entrenador, void *buffer)
{
    if (entrenador) {
        size_t longitud = strlen(*(char **)buffer) + strlen(entrenador_obtener_nombre((entrenador_t *)entrenador)) + 2; //longitud del "%s\n\0"
        char texto_auxiliar[longitud];
        sprintf(texto_auxiliar, FORMATO_ESCRITURA_ARCH_ENTRENADOR_SOLO_NOMBRE, *(char **)buffer, entrenador_obtener_nombre((entrenador_t *)entrenador));
        //*(char**)buffer = realloc(*(char**)buffer, longitud);
        strcpy(*(char **)buffer, texto_auxiliar);
    }
    return true;
}
/****************************************************************************************************************************************
 * FUNCIONES PARA ARNAR STRINGS PARA LOS COMANDOS
 *****************************************************************************************************************************************/

/****************************************************************************************************************************************
  * FUNCIONES PARA FILTRAR ENTRENADORES
  *****************************************************************************************************************************************/
bool recorrer_entrenadores(void *entrenador, void *extra)
{
    if (entrenador) {
        lista_encolar((lista_t *)extra, (entrenador_t *)entrenador);
    }
    return false;
}
/****************************************************************************************************************************************
 * FUNCIONES PARA FILTRAR ENTRENADORES
 *****************************************************************************************************************************************/

/****************************************************************************************************************************************
  * FUNCIONES PARA REGLAS DE COMBATE
  *****************************************************************************************************************************************/
int enfrentamiento_clasico(void *pokemon, void *rival, void *extra)
{
    double stats_pokemon = 0.8 * pokemon_obtener_nivel((pokemon_t *)pokemon) + pokemon_obtener_fuerza((pokemon_t *)pokemon) + 2 * pokemon_obtener_velocidad((pokemon_t *)pokemon);
    double stats_rival = 0.8 * pokemon_obtener_nivel((pokemon_t *)rival) + pokemon_obtener_fuerza((pokemon_t *)rival) + 2 * pokemon_obtener_velocidad((pokemon_t *)rival);
    int resultado_batalla = (int)(stats_pokemon - stats_rival);
    *(int *)extra = (resultado_batalla >= 0) ? 1 : 2;
    return (resultado_batalla >= 0) ? 1 : 2;
}

int enfrentamiento_moderno(void *pokemon, void *rival, void *extra)
{
    pokemon_obtener_nivel((pokemon_t *)pokemon);
    double stats_pokemon = 0.5 * pokemon_obtener_nivel((pokemon_t *)pokemon) + 0.9 * pokemon_obtener_defensa((pokemon_t *)pokemon) + 3 * pokemon_obtener_inteligencia((pokemon_t *)pokemon);
    double stats_rival = 0.5 * pokemon_obtener_nivel((pokemon_t *)rival) + 0.9 * pokemon_obtener_defensa((pokemon_t *)rival) + 3 * pokemon_obtener_inteligencia((pokemon_t *)rival);
    int resultado_batalla = (int)(stats_pokemon - stats_rival);
    *(int *)extra = (resultado_batalla >= 0) ? 1 : 2;
    return (resultado_batalla >= 0) ? 1 : 2;
}
/****************************************************************************************************************************************
 * FUNCIONES PARA REGLAS DE COMBATE
 *****************************************************************************************************************************************/

bool enfrentar_entrenadores(salon_t *salon, entrenador_t *entrenador_1, entrenador_t *entrenador_2, char *regla, void *resultado)
{

    lista_iterador_t *iterador_equipo_1 = lista_iterador_crear(entrenador_obtener_equipo(entrenador_1));
    lista_iterador_t *iterador_equipo_2 = lista_iterador_crear(entrenador_obtener_equipo(entrenador_2));
    int resultado_enfrentamiento = 0;
    while (lista_iterador_tiene_siguiente(iterador_equipo_1) && lista_iterador_tiene_siguiente(iterador_equipo_2)) {
        menu_procesar_regla(salon->reglas, regla, lista_iterador_elemento_actual(iterador_equipo_1), lista_iterador_elemento_actual(iterador_equipo_2), &resultado_enfrentamiento);
        if (resultado_enfrentamiento == 1) {
            lista_iterador_avanzar(iterador_equipo_2);
        } else {
            lista_iterador_avanzar(iterador_equipo_1);
        }
        size_t longitud = strlen(*(char **)resultado) + 3; //longitud del "%s\n\0"
        char resultado_enfrentamiento_char[longitud];
        sprintf(resultado_enfrentamiento_char, "%s%i\n", *(char **)resultado, resultado_enfrentamiento);
        strcpy(*(char **)resultado, resultado_enfrentamiento_char);
    }
    lista_iterador_destruir(iterador_equipo_1);
    lista_iterador_destruir(iterador_equipo_2);
    return true;
}
/****************************************************************************************************************************************
 * COMANDOS
 *****************************************************************************************************************************************/
bool todos_los_entrenadores(entrenador_t *entrenador, void *extra)
{
    return true;
}

bool verificar_pokemones(void *pokemon, void *extra)
{
    //extra va a ser una lista_t* que contenga lista_t[0] = nombre_pokemon, y lista_t[1] = cantidad_pokemones
    if (pokemon) {
        char *nombre_pokemon = *(char **)lista_elemento_en_posicion(*(lista_t **)extra, 0);
        size_t *cantidad_pokemones = (size_t *)lista_elemento_en_posicion(*(lista_t **)extra, 1);

        if (strcasecmp(nombre_pokemon, pokemon_obtener_nombre((pokemon_t *)pokemon)) == 0) {
            (*cantidad_pokemones)++;
            return false;
        }
    }
    return true;
}

//extra va a ser una lista_t* que contenga lista_t[0] = nombre_pokemon, y lista_t[1] = cantidad_pokemones
bool entrenadores_por_pokemon(entrenador_t *entrenador, void *extra)
{
    lista_t *equipo = entrenador_obtener_equipo(entrenador);
    lista_con_cada_elemento(equipo, verificar_pokemones, extra);
    size_t *cantidad_pokemones = (size_t *)lista_elemento_en_posicion(*(lista_t **)extra, 1);
    return (*cantidad_pokemones > 0);
}

//extra va a ser una lista_t* que contenga lista_t[0] = cant_victorias (por ahora lo veo asi para mantener el mismo criterio para todas las llamadas)
bool entrenadores_por_victoria(entrenador_t *entrenador, void *extra)
{
    int cant_victorias = entrenador_obtener_victorias(entrenador);

    int *cant_victorias_requeridas = (int *)lista_elemento_en_posicion(*(lista_t **)extra, 0);
    return (cant_victorias >= *cant_victorias_requeridas);
}

bool salon_entrenadores(int argc, char *argv[], void *contexto)
{
    //tengo que recibir si o si todos estos parametros. Sino, falla.
    if (!argc || !argv || !contexto)
        return false;

    //contexto es una lista_t*, cuyo primer elemento es el salon
    salon_t *salon = lista_elemento_en_posicion(*(lista_t **)contexto, 0);

    //contexto es una lista_t*, cuyo segundo elemento es un char* en donde voy a concatenar los entrenadores.
    char *string_resultado = lista_elemento_en_posicion(*(lista_t **)contexto, 1);

    lista_t *extra = lista_crear(NULL);
    if (!extra)
        return false;

    lista_t *entrenadores_filtrados = NULL;
    //ahora que tengo los argumentos, puedo verificar que funcion voy a usar para filtrar.
    if (argc == 1) {
        entrenadores_filtrados = salon_filtrar_entrenadores(salon, todos_los_entrenadores, &extra);
        lista_con_cada_elemento(entrenadores_filtrados, imprimir_entrenadores_en_pantalla_lista, &string_resultado);
    } else if (argc == 2) {
        char **subcomando = split(argv[1], ',');
        if (!subcomando) {
            lista_destruir(extra);
            return false;
        }

        if (vtrlen(subcomando) != 2) {
            lista_destruir(extra);
            vtrfree(subcomando);
            return false;
        }

        if (strcmp(subcomando[0], "victorias") == 0) {
            //extra va a ser una lista_t* que contenga lista_t[0] = cant_victorias (por ahora lo veo asi para mantener el mismo criterio para todas las llamadas)
            int cant_victorias = atoi(subcomando[1]);
            lista_encolar(extra, &cant_victorias);
            entrenadores_filtrados = salon_filtrar_entrenadores(salon, entrenadores_por_victoria, &extra);
            lista_con_cada_elemento(entrenadores_filtrados, imprimir_entrenadores_en_pantalla_lista_solo_nombre, &string_resultado);
        } else if (strcmp(subcomando[0], "pokemon") == 0) {
            //extra va a ser una lista_t* que contenga lista_t[0] = nombre_pokemon, y lista_t[1] = cantidad_pokemones
            size_t cant_pokemones = 0;
            lista_encolar(extra, &subcomando[1]);
            lista_encolar(extra, &cant_pokemones);
            entrenadores_filtrados = salon_filtrar_entrenadores(salon, entrenadores_por_pokemon, &extra);
            lista_con_cada_elemento(entrenadores_filtrados, imprimir_entrenadores_en_pantalla_lista_solo_nombre, &string_resultado);
        }
        vtrfree(subcomando);
    }
    lista_destruir(extra);
    lista_destruir(entrenadores_filtrados);
    return false;
}

bool salon_equipo(int argc, char *argv[], void *contexto)
{
    if (!argc || !argv || !contexto)
        return false;

    //yo ya se que el contexto es una lista con argumentos.
    salon_t *salon = lista_elemento_en_posicion(*(lista_t **)contexto, 0);
    char *resultado = lista_elemento_en_posicion(*(lista_t **)contexto, 1);

    entrenador_t *auxiliar_para_buscar_entrenador = entrenador_crear((char *)argv[1], 0);
    entrenador_t *entrenador_buscado = arbol_buscar(salon->entrenadores, auxiliar_para_buscar_entrenador);
    if (!entrenador_buscado)
        return false;

    //probablemente esto deberia estar dentro del pokemon, para mantener algun tipo de separacion. No es una lista, es un equipo de pokemones, para el salón.
    lista_con_cada_elemento(entrenador_obtener_equipo(entrenador_buscado), imprimir_pokemones_en_pantalla, &resultado);
    entrenador_destruir(auxiliar_para_buscar_entrenador);

    return false;
}

bool salon_reglas(int argc, char *argv[], void *contexto)
{
    //yo ya se que el contexto es una lista con argumentos.
    salon_t *salon = lista_elemento_en_posicion(*(lista_t **)contexto, 0);
    char *resultado = lista_elemento_en_posicion(*(lista_t **)contexto, 1);

    menu_reglas_con_cada_elemento(salon->reglas, &resultado);

    return false;
}

bool salon_comparar(int argc, char *argv[], void *contexto)
{
    if (!argc || !argv || !contexto || argc != 2)
        return false;
    salon_t *salon = lista_elemento_en_posicion(*(lista_t **)contexto, 0);
    char *resultado = lista_elemento_en_posicion(*(lista_t **)contexto, 1);

    char **subcomando = split(argv[1], ',');
    if (!subcomando) {
        return false;
    }

    if (vtrlen(subcomando) != 3) {
        vtrfree(subcomando);
        return false;
    }

    entrenador_t *auxiliar_para_buscar_entrenador_1 = entrenador_crear((char *)subcomando[0], 0);
    entrenador_t *entrenador_buscado_1 = arbol_buscar(salon->entrenadores, auxiliar_para_buscar_entrenador_1);
    if (!entrenador_buscado_1) {
        entrenador_destruir(auxiliar_para_buscar_entrenador_1);
        vtrfree(subcomando);
        return false;
    }

    entrenador_t *auxiliar_para_buscar_entrenador_2 = entrenador_crear((char *)subcomando[1], 0);
    entrenador_t *entrenador_buscado_2 = arbol_buscar(salon->entrenadores, auxiliar_para_buscar_entrenador_2);
    if (!entrenador_buscado_2) {
        entrenador_destruir(auxiliar_para_buscar_entrenador_1);
        entrenador_destruir(auxiliar_para_buscar_entrenador_2);
        vtrfree(subcomando);
        return false;
    }

    bool guardado_exitoso = enfrentar_entrenadores(salon, entrenador_buscado_1, entrenador_buscado_2, (char *)subcomando[2], &resultado);

    if (!guardado_exitoso)
        return false;

    entrenador_destruir(auxiliar_para_buscar_entrenador_1);
    entrenador_destruir(auxiliar_para_buscar_entrenador_2);
    vtrfree(subcomando);
    return false;
}

//se agrega firma de funciones por ser necesarias para ejecutar el comando.
pokemon_t *parsear_pokemon(char **campos);
bool agregar_pokemon_o_destruir(entrenador_t *entrenador, pokemon_t *pokemon);

bool salon_agregar_pokemon(int argc, char *argv[], void *contexto)
{
    if (!argc || !argv || !contexto || argc != 2)
        return false;
    salon_t *salon = lista_elemento_en_posicion(*(lista_t **)contexto, 0);
    char *resultado = lista_elemento_en_posicion(*(lista_t **)contexto, 1);

    char **subcomando = split(argv[1], ',');
    if (!subcomando) {
        return false;
    }

    if (vtrlen(subcomando) != 7) {
        vtrfree(subcomando);
        return false;
    }

    entrenador_t *auxiliar_para_buscar_entrenador = entrenador_crear((char *)subcomando[0], 0);
    entrenador_t *entrenador_buscado = arbol_buscar(salon->entrenadores, auxiliar_para_buscar_entrenador);
    if (!entrenador_buscado) {
        vtrfree(subcomando);
        return false;
    }

    pokemon_t *pokemon_creado = parsear_pokemon(subcomando + 1);
    if (!pokemon_creado) {
        vtrfree(subcomando);
        return false;
    }

    //probablemente esto deberia estar dentro del pokemon, para mantener algun tipo de separacion. No es una lista, es un equipo de pokemones, para el salón.
    bool agregado_fallido = agregar_pokemon_o_destruir(entrenador_buscado, pokemon_creado);

    if (!agregado_fallido)
        strcpy(resultado, "OK\n");

    entrenador_destruir(auxiliar_para_buscar_entrenador);
    vtrfree(subcomando);
    return false;
}

bool obtener_posicion_pokemon(void *pokemon, void *extra)
{
    //extra va a ser una lista_t* que contenga lista_t[0] = nombre_pokemon, y lista_t[1] = posicion_pokemon
    if (pokemon) {
        char *nombre_pokemon = (char *)lista_elemento_en_posicion(*(lista_t **)extra, 0);
        int *posicion_pokemon = (int *)lista_elemento_en_posicion(*(lista_t **)extra, 1);

        if (strcasecmp(nombre_pokemon, pokemon_obtener_nombre((pokemon_t *)pokemon)) == 0) {
            return false;
        }
        (*posicion_pokemon)++;
    }
    return true;
}

//extra va a ser una lista_t* que contenga lista_t[0] = nombre_pokemon, y lista_t[1] = posicion_pokemon
void buscar_pokemon(entrenador_t *entrenador, void *extra)
{
    lista_t *equipo = entrenador_obtener_equipo(entrenador);

    size_t cant_elementos_recorridos = lista_con_cada_elemento(equipo, obtener_posicion_pokemon, extra);
    int *posicion_pokemon = (int *)lista_elemento_en_posicion(*(lista_t **)extra, 1);
    if (!cant_elementos_recorridos)
        *posicion_pokemon = -1;
}

bool salon_quitar_pokemon(int argc, char *argv[], void *contexto)
{
    if (!argc || !argv || !contexto || argc != 2)
        return false;
    salon_t *salon = lista_elemento_en_posicion(*(lista_t **)contexto, 0);
    char *resultado = lista_elemento_en_posicion(*(lista_t **)contexto, 1);

    char **subcomando = split(argv[1], ',');
    if (!subcomando) {
        return false;
    }

    if (vtrlen(subcomando) != 2) {
        vtrfree(subcomando);
        return false;
    }

    entrenador_t *auxiliar_para_buscar_entrenador = entrenador_crear((char *)subcomando[0], 0);
    entrenador_t *entrenador_buscado = arbol_buscar(salon->entrenadores, auxiliar_para_buscar_entrenador);
    if (!entrenador_buscado) {
        entrenador_destruir(auxiliar_para_buscar_entrenador);
        vtrfree(subcomando);
        return false;
    }

    if (lista_elementos(entrenador_obtener_equipo(entrenador_buscado)) <= 1) {
        vtrfree(subcomando);
        return false;
    }

    int pos_pokemon = 0;
    lista_t *lista_auxiliar = lista_crear(NULL);
    lista_encolar(lista_auxiliar, subcomando[1]);
    lista_encolar(lista_auxiliar, &pos_pokemon);
    buscar_pokemon(entrenador_buscado, &lista_auxiliar);

    int borrado_exitoso = lista_borrar_de_posicion(entrenador_obtener_equipo(entrenador_buscado), (size_t)pos_pokemon);

    if (borrado_exitoso != -1)
        strcpy(resultado, "OK\n");

    entrenador_destruir(auxiliar_para_buscar_entrenador);
    vtrfree(subcomando);
    lista_destruir(lista_auxiliar);
    return false;
}

bool salon_guardar(int argc, char *argv[], void *contexto)
{
    if (!argc || !argv || !contexto || argc != 2)
        return false;
    salon_t *salon = lista_elemento_en_posicion(*(lista_t **)contexto, 0);
    char *resultado = lista_elemento_en_posicion(*(lista_t **)contexto, 1);

    char path[1024] = "salones/";

    strcpy(path + strlen(path), argv[1]);

    int guardado_exitoso = salon_guardar_archivo(salon, path);

    if (guardado_exitoso != -1)
        strcpy(resultado, "OK\n");

    return false;
}
/****************************************************************************************************************************************
 * COMANDOS
 *****************************************************************************************************************************************/

/****************************************************************************************************************************************
  * CREACION MENU REGLAS
  *****************************************************************************************************************************************/
menu_reglas_t *salon_crear_menu_reglas()
{
    menu_reglas_t *menu_reglas = menu_reglas_crear();
    if (!menu_reglas)
        return NULL;

    menu_agregar_regla(menu_reglas, "CLASICO", "las reglas clásicas indican que un combate lo gana el Pokemon con el coeficiente de batalla mas alto en base al siguiente cálculo: 0.8 ∗ nivel + fuerza + 2 ∗ velocidad", enfrentamiento_clasico);
    menu_agregar_regla(menu_reglas, "MODERNO", "las reglas modernas indican que un combate lo gana el Pokemon con el coeficiente de batalla mas alto en base al siguiente cálculo: 0.5 ∗ nivel + 0.9 ∗ defensa + 3 ∗ inteligencia", enfrentamiento_moderno);

    return menu_reglas;
}
/****************************************************************************************************************************************
 * CREACION MENU REGLAS
 *****************************************************************************************************************************************/

/****************************************************************************************************************************************
  * CREACION MENU COMANDOS
  *****************************************************************************************************************************************/
menu_t *salon_crear_menu()
{
    menu_t *menu = menu_crear();
    if (!menu)
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
/****************************************************************************************************************************************
 * CREACION MENU COMANDOS
 *****************************************************************************************************************************************/

/****************************************************************************************************************************************
  * PRIMITIVAS SALON
  *****************************************************************************************************************************************/
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
    if (!salon->entrenadores) {
        free(salon);
        return NULL;
    }
    salon->menu_salon = salon_crear_menu();
    if (!salon->menu_salon) {
        arbol_destruir(salon->entrenadores);
        free(salon);
        return NULL;
    }

    salon->reglas = salon_crear_menu_reglas();
    if (!salon->reglas) {
        arbol_destruir(salon->entrenadores);
        menu_destruir(salon->menu_salon);
        free(salon);
        return NULL;
    }
    return salon;
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
    int resultado = arbol_insertar(salon->entrenadores, entrenador);
    if (resultado == SALON_ERROR) {
        entrenador_destruir(entrenador);
        return true;
    }
    return false;
}

bool agregar_pokemon_o_destruir(entrenador_t *entrenador, pokemon_t *pokemon)
{
    int resultado = lista_encolar(entrenador_obtener_equipo(entrenador), pokemon);
    if (resultado == SALON_ERROR) {
        pokemon_destruir(pokemon);
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
    entrenador_t *ult_entrenador = NULL;
    size_t *cant_lineas_leidas = 0;
    while (!error && (linea = fgets_alloc(archivo)) != NULL) {
        char **campos = split(linea, ';');

        pokemon_t *pokemon = parsear_pokemon(campos);
        entrenador_t *entrenador = parsear_entrenador(campos);

        if (pokemon != NULL) {
            error = agregar_pokemon_o_destruir(ult_entrenador, pokemon);
        } else if (entrenador != NULL) {
            error = agregar_entrenador_o_destruir(salon, entrenador);
            ult_entrenador = entrenador;
        } else {
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

    bool no_se_pudo_leer = cargar_archivo(salon, archivo);

    fclosen(archivo);

    abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, validar_entrenadores, &no_se_pudo_leer);

    if (no_se_pudo_leer) {
        salon_destruir(salon);
        return NULL;
    }

    return salon;
}

int salon_guardar_archivo(salon_t *salon, const char *nombre_archivo)
{
    if (!salon || !nombre_archivo) {
        return -1;
    }
    FILE *archivo_nuevo = fopen(nombre_archivo, "w");
    if (!archivo_nuevo) {
        return -1;
    }

    int cant_entrenadores_guardados = (int)abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, imprimir_entrenadores, &archivo_nuevo);

    fclosen(archivo_nuevo);
    return (cant_entrenadores_guardados) ? cant_entrenadores_guardados : -1;
}

salon_t *salon_agregar_entrenador(salon_t *salon, entrenador_t *entrenador)
{
    if (!salon || !entrenador)
        return NULL;

    int resultado = arbol_insertar(salon->entrenadores, entrenador);

    if (resultado == SALON_ERROR) {
        entrenador_destruir(entrenador);
        return NULL;
    }

    return salon;
}

lista_t *salon_filtrar_entrenadores(salon_t *salon, bool (*f)(entrenador_t *, void *), void *extra)
{
    if (!salon || !f)
        return NULL;

    lista_t *lista_aux = lista_crear(NULL);
    if (!lista_aux)
        return NULL;

    abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, recorrer_entrenadores, lista_aux);

    lista_iterador_t *iterador_lista = lista_iterador_crear(lista_aux);
    lista_t *lista_final = lista_crear(NULL);
    while (lista_iterador_tiene_siguiente(iterador_lista)) {
        if (f(lista_iterador_elemento_actual(iterador_lista), extra)) {
            lista_encolar(lista_final, lista_iterador_elemento_actual(iterador_lista));
        }
        lista_iterador_avanzar(iterador_lista);
    }
    lista_iterador_destruir(iterador_lista);
    lista_destruir(lista_aux);
    return lista_final;
}

char *salon_ejecutar_comando(salon_t *salon, const char *comando)
{
    if (!salon || !comando)
        return NULL;

    char *resultado = calloc(1, sizeof(char) * 2048);
    if (!resultado)
        return NULL;

    //creo una lista de argumentos, que va a servir para pasar el salon y el char a donde voy a guardar el texto
    lista_t *argumentos = lista_crear(NULL);
    lista_encolar(argumentos, salon);
    lista_encolar(argumentos, resultado);

    //menu_procesar_opcion va a recibir una lista de argumentos, que le va a pasar al comando. El comando sabe qué tiene que hacer.
    menu_procesar_opcion(salon->menu_salon, comando, &argumentos);
    lista_destruir(argumentos);

    //si al salir de la ejecucion, no se cargó un texto, retorno NULL y libero el char
    if (strlen(resultado) == 0) {
        free(resultado);
        return NULL;
    }
    return resultado;
}

void salon_destruir(salon_t *salon)
{
    if (salon) {
        arbol_destruir(salon->entrenadores);
        menu_destruir(salon->menu_salon);
        menu_reglas_destruir(salon->reglas);
        free(salon);
    }
}
/****************************************************************************************************************************************
 * PRIMITIVAS SALON
 *****************************************************************************************************************************************/