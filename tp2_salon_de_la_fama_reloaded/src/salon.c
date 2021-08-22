#include "salon.h"
#include <stdlib.h>
#include <stdio.h>
#include "abb.h"
#include "menu.h"
#include "reglas.h"
#include "gimnasios.h"
#include "utils.h"
#include <string.h>
#include <strings.h>
#include <time.h>

#define ES_POKEMON (vtrlen(campos) == 6)
#define ES_ENTRENADOR (vtrlen(campos) == 2)
#define GUARDADO_EXITOSO (cant_entrenadores_guardados) ? cant_entrenadores_guardados : SALON_ERROR

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

void concatenar_resultado_ok(char **resultado, char *separador)
{
    char char_resultado[10];
    strcpy(char_resultado, STR_OK);

    size_t tam_resultado = strlen(char_resultado);

    void **vector_resultado = NULL;
    vector_resultado = vtradd(vector_resultado, char_resultado);
    concatenar_str(vector_resultado, tam_resultado, resultado, separador, !agregar_salto_de_linea);
    free(vector_resultado);
}

void concatenar_pokemon(pokemon_t *pokemon, char **resultado, char *separador)
{
    void **vector_pkm = NULL;

    char *char_nombre = pokemon_obtener_nombre(pokemon);
    size_t tam_nom = strlen(char_nombre);
    vector_pkm = vtradd(vector_pkm, char_nombre);

    char char_niv[10];
    sprintf(char_niv, "%i", pokemon_obtener_nivel(pokemon));
    size_t tam_niv = strlen(char_niv);
    vector_pkm = vtradd(vector_pkm, char_niv);

    char char_def[10];
    sprintf(char_def, "%i", pokemon_obtener_defensa(pokemon));
    size_t tam_def = strlen(char_def);
    vector_pkm = vtradd(vector_pkm, char_def);

    char char_fue[10];
    sprintf(char_fue, "%i", pokemon_obtener_fuerza(pokemon));
    size_t tam_fue = strlen(char_fue);
    vector_pkm = vtradd(vector_pkm, char_fue);

    char char_int[10];
    sprintf(char_int, "%i", pokemon_obtener_inteligencia(pokemon));
    size_t tam_int = strlen(char_int);
    vector_pkm = vtradd(vector_pkm, char_int);

    char char_vel[10];
    sprintf(char_vel, "%i", pokemon_obtener_velocidad(pokemon));
    size_t tam_vel = strlen(char_vel);
    vector_pkm = vtradd(vector_pkm, char_vel);

    size_t tam_buffer = tam_nom + tam_niv + tam_fue + tam_int + tam_vel + tam_def + 2;

    concatenar_str(vector_pkm, tam_buffer, resultado, separador, agregar_salto_de_linea);

    free(vector_pkm);
}

void concatenar_entrenador(entrenador_t *entrenador, char **resultado, char *separador, bool mostrar_victorias)
{
    void **vector_entrenador = NULL;

    char *char_nombre = entrenador_obtener_nombre(entrenador);
    size_t tam_nom = strlen(char_nombre);
    vector_entrenador = vtradd(vector_entrenador, char_nombre);

    size_t tam_victorias = 0;
    if (mostrar_victorias)
    {
        char char_victorias[10];
        sprintf(char_victorias, "%i", entrenador_obtener_victorias(entrenador));
        tam_victorias = strlen(char_victorias);
        vector_entrenador = vtradd(vector_entrenador, char_victorias);
    }

    size_t tam_buffer = tam_nom + tam_victorias + 2;

    concatenar_str(vector_entrenador, tam_buffer, resultado, separador, agregar_salto_de_linea);

    free(vector_entrenador);
}

int enfrentamiento_clasico(void *pokemon, void *rival, void *extra)
{
    int *resultado = lista_elemento_en_posicion((lista_t *)extra, 1);
    double stats_pokemon = 0.8 * pokemon_obtener_nivel((pokemon_t *)pokemon) + pokemon_obtener_fuerza((pokemon_t *)pokemon) + 2 * pokemon_obtener_velocidad((pokemon_t *)pokemon);
    double stats_rival = 0.8 * pokemon_obtener_nivel((pokemon_t *)rival) + pokemon_obtener_fuerza((pokemon_t *)rival) + 2 * pokemon_obtener_velocidad((pokemon_t *)rival);
    int resultado_batalla = (int)(stats_pokemon - stats_rival);
    *(int *)resultado = (resultado_batalla >= 0) ? 1 : 2;
    return (resultado_batalla >= 0) ? 1 : 2;
}

int enfrentamiento_moderno(void *pokemon, void *rival, void *extra)
{
    int *resultado = lista_elemento_en_posicion((lista_t *)extra, 1);

    pokemon_obtener_nivel((pokemon_t *)pokemon);
    double stats_pokemon = 0.5 * pokemon_obtener_nivel((pokemon_t *)pokemon) + 0.9 * pokemon_obtener_defensa((pokemon_t *)pokemon) + 3 * pokemon_obtener_inteligencia((pokemon_t *)pokemon);
    double stats_rival = 0.5 * pokemon_obtener_nivel((pokemon_t *)rival) + 0.9 * pokemon_obtener_defensa((pokemon_t *)rival) + 3 * pokemon_obtener_inteligencia((pokemon_t *)rival);
    int resultado_batalla = (int)(stats_pokemon - stats_rival);
    *(int *)resultado = (resultado_batalla >= 0) ? 1 : 2;
    return (resultado_batalla >= 0) ? 1 : 2;
}

int enfrentamiento_con_suerte(void *pokemon, void *rival, void *extra)
{
    int *resultado = lista_elemento_en_posicion((lista_t *)extra, 1);

    srand((unsigned int)time(NULL));
    pokemon_obtener_nivel((pokemon_t *)pokemon);
    double stats_pokemon = 0.5 * pokemon_obtener_nivel((pokemon_t *)pokemon) + 0.9 * pokemon_obtener_defensa((pokemon_t *)pokemon) + 3 * pokemon_obtener_inteligencia((pokemon_t *)pokemon);
    double stats_rival = 0.5 * pokemon_obtener_nivel((pokemon_t *)rival) + 0.9 * pokemon_obtener_defensa((pokemon_t *)rival) + 3 * pokemon_obtener_inteligencia((pokemon_t *)rival);
    double suma_ataque_pokemon = 0;
    double suma_ataque_rival = 0;
    for (size_t i = 0; i < 10; i++)
    {
        int suerte_pokemon = rand() % 10;
        int suerte_rival = rand() % 10;
        suma_ataque_pokemon += stats_pokemon * suerte_pokemon;
        suma_ataque_rival += stats_rival * suerte_rival;
    }

    int resultado_batalla = (int)(suma_ataque_pokemon - suma_ataque_rival);

    *resultado = (resultado_batalla >= 0) ? 1 : 2;
    return (resultado_batalla >= 0) ? 1 : 2;
}

int enfrentamiento_gimnasio(void *pokemon, void *rival, void *extra)
{
    salon_t *salon = lista_elemento_en_posicion((lista_t *)extra, 0);
    int *resultado = lista_elemento_en_posicion((lista_t *)extra, 1);

    int *gimnasio_pokemon = lista_elemento_en_posicion((lista_t *)extra, 2);
    if (!gimnasio_pokemon)
        *gimnasio_pokemon = rand() % 2;

    int *gimnasio_rival = lista_elemento_en_posicion((lista_t *)extra, 3);
    if (!gimnasio_rival)
        *gimnasio_rival = rand() % 2;

    gimnasio_t **gimnasios = salon->gimnasios;

    double stats_pokemon = 0.8 * pokemon_obtener_nivel((pokemon_t *)pokemon) + pokemon_obtener_fuerza((pokemon_t *)pokemon) + 2 * pokemon_obtener_velocidad((pokemon_t *)pokemon);

    stats_pokemon = stats_pokemon * gimnasio_obtener_efectividad_rival(gimnasios[*gimnasio_pokemon], gimnasio_obtener_tipo(gimnasios[*gimnasio_rival]));

    double stats_rival = 0.8 * pokemon_obtener_nivel((pokemon_t *)rival) + pokemon_obtener_fuerza((pokemon_t *)rival) + 2 * pokemon_obtener_velocidad((pokemon_t *)rival);

    stats_rival = stats_rival * gimnasio_obtener_efectividad_rival(gimnasios[*gimnasio_rival], gimnasio_obtener_tipo(gimnasios[*gimnasio_pokemon]));

    int resultado_batalla = (int)(stats_pokemon - stats_rival);
    *(int *)resultado = (resultado_batalla >= 0) ? 1 : 2;
    return (resultado_batalla >= 0) ? 1 : 2;
}

int enfrentamiento_enfrentaditto(void *pokemon, void *rival, void *extra)
{
    salon_t *salon = lista_elemento_en_posicion((lista_t *)extra, 0);
    int *resultado = lista_elemento_en_posicion((lista_t *)extra, 1);

    int *gimnasio_pokemon = lista_elemento_en_posicion((lista_t *)extra, 2);
    *gimnasio_pokemon = rand() % 2;

    int *gimnasio_rival = lista_elemento_en_posicion((lista_t *)extra, 3);
    *gimnasio_rival = rand() % 2;

    gimnasio_t **gimnasios = salon->gimnasios;

    double stats_pokemon = 0.8 * pokemon_obtener_nivel((pokemon_t *)pokemon) + pokemon_obtener_fuerza((pokemon_t *)pokemon) + 2 * pokemon_obtener_velocidad((pokemon_t *)pokemon);

    stats_pokemon = stats_pokemon * gimnasio_obtener_efectividad_rival(gimnasios[*gimnasio_pokemon], gimnasio_obtener_tipo(gimnasios[*gimnasio_rival]));

    double stats_rival = 0.8 * pokemon_obtener_nivel((pokemon_t *)rival) + pokemon_obtener_fuerza((pokemon_t *)rival) + 2 * pokemon_obtener_velocidad((pokemon_t *)rival);

    stats_rival = stats_rival * gimnasio_obtener_efectividad_rival(gimnasios[*gimnasio_rival], gimnasio_obtener_tipo(gimnasios[*gimnasio_pokemon]));

    int resultado_batalla = (int)(stats_pokemon - stats_rival);
    *(int *)resultado = (resultado_batalla >= 0) ? 1 : 2;
    return (resultado_batalla >= 0) ? 1 : 2;
}

menu_reglas_t *salon_crear_menu_reglas()
{
    menu_reglas_t *menu_reglas = menu_reglas_crear();
    if (!menu_reglas)
        return NULL;

    menu_agregar_regla(menu_reglas, "CLASICO", "las reglas clásicas indican que un combate lo gana el Pokemon con el coeficiente de batalla mas alto en base al siguiente cálculo: 0.8 * nivel + fuerza + 2 * velocidad", enfrentamiento_clasico);
    menu_agregar_regla(menu_reglas, "MODERNO", "las reglas modernas indican que un combate lo gana el Pokemon con el coeficiente de batalla mas alto en base al siguiente cálculo: 0.5 * nivel + 0.9 * defensa + 3 * inteligencia", enfrentamiento_moderno);
    menu_agregar_regla(menu_reglas, "DIRTY_HARRY", "Los pokemones atacan 10 veces. La fuerza del ataque se calcula con el coeficiente de la batalla moderna pero afectado por un valor aleatorio de SUERTE (de 1 a 10)", enfrentamiento_con_suerte);
    menu_agregar_regla(menu_reglas, "YANKENPON", "A cada entrenador se le asigna un Gimnasio aleatoriamente: AGUA FUEGO o PLANTA (el resto sale en el nuevo DLC: Salon de la fama ReReloaded. La venganza de Magikarp). Se aplican coeficientes Clasicos pero se le suma la efectividad por tipo de gimnasio. NEUTRAL: +0\% DEBIL: -10\% FUERTE: +10\%", enfrentamiento_gimnasio);
    menu_agregar_regla(menu_reglas, "PELEADITTO", "Te cambiaron a tu equipo por Dittos y cada uno imita a un pokemon que puede ser de AGUA FUEGO o PLANTA (DLC proximamente: El Salon MejoraDitto - pls no me bajen puntos por esto D:). NEUTRAL: +0\% DEBIL: -10\% FUERTE: +10\%", enfrentamiento_enfrentaditto);

    return menu_reglas;
}

void salon_guardar(size_t argc, char *argv[], void *contexto)
{
    if (!argc || !argv || !contexto)
        return;

    bool *error = lista_elemento_en_posicion(*(lista_t **)contexto, 2);

    char *argumentos = argv[1];
    if (argc != 2 || strlen(argumentos) == 0)
    {
        *error = true;
        return;
    }

    //yo ya se que el contexto es una lista con argumentos.
    salon_t *salon = lista_elemento_en_posicion(*(lista_t **)contexto, 0);
    if (!salon)
    {
        *error = true;
        return;
    }

    char **str_salida = lista_elemento_en_posicion(*(lista_t **)contexto, 1);

    int guardado_exitoso = salon_guardar_archivo(salon, argumentos);

    if (guardado_exitoso != SALON_ERROR)
    {
        concatenar_resultado_ok(str_salida, ";");
    }
}

void salon_reglas(size_t argc, char *argv[], void *contexto)
{
    if (!argc || !argv || !contexto)
        return;
    bool *error = lista_elemento_en_posicion(*(lista_t **)contexto, 2);
    if (argc != 1)
    {
        *error = true;
        return;
    }
    //yo ya se que el contexto es una lista con argumentos.
    salon_t *salon = lista_elemento_en_posicion(*(lista_t **)contexto, 0);
    if (!salon)
    {
        *error = true;
        return;
    }
    char **resultado = lista_elemento_en_posicion(*(lista_t **)contexto, 1);

    menu_reglas_con_cada_elemento(salon->reglas, resultado);
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
        char *nombre_pokemon = *(char **)lista_elemento_en_posicion(*(lista_t **)extra, 0);
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
    lista_t *equipo = entrenador_obtener_equipo(entrenador);
    size_t *cantidad_pokemones = (size_t *)lista_elemento_en_posicion(*(lista_t **)extra, 1);
    *cantidad_pokemones = 0;
    lista_con_cada_elemento(equipo, verificar_pokemones, extra);
    return (*cantidad_pokemones > 0);
}

bool entrenadores_por_victoria(entrenador_t *entrenador, void *extra)
{
    int cant_victorias = entrenador_obtener_victorias(entrenador);

    int *cant_victorias_requeridas = (int *)lista_elemento_en_posicion(*(lista_t **)extra, 0);
    return (cant_victorias >= *cant_victorias_requeridas);
}

bool imprimir_entrenadores(void *entrenador, void *argumentos);

void salon_entrenadores(size_t argc, char *argv[], void *contexto)
{
    //tengo que recibir si o si todos estos parametros. Sino, falla.
    if (!argc || !argv || !contexto)
        return;

    bool *error = lista_elemento_en_posicion(*(lista_t **)contexto, 2);

    //contexto es una lista_t*, cuyo primer elemento es el salon
    salon_t *salon = lista_elemento_en_posicion(*(lista_t **)contexto, 0);
    if (!salon)
    {
        *error = true;
        return;
    }

    //contexto es una lista_t*, cuyo segundo elemento es un char* en donde voy a concatenar los entrenadores.
    char **string_resultado = lista_elemento_en_posicion(*(lista_t **)contexto, 1);

    lista_t *extra = lista_crear(NULL);
    if (!extra)
        return;

    lista_t *entrenadores_filtrados = NULL;
    //ahora que tengo los argumentos, puedo verificar que funcion voy a usar para filtrar.
    if (argc == 1)
    {
        entrenadores_filtrados = salon_filtrar_entrenadores(salon, todos_los_entrenadores, &extra);

        lista_t *lista_argumentos = lista_crear(NULL);

        char separador[2];
        strcpy(separador, ",");

        bool mostrar_victorias = true;
        bool mostrar_pokemones = false;

        lista_encolar(lista_argumentos, string_resultado);
        lista_encolar(lista_argumentos, separador);
        lista_encolar(lista_argumentos, &mostrar_victorias);
        lista_encolar(lista_argumentos, &mostrar_pokemones);

        lista_con_cada_elemento(entrenadores_filtrados, imprimir_entrenadores, &lista_argumentos);
        lista_destruir(lista_argumentos);
    }
    else if (argc == 2)
    {
        char **subcomando = split(argv[1], ',');
        if (!subcomando)
        {
            lista_destruir(extra);
            *error = true;
            return;
        }

        if (vtrlen(subcomando) != 2 || strcmp(subcomando[0], "") == 0 || strcmp(subcomando[1], "") == 0)
        {
            lista_destruir(extra);
            vtrfree(subcomando);
            *error = true;
            return;
        }

        if (strcmp(subcomando[0], "victorias") == 0)
        {
            //extra va a ser una lista_t* que contenga lista_t[0] = cant_victorias (por ahora lo veo asi para mantener el mismo criterio para todas las llamadas)
            int cant_victorias = atoi(subcomando[1]);
            lista_encolar(extra, &cant_victorias);
            entrenadores_filtrados = salon_filtrar_entrenadores(salon, entrenadores_por_victoria, &extra);

            lista_t *lista_argumentos = lista_crear(NULL);

            char separador[2];
            strcpy(separador, ",");

            bool mostrar_victorias = false;
            bool mostrar_pokemones = false;

            lista_encolar(lista_argumentos, string_resultado);
            lista_encolar(lista_argumentos, separador);
            lista_encolar(lista_argumentos, &mostrar_victorias);
            lista_encolar(lista_argumentos, &mostrar_pokemones);

            lista_con_cada_elemento(entrenadores_filtrados, imprimir_entrenadores, &lista_argumentos);
            lista_destruir(lista_argumentos);
        }
        else if (strcmp(subcomando[0], "pokemon") == 0)
        {
            //extra va a ser una lista_t* que contenga lista_t[0] = nombre_pokemon, y lista_t[1] = cantidad_pokemones
            size_t cant_pokemones = 0;
            lista_encolar(extra, &subcomando[1]);
            lista_encolar(extra, &cant_pokemones);
            entrenadores_filtrados = salon_filtrar_entrenadores(salon, entrenadores_por_pokemon, &extra);

            lista_t *lista_argumentos = lista_crear(NULL);

            char separador[2];
            strcpy(separador, ",");

            bool mostrar_victorias = false;
            bool mostrar_pokemones = false;

            lista_encolar(lista_argumentos, string_resultado);
            lista_encolar(lista_argumentos, separador);
            lista_encolar(lista_argumentos, &mostrar_victorias);
            lista_encolar(lista_argumentos, &mostrar_pokemones);

            lista_con_cada_elemento(entrenadores_filtrados, imprimir_entrenadores, &lista_argumentos);
            lista_destruir(lista_argumentos);
        }
        else
        {
            *error = true;
        }
        vtrfree(subcomando);
    }
    lista_destruir(extra);
    lista_destruir(entrenadores_filtrados);
}

bool imprimir_pokemones(void *pokemon, void *argumentos);

void salon_equipo(size_t argc, char *argv[], void *contexto)
{
    if (!argc || !argv || !contexto)
        return;

    bool *error = lista_elemento_en_posicion(*(lista_t **)contexto, 2);
    if (argc != 2)
    {
        *error = true;
        return;
    }

    //yo ya se que el contexto es una lista con argumentos.
    salon_t *salon = lista_elemento_en_posicion(*(lista_t **)contexto, 0);
    if (!salon)
    {
        *error = true;
        return;
    }

    entrenador_t *auxiliar_para_buscar_entrenador = entrenador_crear((char *)argv[1], 0);
    entrenador_t *entrenador_buscado = arbol_buscar(salon->entrenadores, auxiliar_para_buscar_entrenador);

    if (lista_vacia(entrenador_obtener_equipo(entrenador_buscado)))
    {
        *error = true;
        entrenador_destruir(auxiliar_para_buscar_entrenador);
        return;
    }

    char **string_resultado = lista_elemento_en_posicion(*(lista_t **)contexto, 1);

    lista_t *lista_argumentos = lista_crear(NULL);

    char separador[2];
    strcpy(separador, ",");

    lista_encolar(lista_argumentos, string_resultado);
    lista_encolar(lista_argumentos, separador);

    lista_con_cada_elemento(entrenador_obtener_equipo(entrenador_buscado), imprimir_pokemones, &lista_argumentos);
    lista_destruir(lista_argumentos);
    entrenador_destruir(auxiliar_para_buscar_entrenador);
}

bool agregar_pokemon_o_destruir(entrenador_t *entrenador, pokemon_t *pokemon);
pokemon_t *parsear_pokemon(char **campos);

void salon_agregar_pokemon(size_t argc, char *argv[], void *contexto)
{
    if (!argc || !argv || !contexto)
        return;

    bool *error = lista_elemento_en_posicion(*(lista_t **)contexto, 2);
    if (argc != 2)
    {
        *error = true;
        return;
    }
    //yo ya se que el contexto es una lista con argumentos.
    salon_t *salon = lista_elemento_en_posicion(*(lista_t **)contexto, 0);
    if (!salon)
    {
        *error = true;
        return;
    }

    char **resultado = lista_elemento_en_posicion(*(lista_t **)contexto, 1);

    char **subcomando = split(argv[1], ',');
    if (!subcomando)
    {
        *error = true;
        return;
    }

    if (vtrlen(subcomando) != 7)
    {
        *error = true;
        vtrfree(subcomando);
        return;
    }

    entrenador_t *auxiliar_para_buscar_entrenador = entrenador_crear((char *)subcomando[0], 0);
    entrenador_t *entrenador_buscado = arbol_buscar(salon->entrenadores, auxiliar_para_buscar_entrenador);

    if (!entrenador_buscado)
    {
        entrenador_destruir(auxiliar_para_buscar_entrenador);
        vtrfree(subcomando);
        *error = true;
        return;
    }

    pokemon_t *pokemon_creado = parsear_pokemon(subcomando + 1);
    if (!pokemon_creado)
    {
        entrenador_destruir(auxiliar_para_buscar_entrenador);
        vtrfree(subcomando);
        *error = true;
        return;
    }

    bool agregado_fallido = agregar_pokemon_o_destruir(entrenador_buscado, pokemon_creado);

    if (agregado_fallido)
    {
        entrenador_destruir(auxiliar_para_buscar_entrenador);
        vtrfree(subcomando);
        *error = true;
        return;
    }

    concatenar_resultado_ok(resultado, ";");

    entrenador_destruir(auxiliar_para_buscar_entrenador);
    vtrfree(subcomando);
}

bool obtener_posicion_pokemon(void *pokemon, void *extra)
{
    //extra va a ser una lista_t* que contenga lista_t[0] = nombre_pokemon, lista_t[1] = posicion_pokemon y lista_t[2] = bool encontrado
    if (pokemon)
    {
        char *nombre_pokemon = (char *)lista_elemento_en_posicion(*(lista_t **)extra, 0);
        int *posicion_pokemon = (int *)lista_elemento_en_posicion(*(lista_t **)extra, 1);
        bool *encontrado = (bool *)lista_elemento_en_posicion(*(lista_t **)extra, 2);

        if (strcasecmp(nombre_pokemon, pokemon_obtener_nombre((pokemon_t *)pokemon)) == 0)
        {
            *encontrado = true;
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
    lista_con_cada_elemento(equipo, obtener_posicion_pokemon, extra);
}

void salon_quitar_pokemon(size_t argc, char *argv[], void *contexto)
{
    if (!argc || !argv || !contexto)
        return;

    bool *error = lista_elemento_en_posicion(*(lista_t **)contexto, 2);

    if (argc != 2)
    {
        *error = true;
        return;
    }

    //yo ya se que el contexto es una lista con argumentos.
    salon_t *salon = lista_elemento_en_posicion(*(lista_t **)contexto, 0);
    if (!salon)
    {
        *error = true;
        return;
    }

    char **resultado = lista_elemento_en_posicion(*(lista_t **)contexto, 1);

    char **subcomando = split(argv[1], ',');
    if (!subcomando)
    {
        *error = true;
        return;
    }

    if (vtrlen(subcomando) != 2)
    {
        *error = true;
        vtrfree(subcomando);
        return;
    }

    entrenador_t *auxiliar_para_buscar_entrenador = entrenador_crear((char *)subcomando[0], 0);
    entrenador_t *entrenador_buscado = arbol_buscar(salon->entrenadores, auxiliar_para_buscar_entrenador);

    if (lista_elementos(entrenador_obtener_equipo(entrenador_buscado)) <= 1)
    {
        *error = true;
        entrenador_destruir(auxiliar_para_buscar_entrenador);
        vtrfree(subcomando);
        return;
    }

    size_t pos_pokemon = 0;
    bool encontrado = false;
    lista_t *lista_auxiliar = lista_crear(NULL);

    //subcomando[1] es el nombre del pokemon a eliminar
    lista_encolar(lista_auxiliar, subcomando[1]);

    //pos pokemon es la posicion del pokemon
    lista_encolar(lista_auxiliar, &pos_pokemon);

    lista_encolar(lista_auxiliar, &encontrado);

    //estoy pasando al entrenador, una posicion inicializada en 0 y el nombre del pokemon buscado y un flag para saber si lo encontré.
    buscar_pokemon(entrenador_buscado, &lista_auxiliar);

    if (!encontrado)
    {
        *error = true;
        lista_destruir(lista_auxiliar);
        entrenador_destruir(auxiliar_para_buscar_entrenador);
        vtrfree(subcomando);
        return;
    }

    int borrado_exitoso = lista_borrar_de_posicion(entrenador_obtener_equipo(entrenador_buscado), pos_pokemon);

    if (borrado_exitoso == SALON_ERROR)
    {
        *error = true;
        lista_destruir(lista_auxiliar);
        entrenador_destruir(auxiliar_para_buscar_entrenador);
        vtrfree(subcomando);
        return;
    }

    concatenar_resultado_ok(resultado, ";");

    entrenador_destruir(auxiliar_para_buscar_entrenador);
    vtrfree(subcomando);
    lista_destruir(lista_auxiliar);
}

bool enfrentar_entrenadores(salon_t *salon, entrenador_t *entrenador_1, entrenador_t *entrenador_2, char *regla, void *resultado, bool *error)
{

    lista_iterador_t *iterador_equipo_1 = lista_iterador_crear(entrenador_obtener_equipo(entrenador_1));
    lista_iterador_t *iterador_equipo_2 = lista_iterador_crear(entrenador_obtener_equipo(entrenador_2));
    int resultado_enfrentamiento = 0;
    lista_t *lista_contexto = lista_crear(NULL);
    if (!lista_contexto)
        return false;

    int gimnasio_pokemon = rand() % 2;
    int gimnasio_rival = rand() % 2;

    lista_encolar(lista_contexto, salon);
    lista_encolar(lista_contexto, &resultado_enfrentamiento);
    lista_encolar(lista_contexto, &gimnasio_pokemon);
    lista_encolar(lista_contexto, &gimnasio_rival);

    char separador[2];
    strcpy(separador, "");

    while (lista_iterador_tiene_siguiente(iterador_equipo_1) && lista_iterador_tiene_siguiente(iterador_equipo_2))
    {
        menu_procesar_regla(salon->reglas, regla, lista_iterador_elemento_actual(iterador_equipo_1), lista_iterador_elemento_actual(iterador_equipo_2), lista_contexto, error);
        if (resultado_enfrentamiento == 1)
        {
            lista_iterador_avanzar(iterador_equipo_2);
        }
        else
        {
            lista_iterador_avanzar(iterador_equipo_1);
        }

        char resultado_enfrentamiento_char[10];
        sprintf(resultado_enfrentamiento_char, "%i", resultado_enfrentamiento);

        size_t tam_resultado_enfrentamiento = strlen(resultado_enfrentamiento_char) + 2;

        void **vtr_enfrentamientos = NULL;
        vtr_enfrentamientos = vtradd(vtr_enfrentamientos, resultado_enfrentamiento_char);

        concatenar_str(vtr_enfrentamientos, tam_resultado_enfrentamiento, resultado, separador, agregar_salto_de_linea);

        free(vtr_enfrentamientos);
    }

    lista_iterador_destruir(iterador_equipo_1);
    lista_iterador_destruir(iterador_equipo_2);
    lista_destruir(lista_contexto);
    return true;
}

void salon_comparar(size_t argc, char *argv[], void *contexto)
{
    if (!argc || !argv || !contexto)
        return;

    bool *error = lista_elemento_en_posicion(*(lista_t **)contexto, 2);
    if (argc != 2 || strcmp(argv[1], "") == 0)
    {
        *error = true;
        return;
    }
    //yo ya se que el contexto es una lista con argumentos.
    salon_t *salon = lista_elemento_en_posicion(*(lista_t **)contexto, 0);
    if (!salon)
    {
        *error = true;
        return;
    }

    char **resultado = lista_elemento_en_posicion(*(lista_t **)contexto, 1);

    char **subcomando = split(argv[1], ',');
    if (!subcomando)
    {
        return;
    }

    if (vtrlen(subcomando) != 3 || strcmp(subcomando[0], "") == 0 || strcmp(subcomando[1], "") == 0 || strcmp(subcomando[2], "") == 0)
    {
        *error = true;
        vtrfree(subcomando);
        return;
    }

    entrenador_t *auxiliar_para_buscar_entrenador_1 = entrenador_crear((char *)subcomando[0], 0);
    entrenador_t *entrenador_buscado_1 = arbol_buscar(salon->entrenadores, auxiliar_para_buscar_entrenador_1);
    if (!entrenador_buscado_1)
    {
        *error = true;
        entrenador_destruir(auxiliar_para_buscar_entrenador_1);
        vtrfree(subcomando);
        return;
    }

    entrenador_t *auxiliar_para_buscar_entrenador_2 = entrenador_crear((char *)subcomando[1], 0);
    entrenador_t *entrenador_buscado_2 = arbol_buscar(salon->entrenadores, auxiliar_para_buscar_entrenador_2);
    if (!entrenador_buscado_2)
    {
        *error = true;
        entrenador_destruir(auxiliar_para_buscar_entrenador_1);
        entrenador_destruir(auxiliar_para_buscar_entrenador_2);
        vtrfree(subcomando);
        return;
    }

    bool comparacion_exitosa = enfrentar_entrenadores(salon, entrenador_buscado_1, entrenador_buscado_2, (char *)subcomando[2], resultado, error);

    if (!comparacion_exitosa)
        return;

    entrenador_destruir(auxiliar_para_buscar_entrenador_1);
    entrenador_destruir(auxiliar_para_buscar_entrenador_2);
    vtrfree(subcomando);
}

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

    salon->gimnasios = gimnasio_inicializar_gimnasios();
    if (!salon->gimnasios)
    {
        arbol_destruir(salon->entrenadores);
        menu_destruir(salon->menu_salon);
        menu_reglas_destruir(salon->reglas);
        free(salon);
        return NULL;
    }

    return salon;
}

bool validar_entrenadores(void *entrenador, void *extra)
{
    if (entrenador)
    {
        if (lista_vacia(entrenador_obtener_equipo((entrenador_t *)entrenador)))
        {
            *(bool *)extra = true;
            return false;
        }
    }
    return true;
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

bool imprimir_pokemones(void *pokemon, void *argumentos)
{
    if (pokemon)
    {
        char **str_salida = lista_elemento_en_posicion(*(lista_t **)argumentos, 0);
        char *separador = lista_elemento_en_posicion(*(lista_t **)argumentos, 1);

        concatenar_pokemon(pokemon, str_salida, separador);
        return true;
    }
    return false;
}

bool imprimir_entrenadores(void *entrenador, void *argumentos)
{
    if (entrenador)
    {
        char **str_salida = lista_elemento_en_posicion(*(lista_t **)argumentos, 0);
        char *separador = lista_elemento_en_posicion(*(lista_t **)argumentos, 1);
        bool *mostrar_victorias = lista_elemento_en_posicion(*(lista_t **)argumentos, 2);
        bool *mostrar_pokemones = lista_elemento_en_posicion(*(lista_t **)argumentos, 3);

        concatenar_entrenador((entrenador_t *)entrenador, str_salida, separador, *mostrar_victorias);
        if (*mostrar_pokemones)
            lista_con_cada_elemento((lista_t *)entrenador_obtener_equipo((entrenador_t *)entrenador), imprimir_pokemones, argumentos);
        return true;
    }
    return false;
}

int salon_guardar_archivo(salon_t *salon, const char *nombre_archivo)
{
    if (!salon || !nombre_archivo)
        return SALON_ERROR;

    bool error = false;

    abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, validar_entrenadores, &error);

    if (error)
        return SALON_ERROR;
    FILE *archivo_nuevo = fopen(nombre_archivo, "w");
    if (!archivo_nuevo)
        return SALON_ERROR;

    char *str_salida = malloc(sizeof(char) * 2);
    if (!str_salida)
    {
        fclosen(archivo_nuevo);
        return SALON_ERROR;
    }
    strcpy(str_salida, "");

    lista_t *lista_argumentos = lista_crear(NULL);

    char separador[2];
    strcpy(separador, ";");

    bool mostrar_victorias = true;
    bool mostrar_entrenadores = true;

    lista_encolar(lista_argumentos, &str_salida);
    lista_encolar(lista_argumentos, separador);
    lista_encolar(lista_argumentos, &mostrar_victorias);
    lista_encolar(lista_argumentos, &mostrar_entrenadores);

    int cant_entrenadores_guardados = (int)abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, imprimir_entrenadores, &lista_argumentos);
    fprintf(archivo_nuevo, "%s", str_salida);

    fclosen(archivo_nuevo);
    free(str_salida);
    lista_destruir(lista_argumentos);
    return GUARDADO_EXITOSO;
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

bool enlistar_entrenadores(void *entrenador, void *extra)
{
    if (entrenador)
        lista_encolar((lista_t *)extra, (entrenador_t *)entrenador);

    return true;
}

lista_t *salon_filtrar_entrenadores(salon_t *salon, bool (*f)(entrenador_t *, void *), void *extra)
{
    if (!salon || !f)
        return NULL;

    lista_t *lista_aux = lista_crear(NULL);
    if (!lista_aux)
        return NULL;

    abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, enlistar_entrenadores, lista_aux);

    lista_iterador_t *iterador_lista = lista_iterador_crear(lista_aux);
    lista_t *lista_final = lista_crear(NULL);

    while (lista_iterador_tiene_siguiente(iterador_lista))
    {
        if (f(lista_iterador_elemento_actual(iterador_lista), extra))
            lista_encolar(lista_final, lista_iterador_elemento_actual(iterador_lista));

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

    char *str_salida = malloc(sizeof(char) * 2);

    if (!str_salida)
        return NULL;

    strcpy(str_salida, "");

    bool error = false;

    lista_t *argumentos = lista_crear(NULL);
    lista_encolar(argumentos, salon);
    lista_encolar(argumentos, &str_salida);
    lista_encolar(argumentos, &error);

    menu_procesar_opcion(salon->menu_salon, comando, &argumentos);
    lista_destruir(argumentos);

    if (error)
    {
        free(str_salida);
        str_salida = NULL;
    }

    return str_salida;
}

void salon_destruir(salon_t *salon)
{
    if (salon)
    {
        if (salon->entrenadores)
            arbol_destruir(salon->entrenadores);

        if (salon->menu_salon)
            menu_destruir(salon->menu_salon);

        if (salon->reglas)
            menu_reglas_destruir(salon->reglas);

        if (salon->gimnasios)
            gimnasio_destruir_gimnasios(salon->gimnasios);

        free(salon);
    }
}