#include "salon.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    printf("               _,........__\n");
    printf("            ,-'            \"`-.\n");
    printf("          ,'                   `-.\n");
    printf("        ,'                        \\\n");
    printf("      ,'                           .\n");
    printf("      .'\\               ,\"\".       `\n");
    printf("     ._.'|             / |  `       \\\n");
    printf("     |   |            `-.'  ||       `.\n");
    printf("     |   |            '-._,'||       | \\\n");
    printf("     .`.,'             `..,'.'       , |`-.\n");
    printf("     l                       .'`.  _/  |   `.\n");
    printf("     `-.._'-   ,          _ _'   -\" \\  .     `\n");
    printf("`.\"\"\"\"\"'-.`-...,---------','         `. `....__.\n");
    printf(".'        `\"-..___      __,'\\          \\  \\     \\\n");
    printf("\\_ .          |   `\"\"\"\"'    `.           . \\     \\\n");
    printf("  `.          |              `.          |  .     L\n");
    printf("    `.        |`--...________.'.        j   |     |\n");
    printf("      `._    .'      |          `.     .|   ,     |\n");
    printf("         `--,\\       .            `7\"\"' |  ,      |\n");
    printf("            ` `      `            /     |  |      |    _,-'\"\"\"`-.\n");
    printf("             \\ `.     .          /      |  '      |  ,'          `.\n");
    printf("              \\  v.__  .        '       .   \\    /| /              \\\n");
    printf("               \\/    `\"\"\\\"\"\"\"\"\"\"`.       \\   \\  /.''                |\n");
    printf("                `        .        `._ ___,j.  `/ .-       ,---.     |\n");
    printf("                ,`-.      \\         .\"     `.  |/        j     `    |\n");
    printf("               /    `.     \\       /         \\ /         |     /    j\n");
    printf("              |       `-.   7-.._ .          |\"          '         /\n");
    printf("              |          `./_    `|          |            .     _,'\n");
    printf("              `.           / `----|          |-............`---'\n");
    printf("                \\          \\      |          |\n");
    printf("               ,'           )     `.         |\n");
    printf("                7____,,..--'      /          |\n");
    printf("                                  `---.__,--.'\n");
    printf("Crear un salon usando el archivo 'salon_original.sal'\n");
    salon_t* salon = salon_leer_archivo("salon_original.sal");
    if(!salon)
        return 1;


    printf("\nObtener los entrenadores con al menos 3 ligas ganadas y mostrarlos por pantalla.\n");
    entrenador_t** entrenadores_mas_exitosos_que_ash = salon_obtener_entrenadores_mas_ganadores(salon, 3);
    if(!entrenadores_mas_exitosos_que_ash){
        salon_destruir(salon);
        return 1;
    }

    size_t pos = 0;
    while(entrenadores_mas_exitosos_que_ash[pos]){
        salon_mostrar_entrenador(entrenadores_mas_exitosos_que_ash[pos]);
        pos++;
    }

    printf("\nAgregar 2 entrenadores al salon con 5 y 7 victorias respectivamente.\n");
    entrenador_t* entrenador1 = calloc(1, sizeof(entrenador_t));
    if(!entrenador1) {
        free(entrenadores_mas_exitosos_que_ash);
        salon_destruir(salon);
        return 1;
    }
    entrenador1->victorias = 5;

    salon_t* salon_aux = salon_agregar_entrenador(salon, entrenador1);
    if(!salon_aux) {
        free(entrenador1);
        free(entrenadores_mas_exitosos_que_ash);
        salon_destruir(salon);
        return 1;
    }

    entrenador_t* entrenador2 = calloc(1, sizeof(entrenador_t));
    if(!entrenador2) {
        free(entrenadores_mas_exitosos_que_ash);
        salon_destruir(salon);
        return 1;
    }
    entrenador2->victorias = 7;

    salon_aux = salon_agregar_entrenador(salon, entrenador2);
    if(!salon_aux) {
        free(entrenador2);
        free(entrenadores_mas_exitosos_que_ash);
        salon_destruir(salon);
        return 1;
    }

    printf("\nObtener los entrenadores con al menos 5 ligas ganadas y mostrarlos por pantalla.\n");
    entrenador_t** entrenadores_exitosos = salon_obtener_entrenadores_mas_ganadores(salon, 5);
    if(!entrenadores_exitosos) {
        free(entrenadores_mas_exitosos_que_ash);
        salon_destruir(salon);
        return 1;
    }

    pos = 0;
    while(entrenadores_exitosos[pos]){
        salon_mostrar_entrenador(entrenadores_exitosos[pos]);
        pos++;
    }

    printf("\nGuardar el salon a un nuevo archivo 'salon_modificado.sal'\n");
    int resultado = salon_guardar_archivo(salon, "salon_modificado.sal");
    if(resultado != 5) {
        free(entrenadores_exitosos);
        free(entrenadores_mas_exitosos_que_ash);
        salon_destruir(salon);
        return 1;
    }

    free(entrenadores_mas_exitosos_que_ash);
    free(entrenadores_exitosos);
    salon_destruir(salon);

    printf("\nSalir con valor de retorno 0\n");
    return 0;
}
