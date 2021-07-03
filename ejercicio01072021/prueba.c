#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hash.h"

//typedef struct {
//  Menu* menu_activo;
//    Jugador* jugador;
//    size_t tiempo;
//} Juego;

typedef struct {
    const char* nombre;
    const char* documentacion;
    bool (*ejecutar)(int argc, char* argv[], void*);
}Comando;

typedef struct{
    //Comando* comandos;
    const char* nombre_menu;
    const char* ayuda;
    hash_t* comandos;
    //hash_t* flags_comandos;
}Menu;

void agregar_comando(Menu* menu, const char* nombre, const char* doc, ){
    Comando *c = crear_comando();
    hash_insertar(menu->comandos, nombre, comando);

}

void procesar_opcion(char opcion, int* contador) {

    char* argumentos = split(linea, ' ');
    if(!argumentos) {
        printf("sos un gil");
        return;
    }
    Comando* comando = hash_buscar(menu->comandos, opcion);
    if(comando) {
        comando->ejecutar(vtrlen(argumentos), argumentos, contexto);
    }
}

void _procesar_opcion(char opcion, int * contador) {
    if(opcion == '?'){
                printf("esta es la ayuda\n");
            }
            else if(opcion == 'I'){
                printf("Contador incrementado\n");
                contador++;
            }
            else if(opcion == 'D'){
                printf("Contador disminuido\n");
                contador--;
            }
            else if(opcion == 'R'){
                printf("Contador reseteado\n");
                contador = 0;
            }
            else if(opcion == 'P'){
                printf("Se muestra contador\n");
                printf("%i\n", *contador);
            }
            else {
                printf("no seas gil\n");
            }
}

char* leer_linea(char* buffer, size_t tam) {
    char* respuesta = fgets(buffer, tam, stdin);
    if(respuesta)
        respuesta[strlen(respuesta) - 1] = 0;
    return respuesta;
}


int main(int argc, char *argv[]) {

    char buffer[512];
    buffer[0] = 0;

    int contador = 0;

    agregar_comando(menu, "I", "Incrementar contador", incrementar_contador);

    while (strcmp(buffer, "quit") != 0)
    {
        printf("> ");
        char* respuesta = leer_linea(buffer, 512);

        //if(respuesta) {
          //  char opcion = respuesta[0];
            //procesar_opcion(opcion, &contador);
        //}

        if(respuesta) {
            procesar_opcion();
            printf("\n");
        }
    }
}