#include "reglas.h"
#include "hash.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define FORMATO_ESCRITURA_ARCH_REGLA "%s%s,%s\n" //formato quedaria: texto anterior + nombre,descripcion\n

struct regla
{
    const char *nombre;
    const char *descripcion;
    enfrentar enfrentamiento;
};

struct menu_reglas
{
    hash_t *reglas;
};

regla_t *regla_crear(const char *nombre, const char *descripcion, int (*enfrentamiento)(void *pokemon, void *rival, void *extra))
{
    regla_t *regla = calloc(1, sizeof(regla_t));
    if (!regla)
        return NULL;
    regla->nombre = nombre;
    regla->descripcion = descripcion;
    regla->enfrentamiento = enfrentamiento;

    return regla;
}

void regla_destruir(void *regla)
{
    free(regla);
}

menu_reglas_t *menu_reglas_crear()
{
    menu_reglas_t *menu_reglas = calloc(1, sizeof(menu_reglas_t));
    if (!menu_reglas)
        return NULL;

    menu_reglas->reglas = hash_crear(regla_destruir, 10);
    if (!menu_reglas->reglas)
    {
        free(menu_reglas);
        return NULL;
    }
    return menu_reglas;
}

void menu_agregar_regla(menu_reglas_t *menu_reglas, const char *nombre, const char *descripcion, int (*enfrentamiento)(void *pokemon, void *rival, void *extra))
{
    regla_t *regla_nueva = regla_crear(nombre, descripcion, enfrentamiento);
    if (!regla_nueva)
        return;
    hash_insertar(menu_reglas->reglas, regla_nueva->nombre, regla_nueva);
}

/**
tengo un problema con esta funcion y tiene que ver con que el iterador del hash, recorre los elementos para luego solo devolverme la clave.
Necesitaría que me devolviera el valor, pero por ahora simplemente voy a recuperar el valor buscandolo. Es malisimo, pero despues lo mejoro, cuando
cuando tenga una app funcionando.
**/

void concatenar_regla(regla_t *regla, void *resultado, char *separador)
{
    void **vector_regla = NULL;

    char char_nombre[strlen(regla->nombre) + 2];
    strcpy(char_nombre, regla->nombre);
    size_t tam_nom = strlen(char_nombre);
    vector_regla = vtradd(vector_regla, char_nombre);

    char char_desc[strlen(regla->descripcion) + 2];
    strcpy(char_desc, regla->descripcion);

    size_t tam_desc = strlen(char_desc);
    vector_regla = vtradd(vector_regla, char_desc);

    size_t tam_buffer = tam_nom + tam_desc + 2;

    char **str_salida = resultado;

    concatenar_str(vector_regla, tam_buffer, str_salida, separador, agregar_salto_de_linea);

    free(vector_regla);
}

bool imprimir_reglas_en_pantalla(hash_t *hash, const char *clave, void *str_salida)
{
    if (clave)
    {
        regla_t *regla = (regla_t *)hash_obtener(hash, clave);

        concatenar_regla(regla, str_salida, ",");
    }
    return true;
}

void menu_reglas_con_cada_elemento(menu_reglas_t *menu_reglas, void *resultado)
{
    hash_con_cada_clave(menu_reglas->reglas, imprimir_reglas_en_pantalla, resultado);
}

void menu_procesar_regla(menu_reglas_t *menu_reglas, const char *regla_buscada, void *pokemon_1, void *pokemon_2, void *contexto, void *error)
{
    regla_t *regla = hash_obtener(menu_reglas->reglas, regla_buscada);
    if (regla)
    {
        regla->enfrentamiento(pokemon_1, pokemon_2, contexto);
    }
    else
    {
        *(bool *)error = true;
    }
}

void menu_reglas_destruir(menu_reglas_t *menu_reglas)
{
    hash_destruir(menu_reglas->reglas);
    free(menu_reglas);
}