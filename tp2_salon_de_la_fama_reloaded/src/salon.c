#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "utils.h"
#include "entrenador.h"
#include "salon.h"
#include "abb.h"
#include "menu.h"
#include "reglas.h"

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

/****************************************************************************************************************************************
 * FUNCIONES PARA IMPRIMIR EN ARCHIVO (SALON GUARDAR ARCHIVO)
 *****************************************************************************************************************************************/
//aca deberia ver si no falla
bool imprimir_pokemones(void *pokemon, void *archivo)
{
    if (pokemon)
    {
        printf("estoy guardando en archivo al pokemon: %s\n", pokemon_obtener_nombre((pokemon_t *)pokemon));
        fprintf(*(FILE **)archivo, FORMATO_ESCRITURA_POKEMON, pokemon_obtener_nombre((pokemon_t *)pokemon), pokemon_obtener_nivel((pokemon_t *)pokemon), pokemon_obtener_defensa((pokemon_t *)pokemon), pokemon_obtener_fuerza((pokemon_t *)pokemon), pokemon_obtener_inteligencia((pokemon_t *)pokemon), pokemon_obtener_velocidad((pokemon_t *)pokemon));
        return true;
    }
    printf("hubo error al guardar en archivo al pokemon\n");
    return false;
}

//aca deberia ver si no falla
bool imprimir_entrenadores(void *entrenador, void *archivo)
{
    if (entrenador)
    {
        printf("estoy guardando en archivo al entrenador: %s\n", entrenador_obtener_nombre((entrenador_t *)entrenador));
        fprintf(*(FILE **)archivo, FORMATO_ESCRITURA_ENTRENADOR, entrenador_obtener_nombre((entrenador_t *)entrenador), entrenador_obtener_victorias((entrenador_t *)entrenador));
        lista_con_cada_elemento((lista_t *)entrenador_obtener_equipo((entrenador_t *)entrenador), imprimir_pokemones, archivo);
        return false;
    }
    printf("hubo error al guardar en archivo al entrenador\n");
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
    if (pokemon)
    {
        //printf(FORMATO_ESCRITURA_ARCH_POKEMON, pokemon_obtener_nombre((pokemon_t*)pokemon), pokemon_obtener_nivel((pokemon_t*)pokemon),pokemon_obtener_defensa((pokemon_t*)pokemon), pokemon_obtener_fuerza((pokemon_t*)pokemon), pokemon_obtener_inteligencia((pokemon_t*)pokemon), pokemon_obtener_velocidad((pokemon_t*)pokemon));
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
        printf("la longitud obtenida del pokemon es: %zu\n", longitud);
        char texto_auxiliar[longitud];
        sprintf(texto_auxiliar, FORMATO_ESCRITURA_ARCH_POKEMON, *(char **)buffer, pokemon_obtener_nombre((pokemon_t *)pokemon), pokemon_obtener_nivel((pokemon_t *)pokemon), pokemon_obtener_defensa((pokemon_t *)pokemon), pokemon_obtener_fuerza((pokemon_t *)pokemon), pokemon_obtener_inteligencia((pokemon_t *)pokemon), pokemon_obtener_velocidad((pokemon_t *)pokemon));
        printf("el texto auxiliar es:\n%s\nfin del texto auxiliar.\n\n", texto_auxiliar);
        //*(char**)buffer = realloc(*(char**)buffer, longitud);
        strcpy(*(char **)buffer, texto_auxiliar);
        printf("el buffer actualizado es:\n%s\n\n", *(char **)buffer);
    }
    return true;
}

bool imprimir_entrenadores_en_pantalla(void *entrenador, void *buffer)
{
    if (entrenador)
    {
        //paso a char* el nro de victorias
        char victorias[10];
        sprintf(victorias, "%i", entrenador_obtener_victorias((entrenador_t *)entrenador));
        printf("strlen del buffer por ahora es: %zu\n", strlen(*(char **)buffer));
        size_t longitud = strlen(*(char **)buffer) + strlen(entrenador_obtener_nombre((entrenador_t *)entrenador)) + strlen(victorias) + 2; //longitud del "%s;%i\n\0"
        char texto_auxiliar[longitud];
        sprintf(texto_auxiliar, FORMATO_ESCRITURA_ARCH_ENTRENADOR, *(char **)buffer, entrenador_obtener_nombre((entrenador_t *)entrenador), entrenador_obtener_victorias((entrenador_t *)entrenador));
        printf("el texto auxiliar es:\n%s\nfin del texto auxiliar.\n\n", texto_auxiliar);
        //*(char**)buffer = realloc(*(char**)buffer, longitud);
        strcpy(*(char **)buffer, texto_auxiliar);
        printf("el buffer actualizado es:\n%s\n\n", *(char **)buffer);
        //lista_con_cada_elemento((lista_t*)entrenador_obtener_equipo((entrenador_t*)entrenador), imprimir_pokemones_en_pantalla, buffer);
    }
    return false;
}


//el problema es que para lista necesito que retorne true, y para ABB, false. Sino, serían exactamente iguales!!!! (CAMBIAR)
bool imprimir_entrenadores_en_pantalla_lista(void *entrenador, void *buffer)
{
    if (entrenador)
    {
        //paso a char* el nro de victorias
        char victorias[10];
        sprintf(victorias, "%i", entrenador_obtener_victorias((entrenador_t *)entrenador));
        printf("strlen del buffer por ahora es: %zu\n", strlen(*(char **)buffer));
        size_t longitud = strlen(*(char **)buffer) + strlen(entrenador_obtener_nombre((entrenador_t *)entrenador)) + strlen(victorias) + 2; //longitud del "%s;%i\n\0"
        char texto_auxiliar[longitud];
        sprintf(texto_auxiliar, FORMATO_ESCRITURA_ARCH_ENTRENADOR, *(char **)buffer, entrenador_obtener_nombre((entrenador_t *)entrenador), entrenador_obtener_victorias((entrenador_t *)entrenador));
        printf("el texto auxiliar es:\n%s\nfin del texto auxiliar.\n\n", texto_auxiliar);
        //*(char**)buffer = realloc(*(char**)buffer, longitud);
        strcpy(*(char **)buffer, texto_auxiliar);
        printf("el buffer actualizado es:\n%s\n\n", *(char **)buffer);
        //lista_con_cada_elemento((lista_t*)entrenador_obtener_equipo((entrenador_t*)entrenador), imprimir_pokemones_en_pantalla, buffer);
    }
    return true;
}


bool imprimir_entrenadores_en_pantalla_lista_solo_nombre(void *entrenador, void *buffer)
{
    if (entrenador)
    {
        printf("strlen del buffer por ahora es: %zu\n", strlen(*(char **)buffer));
        size_t longitud = strlen(*(char **)buffer) + strlen(entrenador_obtener_nombre((entrenador_t *)entrenador)) + 2; //longitud del "%s\n\0"
        char texto_auxiliar[longitud];
        sprintf(texto_auxiliar, FORMATO_ESCRITURA_ARCH_ENTRENADOR_SOLO_NOMBRE, *(char **)buffer, entrenador_obtener_nombre((entrenador_t *)entrenador));
        printf("el texto auxiliar es:\n%s\nfin del texto auxiliar.\n\n", texto_auxiliar);
        //*(char**)buffer = realloc(*(char**)buffer, longitud);
        strcpy(*(char **)buffer, texto_auxiliar);
        printf("el buffer actualizado es:\n%s\n\n", *(char **)buffer);
    }
    return true;
}



/****************************************************************************************************************************************
 * FUNCIONES PARA ARNAR STRINGS PARA LOS COMANDOS
 *****************************************************************************************************************************************/

/****************************************************************************************************************************************
 * FUNCIONES PARA REGLAS DE COMBATE
 *****************************************************************************************************************************************/

/****************************************************************************************************************************************
 * FUNCIONES PARA REGLAS DE COMBATE
 *****************************************************************************************************************************************/

/****************************************************************************************************************************************
 * FUNCIONES PARA FILTRAR ENTRENADORES
 *****************************************************************************************************************************************/
bool recorrer_entrenadores(void *entrenador, void *extra)
{
    if (entrenador)
    {
        printf("el entrenador es: %s\n", entrenador_obtener_nombre(entrenador));

        lista_encolar((lista_t *)extra, (entrenador_t *)entrenador);
    }
    return false;
}
/****************************************************************************************************************************************
 * FUNCIONES PARA FILTRAR ENTRENADORES
 *****************************************************************************************************************************************/

/****************************************************************************************************************************************
 * COMANDOS
 *****************************************************************************************************************************************/
bool _salon_entrenadores(int argc, char *argv[], void *contexto)
{
    if (!argc || !argv || !contexto)
        return false;
    //yo ya se que el contexto es una lista con argumentos.
    salon_t *salon = lista_elemento_en_posicion(*(lista_t **)contexto, 0);
    char *resultado = lista_elemento_en_posicion(*(lista_t **)contexto, 1);

    if (argc == 1)
    { //solo se ejecuto el comando, sin parámetros.
        //ahora puedo recorrer todos los entrenadores y concatenar en el char resultado sus nombres y victorias.
        //misma nota que con los pokemons. Tal vez deberia hacer una funcion que recorra los entrenadores desde el archivo entrenador.c
        abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, imprimir_entrenadores_en_pantalla, &resultado);
    }
    else if (argc == 2)
    {
        char **subcomando = split(argv[1], ',');
        if (!subcomando)
            return false;

        if (vtrlen(subcomando) != 2)
        {
            printf("fallo al hacer el split del subcomando porque deberia tener maximo dos argumentos\n");
            vtrfree(subcomando);
            return false;
        }

        vtrfree(subcomando);
    }
    else
    { //no pueden haber más de dos argumentos en esta instancia. Esto es un error y retorno un array NULL.
        return false;
    }

    printf("el resultado, al finalizar la ejecucion del comando, es de:\n%s\n\n", resultado);
    return false;
}

bool todos_los_entrenadores(entrenador_t *entrenador, void *extra)
{
    return true;
}

bool verificar_pokemones(void *pokemon, void *extra)
{
    //extra va a ser una lista_t* que contenga lista_t[0] = nombre_pokemon, y lista_t[1] = cantidad_pokemones
    if (pokemon)
    {
        char *nombre_pokemon = *(char**)lista_elemento_en_posicion(*(lista_t **)extra, 0);
        size_t *cantidad_pokemones = (size_t *)lista_elemento_en_posicion(*(lista_t **)extra, 1);

        if (strcasecmp(nombre_pokemon, pokemon_obtener_nombre((pokemon_t *)pokemon)) == 0)
        {
            (*cantidad_pokemones)++;
            return false;
        }
    }
    return true;
}

bool entrenadores_por_pokemon(entrenador_t *entrenador, void *extra)
{
    //extra va a ser una lista_t* que contenga lista_t[0] = nombre_pokemon, y lista_t[1] = cantidad_pokemones
    lista_t *equipo = entrenador_obtener_equipo(entrenador);
    lista_con_cada_elemento(equipo, verificar_pokemones, extra);
    size_t *cantidad_pokemones = (size_t *)lista_elemento_en_posicion(*(lista_t **)extra, 1);
    return *cantidad_pokemones > 0;
}

bool entrenadores_por_victoria(entrenador_t *entrenador, void *extra)
{
    //extra va a ser una lista_t* que contenga lista_t[0] = cant_victorias (por ahora lo veo asi para mantener el mismo criterio para todas las llamadas)
    int cant_victorias = entrenador_obtener_victorias(entrenador);

    int *cant_victorias_requeridas = (int *)lista_elemento_en_posicion(*(lista_t **)extra, 0);
    return cant_victorias >= *cant_victorias_requeridas;
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
    if (argc == 1)
    {
        entrenadores_filtrados = salon_filtrar_entrenadores(salon, todos_los_entrenadores, &extra);
        lista_con_cada_elemento(entrenadores_filtrados, imprimir_entrenadores_en_pantalla_lista, &string_resultado);
    }
    else if (argc == 2)
    {
        char **subcomando = split(argv[1], ',');
        if (!subcomando)
        {
            lista_destruir(extra);
            return false;
        }

        if (vtrlen(subcomando) != 2)
        {
            printf("fallo al hacer el split del subcomando porque deberia tener maximo dos argumentos\n");
            lista_destruir(extra);
            vtrfree(subcomando);
            return false;
        }

        if (strcmp(subcomando[0], "victorias") == 0)
        {
            //extra va a ser una lista_t* que contenga lista_t[0] = cant_victorias (por ahora lo veo asi para mantener el mismo criterio para todas las llamadas)
            int cant_victorias = atoi(subcomando[1]);
            lista_encolar(extra, &cant_victorias);
            entrenadores_filtrados = salon_filtrar_entrenadores(salon, entrenadores_por_victoria, &extra);
            lista_con_cada_elemento(entrenadores_filtrados, imprimir_entrenadores_en_pantalla_lista_solo_nombre, &string_resultado);
        }
        else if (strcmp(subcomando[0], "pokemon") == 0)
        {
            //extra va a ser una lista_t* que contenga lista_t[0] = nombre_pokemon, y lista_t[1] = cantidad_pokemones
            size_t cant_pokemones = 0;


            printf("el pokemon que busco es: %s\n", subcomando[1]);
            lista_encolar(extra, &subcomando[1]);
            lista_encolar(extra, &cant_pokemones);
            entrenadores_filtrados = salon_filtrar_entrenadores(salon, entrenadores_por_pokemon, &extra);
            lista_con_cada_elemento(entrenadores_filtrados, imprimir_entrenadores_en_pantalla_lista_solo_nombre, &string_resultado);
        }
        else
        {
            printf("falla porque no se reconoce el comando\n");
            lista_destruir(extra);
            vtrfree(subcomando);
            return false;
        }
        vtrfree(subcomando);
        lista_destruir(extra);
    }
    else
    {

        lista_destruir(extra);
        return false;
    }

    return false;
}

bool salon_equipo(int argc, char *argv[], void *contexto)
{
    if (!argc || !argv || !contexto)
        return false;

    //yo ya se que el contexto es una lista con argumentos.
    salon_t *salon = lista_elemento_en_posicion(*(lista_t **)contexto, 0);
    char *resultado = lista_elemento_en_posicion(*(lista_t **)contexto, 1);

    printf("el entrenador que estoy buscando es: %s\n", (char *)argv[1]);
    entrenador_t *auxiliar_para_buscar_entrenador = entrenador_crear((char *)argv[1], 0);
    entrenador_t *entrenador_buscado = arbol_buscar(salon->entrenadores, auxiliar_para_buscar_entrenador);
    if (!entrenador_buscado)
        return false;
    printf("los datos del entrenador encontrado son: %s\n", entrenador_obtener_nombre(entrenador_buscado));

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
    salon_t *salon = contexto;
    //ESTO ESTA MAL. SOLO ES PARA MOSTRAR QUE SE EJECUTA ALGO CUANDO INVOCO AL COMANDO.
    printf("salon: %s\n", entrenador_obtener_nombre(*(entrenador_t **)salon->entrenadores->nodo_raiz->elemento));
    return false;
}

bool salon_agregar_pokemon(int argc, char *argv[], void *contexto)
{
    salon_t *salon = contexto;
    //ESTO ESTA MAL. SOLO ES PARA MOSTRAR QUE SE EJECUTA ALGO CUANDO INVOCO AL COMANDO.
    printf("salon: %s\n", entrenador_obtener_nombre(*(entrenador_t **)salon->entrenadores->nodo_raiz->elemento));
    return false;
}

bool salon_quitar_pokemon(int argc, char *argv[], void *contexto)
{
    salon_t *salon = contexto;
    //ESTO ESTA MAL. SOLO ES PARA MOSTRAR QUE SE EJECUTA ALGO CUANDO INVOCO AL COMANDO.
    printf("salon: %s\n", entrenador_obtener_nombre(*(entrenador_t **)salon->entrenadores->nodo_raiz->elemento));
    return false;
}

bool salon_guardar(int argc, char *argv[], void *contexto)
{
    salon_t *salon = contexto;
    //ESTO ESTA MAL. SOLO ES PARA MOSTRAR QUE SE EJECUTA ALGO CUANDO INVOCO AL COMANDO.
    printf("salon: %s\n", entrenador_obtener_nombre(*(entrenador_t **)salon->entrenadores->nodo_raiz->elemento));
    return false;
}
/****************************************************************************************************************************************
 * COMANDOS
 *****************************************************************************************************************************************/

/****************************************************************************************************************************************
 * CREACION MENU REGLAS
 *****************************************************************************************************************************************/
int enfrentamiento_clasico(void *pokemon, void *rival, void *extra)
{
    pokemon_obtener_nivel((pokemon_t *)pokemon);
    double stats_pokemon = 0.8 * pokemon_obtener_nivel((pokemon_t *)pokemon) + pokemon_obtener_fuerza((pokemon_t *)pokemon) + 2 * pokemon_obtener_velocidad((pokemon_t *)pokemon);
    double stats_rival = 0.8 * pokemon_obtener_nivel((pokemon_t *)rival) + pokemon_obtener_fuerza((pokemon_t *)rival) + 2 * pokemon_obtener_velocidad((pokemon_t *)rival);
    int resultado_batalla = (int)(stats_pokemon - stats_rival);
    return (resultado_batalla == 0) ? 1 : resultado_batalla;
}

int enfrentamiento_moderno(void *pokemon, void *rival, void *extra)
{
    pokemon_obtener_nivel((pokemon_t *)pokemon);
    double stats_pokemon = 0.5 * pokemon_obtener_nivel((pokemon_t *)pokemon) + 0.9 * pokemon_obtener_defensa((pokemon_t *)pokemon) + 3 * pokemon_obtener_inteligencia((pokemon_t *)pokemon);
    double stats_rival = 0.5 * pokemon_obtener_nivel((pokemon_t *)rival) + 0.9 * pokemon_obtener_defensa((pokemon_t *)rival) + 3 * pokemon_obtener_inteligencia((pokemon_t *)rival);
    int resultado_batalla = (int)(stats_pokemon - stats_rival);
    return (resultado_batalla == 0) ? 1 : resultado_batalla;
}

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
    if (!salon->entrenadores)
    {
        free(salon);
        return NULL;
    }
    salon->menu_salon = salon_crear_menu();
    if (!salon->menu_salon)
    {
        arbol_destruir(salon->entrenadores);
        free(salon);
        return NULL;
    }

    salon->reglas = salon_crear_menu_reglas();
    if (!salon->reglas)
    {
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
    if (resultado == SALON_ERROR)
    {
        entrenador_destruir(entrenador);
        return true;
    }
    return false;
}

bool agregar_pokemon_o_destruir(entrenador_t *entrenador, pokemon_t *pokemon)
{
    int resultado = lista_encolar(entrenador_obtener_equipo(entrenador), pokemon);
    if (resultado == SALON_ERROR)
    {
        pokemon_destruir(pokemon);
        return true;
    }
    return false;
}

bool cargar_archivo(salon_t *salon, FILE *archivo)
{
    if (!salon || !archivo)
        return false;

    char *linea = NULL;
    bool error = false;
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
            ult_entrenador = entrenador;
        }
        else
        {
            error = true;
        }

        vtrfree(campos);
        free(linea);
    }

    if (error)
        printf("dentro de cargar_archivo error es true\n");
    return error;
}

salon_t *salon_leer_archivo(const char *nombre_archivo)
{
    if (!nombre_archivo)
        return NULL;

    FILE *archivo = fopen(nombre_archivo, "r");
    salon_t *salon = salon_crear();

    bool no_se_pudo_leer = cargar_archivo(salon, archivo);
    if (!no_se_pudo_leer)
        printf("se pudo leer el archivo\n");

    fclosen(archivo);

    if (no_se_pudo_leer)
    {
        printf("hubo un error en la lectura y se elimina el salon\n");
        salon_destruir(salon);
        return NULL;
    }

    return salon;
}

int salon_guardar_archivo(salon_t *salon, const char *nombre_archivo)
{
    if (!salon)
    {
        printf("error en salon porque era NULL\n");
        return -1;
    }
    FILE *archivo_nuevo = fopen(nombre_archivo, "w");
    if (!archivo_nuevo)
    {
        printf("error en creacion archivo nuevo\n");
        return -1;
    }

    printf("estoy por procesar a los entrenadores\n");
    int cant_entrenadores_guardados = (int)abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, imprimir_entrenadores, &archivo_nuevo);
    printf("terminé de procesar a los entrenadores\n");

    fclosen(archivo_nuevo);
    return (cant_entrenadores_guardados) ? cant_entrenadores_guardados : -1;
}

salon_t *salon_agregar_entrenador(salon_t *salon, entrenador_t *entrenador)
{
    if (!salon || !entrenador)
        return NULL;

    int resultado = arbol_insertar(salon->entrenadores, entrenador);

    if (resultado == SALON_ERROR)
    {
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

    int cant = (int)abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, recorrer_entrenadores, lista_aux);
    printf("recorri %i elementos\n", cant);

    lista_iterador_t *iterador_lista = lista_iterador_crear(lista_aux);
    lista_t *lista_final = lista_crear(NULL);
    while (lista_iterador_tiene_siguiente(iterador_lista))
    {
        if (f(lista_iterador_elemento_actual(iterador_lista), extra))
        {
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

    printf("se ejecutó el comando: %s\n", comando);

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
    if (strlen(resultado) == 0)
    {
        free(resultado);
        return NULL;
    }
    return resultado;
}

void salon_destruir(salon_t *salon)
{
    if (salon)
    {
        arbol_destruir(salon->entrenadores);
        menu_destruir(salon->menu_salon);
        menu_reglas_destruir(salon->reglas);
        free(salon);
    }
}
/****************************************************************************************************************************************
 * PRIMITIVAS SALON
 *****************************************************************************************************************************************/