#ifndef MENU_H
#define MENU_H

#include <stddef.h>

typedef struct comando comando_t;

typedef void (*ejecutar)(size_t argc, char *argv[], void *);

typedef struct menu menu_t;

menu_t *menu_crear();

void menu_destruir(menu_t *menu);

void menu_agregar_comando(menu_t *menu, const char *nombre, const char *documentacion, void (*ejecutar)(size_t argc, char *argv[], void *));

void menu_procesar_opcion(menu_t *menu, const char *linea, void *contexto);

void menu_destruir(menu_t *menu);

#endif /* MENU_H */