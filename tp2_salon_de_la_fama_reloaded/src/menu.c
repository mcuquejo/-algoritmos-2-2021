#include "menu.h"
#include "hash.h"
#include "lista.h"
#include "utils.h"
#include <stdbool.h>

struct comando
{
    const char *nombre;
    const char *documentacion;
    ejecutar ejecutor;
    hash_t *subcomandos;
};

struct menu
{
    hash_t *comandos;
};

comando_t *comando_crear(const char *nombre, const char *documentacion, void (*ejecutar)(size_t argc, char *argv[], void *))
{
    comando_t *comando = calloc(1, sizeof(comando_t));
    if (!comando)
        return NULL;
    comando->nombre = nombre;
    comando->documentacion = documentacion;
    comando->ejecutor = ejecutar;

    return comando;
}

void comando_destruir(void *comando)
{
    if (comando)
        free(comando);
}

menu_t *menu_crear()
{
    menu_t *menu = calloc(1, sizeof(menu_t));
    if (!menu)
        return NULL;
    menu->comandos = hash_crear(comando_destruir, 10);
    if (!menu->comandos)
    {
        free(menu);
        return NULL;
    }
    return menu;
}

void menu_agregar_comando(menu_t *menu, const char *nombre, const char *documentacion, void (*ejecutar)(size_t argc, char *argv[], void *))
{
    comando_t *comando = comando_crear(nombre, documentacion, ejecutar);
    if (!comando)
        return;
    hash_insertar(menu->comandos, nombre, comando);
}

//ni siquiera es necesario que las funciones de ejecucion sean bool. No uso en ningun lado el resultado
void menu_procesar_opcion(menu_t *menu, const char *linea, void *contexto)
{
    bool *error = lista_elemento_en_posicion(*(lista_t **)contexto, 2);

    char **argumentos = split(linea, ':');
    if (!argumentos)
    {
        *error = true;
        printf("No se pudo ejecutar la opción\n");
        return;
    }

    comando_t *comando = hash_obtener(menu->comandos, argumentos[0]);
    if (comando)
    {
        comando->ejecutor(vtrlen(argumentos), argumentos, contexto);
    }
    else
    {
        *error = true;
    }
    vtrfree(argumentos);
}

void menu_destruir(menu_t *menu)
{
    hash_destruir(menu->comandos);
    free(menu);
}