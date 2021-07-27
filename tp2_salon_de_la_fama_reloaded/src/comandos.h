#ifndef COMANDOS_H
#define COMANDOS_H

typedef struct comando comando_t;

typedef bool (*ejecutar)(int argc, char* argv[], void*);

typedef struct menu menu_t;

menu_t* menu_crear();

void menu_destruir(menu_t* menu);

void agregar_comando(menu_t* menu, const char* nombre, const char* documentacion, bool (*ejecutar)(int argc, char* argv[], void*));

void procesar_opcion(menu_t* menu, char* linea, void* contexto);

#endif /* COMANDOS_H */