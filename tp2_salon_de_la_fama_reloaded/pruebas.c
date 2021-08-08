#include "pa2mm.h"
#include "src/salon.h"
#include <string.h>

bool filtrar_entrenadores_por_victorias(entrenador_t *entrenador, void *cant_victorias)
{
    if (!entrenador)
        return false;
    //printf("entrenador: %s, victorias: %i\n", entrenador_obtener_nombre(entrenador), entrenador_obtener_victorias(entrenador));
    return entrenador_obtener_victorias(entrenador) > *(int *)cant_victorias;
}

void probarQueFuncioneMasoMeno()
{
    salon_t *salon = salon_leer_archivo("salones/salon_estandar.txt");
    entrenador_t *entrenador = entrenador_crear("MAURO", 10);
    pokemon_t *pokemon = pokemon_crear("PIKACHU", 10, 10, 10, 10, 10);
    entrenador_cargar_pokemon(entrenador, pokemon);
    salon_agregar_entrenador(salon, entrenador);

    int cant_entrenadores = salon_guardar_archivo(salon, "salones/salon_salida.txt");

    printf("se guardaron %i entrenadores en el archivo\n", cant_entrenadores);
    int cantidad_victorias = 10;
    lista_t *lista = salon_filtrar_entrenadores(salon, filtrar_entrenadores_por_victorias, &cantidad_victorias);
    printf("cantidad de entrenadores que cumplieron con esta condicion (10 victorias): %zu\n", lista_elementos(lista));

    lista_destruir(lista);

    cantidad_victorias = 50;
    lista = salon_filtrar_entrenadores(salon, filtrar_entrenadores_por_victorias, &cantidad_victorias);
    printf("cantidad de entrenadores que cumplieron con esta condicion (50 victorias): %zu\n", lista_elementos(lista));

    lista_destruir(lista);

    cantidad_victorias = 100;
    lista = salon_filtrar_entrenadores(salon, filtrar_entrenadores_por_victorias, &cantidad_victorias);
    printf("cantidad de entrenadores que cumplieron con esta condicion (100 victorias): %zu\n", lista_elementos(lista));

    char *resultado = salon_ejecutar_comando(salon, "ENTRENADORES");
    if (!resultado) {
        printf("el resultado es NULL\n");
    } else {
        printf("el resultado fue:\n%s\n", resultado);
        free(resultado);
    }

    char *resultado2 = salon_ejecutar_comando(salon, "EQUIPO:Mariano");
    if (!resultado2) {
        printf("el resultado 2 es NULL\n");
    } else {
        printf("el resultado2 fue:\n%s\n", resultado2);
        free(resultado2);
    }

    char *resultado3 = salon_ejecutar_comando(salon, "REGLAS");
    if (!resultado3) {
        printf("el resultado 3 es NULL\n");
    } else {
        printf("el resultado 3 fue:\n%s\n", resultado3);
        free(resultado3);
    }

    char *resultado4 = salon_ejecutar_comando(salon, "ENTRENADORES:pepe:josefo");
    if (!resultado4) {
        printf("el resultado 4 es NULL\n");
    } else {
        printf("el resultado 4 fue:\n%s\n", resultado4);
        free(resultado4);
    }

    char *resultado5 = salon_ejecutar_comando(salon, "ENTRENADORES:pokemon,Pikachu");
    if (!resultado5) {
        printf("el resultado 5 es NULL\n");
    } else {
        printf("el resultado 5 fue:\n%s\n", resultado5);
        free(resultado5);
    }

    char *resultado6 = salon_ejecutar_comando(salon, "AGREGAR_POKEMON:Stephi,slither,10,10,10,10,10");
    if (!resultado6) {
        printf("el resultado 6 es NULL\n");
    } else {
        printf("el resultado 6 fue:\n%s\n", resultado6);
        free(resultado6);
    }

    char *resultado7 = salon_ejecutar_comando(salon, "GUARDAR:josefo.txt");
    if (!resultado7) {
        printf("el resultado 7 es NULL\n");
    } else {
        printf("el resultado 7 fue:\n%s\n", resultado7);
        free(resultado7);
    }

    char *resultado8 = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Stephi,slither");
    if (!resultado8) {
        printf("el resultado 8 es NULL\n");
    } else {
        printf("el resultado 8 fue:\n%s\n", resultado8);
        free(resultado8);
    }

    char *resultado9 = salon_ejecutar_comando(salon, "GUARDAR:josefo_sin_slither.txt");
    if (!resultado9) {
        printf("el resultado 9 es NULL\n");
    } else {
        printf("el resultado 9 fue:\n%s\n", resultado9);
        free(resultado9);
    }

    char *resultado10 = salon_ejecutar_comando(salon, "COMPARAR:Stephi,Lucas,nombreregla");
    if (!resultado10) {
        printf("el resultado 10 es NULL\n");
    } else {
        printf("el resultado 10 fue:\n%s\n", resultado10);
        free(resultado10);
    }

    char *resultado11 = salon_ejecutar_comando(salon, "COMPARAR:Stephi,Lucas,CLASICO");
    if (!resultado10) {
        printf("el resultado 11 es NULL\n");
    } else {
        printf("el resultado 11 fue:\n%s\n", resultado11);
        free(resultado11);
    }

    lista_destruir(lista);

    salon_destruir(salon);
}

void dadoUnSalonNull_siLeoUnArchivoValido_SeCreaUnSalonDeFormaCorrecta()
{
    salon_t *salon = NULL;
    pa2m_afirmar(!salon, "El salon es NULL antes de leer el archivo");
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    pa2m_afirmar(salon, "El salon ya no es NULL luego de leer un archivo válido");
    salon_destruir(salon);
}

void dadoUnSalonNull_siLeoUnArchivoNull_elSalonSigueSiendoNull()
{
    salon_t *salon = NULL;
    pa2m_afirmar(!salon, "El salon es NULL antes de leer el archivo");
    salon = salon_leer_archivo(NULL);
    pa2m_afirmar(!salon, "Luego de leer un archivo NULL, el salon sigue siendo NULL");
    salon_destruir(salon);
}

void dadoUnSalonNull_siLeoUnArchivoNoExistente_elSalonSigueSiendoNull()
{
    salon_t *salon = NULL;
    pa2m_afirmar(!salon, "El salon es NULL antes de leer el archivo");
    salon = salon_leer_archivo("salones/archivo_que_no_existe.txt");
    pa2m_afirmar(!salon, "Luego de leer un archivo que no existe, el salon sigue siendo NULL");
    salon_destruir(salon);
}

void dadoUnSalonNull_siLeoUnArchivoExistentePeroVacio_elSalonSigueSiendoNull()
{
    salon_t *salon = NULL;
    pa2m_afirmar(!salon, "El salon es NULL antes de leer el archivo");
    salon = salon_leer_archivo("salones/archivo_vacio.txt");
    pa2m_afirmar(!salon, "Luego de leer un archivo que que existe pero está vacío, el salon sigue siendo NULL");
    salon_destruir(salon);
}

void dadoUnSalonNull_siLeoUnArchivoExistenteConPokemonesSinEntrenador_elSalonSigueSiendoNull()
{
    salon_t *salon = NULL;
    pa2m_afirmar(!salon, "El salon es NULL antes de leer el archivo");
    salon = salon_leer_archivo("salones/archivo_con_pokemon_sin_entrenador.txt");
    pa2m_afirmar(!salon, "Luego de leer un archivo que que existe pero con pokemones sin entrenador, el salon sigue siendo NULL");
    salon_destruir(salon);
}

void dadoUnSalonNull_siLeoUnArchivoExistenteConEntrenadorSinPokemones_elSalonSigueSiendoNull()
{
    salon_t *salon = NULL;
    pa2m_afirmar(!salon, "El salon es NULL antes de leer el archivo");
    salon = salon_leer_archivo("salones/archivo_con_entrenador_sin_pokemones.txt");
    pa2m_afirmar(!salon, "Luego de leer un archivo que que existe pero con un entrenador sin pokemones, el salon sigue siendo NULL");
    salon_destruir(salon);
}

void dadoUnSalonConEntrenadores_siGuardoAUnArchivoNull_elArchivoNoSeGuarda()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    pa2m_afirmar(salon_guardar_archivo(salon, NULL) == -1, "No se pudo guardar el salón, porque el path informado es NULL");
    salon_destruir(salon);
}

void dadoUnSalonConEntrenadores_siGuardoAUnArchivoConUnPathInvalido_elArchivoNoSeGuarda()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    pa2m_afirmar(salon_guardar_archivo(salon, "salones/") == -1, "No se pudo guardar el salón, porque el path informado es inválido");
    salon_destruir(salon);
}

void dadoUnSalonConEntrenadores_siGuardoAUnArchivoConUnPathValido_elArchivoSeGuardaCorrectamente()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    pa2m_afirmar(salon_guardar_archivo(salon, "salones/salon_estandar_nuevo.txt") == 5, "Se pudo guardar el salón correctamente en un archivo, habia 5 entrenadores");

    salon_t *salon2 = salon_leer_archivo("salones/salon_estandar_nuevo.txt");
    pa2m_afirmar(salon2, "Luego de guardar el archivo, se pudo leer sin problemas y crear un nuevo salon");

    pa2m_afirmar(salon_guardar_archivo(salon, "salones/salon_estandar_nuevo_bis.txt") == 5, "Se pudo guardar el salón correctamente en un archivo, habia 5 entrenadores");
    pa2m_afirmar(salon_guardar_archivo(salon, "salones/salon_estandar_nuevo_bis.txt") == 5, "Se pudo guardar el salón correctamente en un archivo, pisando el anterior archivo generado");

    salon_destruir(salon);
    salon_destruir(salon2);
}

void dadoUnSalonNull_siGuardoAUnArchivoConUnPathValido_NoPermiteGuardarPorqueElSalonEsNull()
{
    salon_t *salon = NULL;
    pa2m_afirmar(salon_guardar_archivo(salon, "salones/salon_null.txt") == -1, "No permitió guardar el salon a un archivo porque el salon era NULL");
    salon_destruir(salon);
}

void dadoUnSalonNull_siAgregoUnEntrenador_NoPermiteAgregarPorqueElSalonEsNull()
{
    salon_t *salon = NULL;
    entrenador_t *entrenador = entrenador_crear("Mauro", 10);
    pa2m_afirmar(!salon_agregar_entrenador(salon, entrenador), "No permite agregar un entrenador a un salon NULL");
    entrenador_destruir(entrenador);
    salon_destruir(salon);
}

void dadoUnSalon_siAgregoUnEntrenadorNull_NoPermiteAgregarPorqueElEntrenadorEsNull()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    entrenador_t *entrenador = NULL;
    pa2m_afirmar(!salon_agregar_entrenador(salon, entrenador), "No permite agregar un entrenador NULL a un salon");
    salon_destruir(salon);
}

void dadoUnSalon_siAgregoUnEntrenadorSinPokemonesYSolicitoGuardarSalon_NoPermiteGuardarPorqueElEntrenadorDebeTenerAlMenosUnPokemon()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    entrenador_t *entrenador = entrenador_crear("Mauro", 10);
    pa2m_afirmar(salon_agregar_entrenador(salon, entrenador), "Permite agregar un entrenador sin Pokemones a un salon. Para poder guardar el archivo se tiene que agregar al menos un pokemon");
    pa2m_afirmar(salon_guardar_archivo(salon, "salones/salon_entrenador_agregado_sin_pokemones.txt") == -1, "No permitió guardar el salon a un archivo porque el entrenador agregado no tenia pokemones");
    salon_destruir(salon);
}

void dadoUnSalon_siAgregoUnEntrenadorConPokemonesYSolicitoGuardarSalon_permiteGuardarCorrectamente()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    entrenador_t *entrenador = entrenador_crear("Mauro", 10);
    pokemon_t *pokemon = pokemon_crear("Pikachu", 10, 10, 10, 10, 10);
    entrenador_cargar_pokemon(entrenador, pokemon);

    pa2m_afirmar(salon_agregar_entrenador(salon, entrenador), "Permite agregar un entrenador con Pokemones a un salon.");
    pa2m_afirmar(salon_guardar_archivo(salon, "salones/salon_entrenador_agregado_con_pokemones.txt") == 6, "Permitió guardar el salon a un archivo porque el entrenador agregado tenia pokemones");
    salon_destruir(salon);
}

void dadoUnSalonNull_SiSolicitoFiltrarEntrenadores_NoPermiteFiltrarPorqueElSalonEsNull()
{
    salon_t *salon = NULL;
    int cant_victorias = 10;
    pa2m_afirmar(!salon_filtrar_entrenadores(salon, filtrar_entrenadores_por_victorias, &cant_victorias), "Filtrar entrenadores en un salon NULL devuelve NULL");
    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoFiltrarEntrenadoresYNoEncuentraResultados_permiteFiltrarCorrectamente()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    int cant_victorias = 10000;
    lista_t *lista_entrenadores_filtrados = salon_filtrar_entrenadores(salon, filtrar_entrenadores_por_victorias, &cant_victorias);
    pa2m_afirmar(lista_vacia(lista_entrenadores_filtrados), "Filtrar entrenadores en un salon por un criterio que no cumple ningun entrenador, devuelve una lista vacia");
    lista_destruir(lista_entrenadores_filtrados);
    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoFiltrarEntrenadoresConDistintosCriterios_permiteFiltrarCorrectamente()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    int cant_victorias = 0;
    lista_t *lista_entrenadores_filtrados = salon_filtrar_entrenadores(salon, filtrar_entrenadores_por_victorias, &cant_victorias);
    pa2m_afirmar(!lista_vacia(lista_entrenadores_filtrados), "Filtrar entrenadores con más de 0 victorias devuelve una lista no vacia.");
    pa2m_afirmar(lista_elementos(lista_entrenadores_filtrados) == 5, "Filtrar entrenadores con más de 0 victorias devuelve 5 entrenadores.");
    lista_destruir(lista_entrenadores_filtrados);

    cant_victorias = 34;
    lista_entrenadores_filtrados = salon_filtrar_entrenadores(salon, filtrar_entrenadores_por_victorias, &cant_victorias);
    pa2m_afirmar(!lista_vacia(lista_entrenadores_filtrados), "Filtrar entrenadores con más de 34 victorias devuelve una lista no vacia.");
    pa2m_afirmar(lista_elementos(lista_entrenadores_filtrados) == 4, "Filtrar entrenadores con más de 34 victorias devuelve 4 entrenadores.");
    lista_destruir(lista_entrenadores_filtrados);

    cant_victorias = 48;
    lista_entrenadores_filtrados = salon_filtrar_entrenadores(salon, filtrar_entrenadores_por_victorias, &cant_victorias);
    pa2m_afirmar(!lista_vacia(lista_entrenadores_filtrados), "Filtrar entrenadores con más de 48 victorias devuelve una lista no vacia.");
    pa2m_afirmar(lista_elementos(lista_entrenadores_filtrados) == 3, "Filtrar entrenadores con más de 48 victorias devuelve 3 entrenadores.");
    lista_destruir(lista_entrenadores_filtrados);

    cant_victorias = 49;
    lista_entrenadores_filtrados = salon_filtrar_entrenadores(salon, filtrar_entrenadores_por_victorias, &cant_victorias);
    pa2m_afirmar(!lista_vacia(lista_entrenadores_filtrados), "Filtrar entrenadores con más de 49 victorias devuelve una lista no vacia.");
    pa2m_afirmar(lista_elementos(lista_entrenadores_filtrados) == 2, "Filtrar entrenadores con más de 49 victorias devuelve 2 entrenadores.");
    lista_destruir(lista_entrenadores_filtrados);

    cant_victorias = 50;
    lista_entrenadores_filtrados = salon_filtrar_entrenadores(salon, filtrar_entrenadores_por_victorias, &cant_victorias);
    pa2m_afirmar(!lista_vacia(lista_entrenadores_filtrados), "Filtrar entrenadores con más de 50 victorias devuelve una lista no vacia.");
    pa2m_afirmar(lista_elementos(lista_entrenadores_filtrados) == 2, "Filtrar entrenadores con más de 50 victorias devuelve 2 entrenadores.");
    lista_destruir(lista_entrenadores_filtrados);

    cant_victorias = 53;
    lista_entrenadores_filtrados = salon_filtrar_entrenadores(salon, filtrar_entrenadores_por_victorias, &cant_victorias);
    pa2m_afirmar(!lista_vacia(lista_entrenadores_filtrados), "Filtrar entrenadores con más de 53 victorias devuelve una lista no vacia.");
    pa2m_afirmar(lista_elementos(lista_entrenadores_filtrados) == 1, "Filtrar entrenadores con más de 53 victorias devuelve 1 entrenadores.");
    lista_destruir(lista_entrenadores_filtrados);

    salon_destruir(salon);
}

void dadoUnSalonNull_SiSolicitoEjecutarComandoEntrenadores_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    char *resultado = salon_ejecutar_comando(salon, "ENTRENADORES");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando ENTRENADORES en un salon NULL");
    if (resultado)
        free(resultado);
    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoEntrenadoresMalEscrito_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    char *resultado = salon_ejecutar_comando(salon, "ENTRENADORE");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando ENTRENADORE en un salon");
    if (resultado)
        free(resultado);
    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoEntrenadores_PermiteEjecutarComandoCorrectamente()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    char *resultado = salon_ejecutar_comando(salon, "ENTRENADORES");
    pa2m_afirmar(strcmp(resultado, "Dani,47\nLucas,33\nMariano,68\nPucci,52\nStephi,49\n") == 0, "Devuelve correctamente el string \'Dani,47\\nLucas,33\\nMariano,68\\nPucci,52\\nStephi,49\\n\' (ordenado alfabéticamente) al ejecutar el comando ENTRENADORES en un salon");

    if (resultado)
        free(resultado);
    salon_destruir(salon);
}

void dadoUnSalonNull_SiSolicitoEjecutarComandoEntrenadoresVictorias_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    char *resultado = salon_ejecutar_comando(salon, "ENTRENADORES:victorias,10");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando ENTRENADORES:victorias,10 en un salon NULL");

    if (resultado)
        free(resultado);
    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoEntrenadoresVictoriasMalEscrito_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    char *resultado = salon_ejecutar_comando(salon, "ENTRENADORES:victoria,10");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando ENTRENADORES:victoria,10 en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "ENTRENADORES:victorias,10,20,30");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando ENTRENADORES:victorias,10,20,30 en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "ENTRENADORES:victorias");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando ENTRENADORES:victorias en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "ENTRENADORES:victorias,");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando ENTRENADORES:victorias, en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "ENTRENADORES:,10");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando ENTRENADORES:,10 en un salon");

    if (resultado)
        free(resultado);

    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoEntrenadoresVictorias_PermiteEjecutarComandoCorrectamente()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    char *resultado = salon_ejecutar_comando(salon, "ENTRENADORES:victorias,10");
    //Dani,47\nLucas,33\nMariano,68\nPucci,52\nStephi,49\n
    pa2m_afirmar(strcmp(resultado, "Dani\nLucas\nMariano\nPucci\nStephi\n") == 0, "Devuelve correctamente el string \'Dani\\nLucas\\nMariano\\nPucci\\nStephi\\n\' (ordenado alfabéticamente) al ejecutar el comando ENTRENADORES:victorias,10 en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "ENTRENADORES:victorias,33");
    pa2m_afirmar(strcmp(resultado, "Dani\nLucas\nMariano\nPucci\nStephi\n") == 0, "Devuelve correctamente el string \'Dani\\nLucas\\nMariano\\nPucci\\nStephi\\n\' (ordenado alfabéticamente) al ejecutar el comando ENTRENADORES:victorias,33 en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "ENTRENADORES:victorias,34");
    pa2m_afirmar(strcmp(resultado, "Dani\nMariano\nPucci\nStephi\n") == 0, "Devuelve correctamente el string \'Dani\\nMariano\\nPucci\\nStephi\\n\'        (ordenado alfabéticamente) al ejecutar el comando ENTRENADORES:victorias,34 en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "ENTRENADORES:victorias,48");
    pa2m_afirmar(strcmp(resultado, "Mariano\nPucci\nStephi\n") == 0, "Devuelve correctamente el string \'Mariano\\nPucci\\nStephi\\n\'              (ordenado alfabéticamente) al ejecutar el comando ENTRENADORES:victorias,48 en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "ENTRENADORES:victorias,50");
    pa2m_afirmar(strcmp(resultado, "Mariano\nPucci\n") == 0, "Devuelve correctamente el string \'Mariano\\nPucci\\n\'                      (ordenado alfabéticamente) al ejecutar el comando ENTRENADORES:victorias,50 en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "ENTRENADORES:victorias,53");
    pa2m_afirmar(strcmp(resultado, "Mariano\n") == 0, "Devuelve correctamente el string \'Mariano\\n\'                             (ordenado alfabéticamente) al ejecutar el comando ENTRENADORES:victorias,53 en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "ENTRENADORES:victorias,70");
    pa2m_afirmar(strcmp(resultado, "") == 0, "Devuelve correctamente el string \'\'                                      (ordenado alfabéticamente) al ejecutar el comando ENTRENADORES:victorias,70 en un salon");

    if (resultado)
        free(resultado);

    salon_destruir(salon);
}

void dadoUnSalonNull_SiSolicitoEjecutarComandoEntrenadoresPokemon_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    char *resultado = salon_ejecutar_comando(salon, "ENTRENADORES:pokemon,pikachu");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando ENTRENADORES:pokemon,pikachu en un salon NULL");

    if (resultado)
        free(resultado);
    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoEntrenadoresPokemonMalEscrito_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    char *resultado = salon_ejecutar_comando(salon, "ENTRENADORES:pokemo,pikachu");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando ENTRENADORES:pokemo,pikachu en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "ENTRENADORES:pokemon,pikachu,charmander,bulbasaur");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando ENTRENADORES:pokemon,pikachu,charmander,bulbasaur en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "ENTRENADORES:pokemon");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando ENTRENADORES:pokemon en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "ENTRENADORES:pokemon,");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando ENTRENADORES:pokemon, en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "ENTRENADORES:,pikachu");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando ENTRENADORES:,pikachu en un salon");

    if (resultado)
        free(resultado);

    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoEntrenadoresPokemon_PermiteEjecutarComandoCorrectamente()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    char *resultado = salon_ejecutar_comando(salon, "ENTRENADORES:pokemon,pikachu");
    pa2m_afirmar(strcmp(resultado, "Dani\nLucas\n") == 0, "Devuelve correctamente el string \'Dani\\nLucas\\n\' (ordenado alfabéticamente) al ejecutar el comando ENTRENADORES:pokemon,pikachu en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "ENTRENADORES:pokemon,lapras");
    pa2m_afirmar(strcmp(resultado, "Mariano\n") == 0, "Devuelve correctamente el string \'Mariano\\n\'     (ordenado alfabéticamente) al ejecutar el comando ENTRENADORES:pokemon,lapras en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "ENTRENADORES:pokemon,magicarp");
    pa2m_afirmar(strcmp(resultado, "") == 0, "Devuelve correctamente el string \'\'              (ordenado alfabéticamente) al ejecutar el comando ENTRENADORES:pokemon,magicarp en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "ENTRENADORES:pokemon,PIKACHU");
    pa2m_afirmar(strcmp(resultado, "Dani\nLucas\n") == 0, "Devuelve correctamente el string \'Dani\\nLucas\\n\' (ordenado alfabéticamente) al ejecutar el comando ENTRENADORES:pokemon,PIKACHU en un salon");

    if (resultado)
        free(resultado);

    salon_destruir(salon);
}

void dadoUnSalonNull_SiSolicitoEjecutarComandoEquipo_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    char *resultado = salon_ejecutar_comando(salon, "EQUIPO:Dani");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando EQUIPO:Dani en un salon NULL");

    if (resultado)
        free(resultado);
    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoEquipoMalEscrito_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    char *resultado = salon_ejecutar_comando(salon, "EQUIP:Dani");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando EQUIP:Dani en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:Lucia,Stephi");
    pa2m_afirmar(strcmp(resultado, "") == 0, "Devuelve \'\' al ejecutar el comando EQUIPO:Lucia,Stephi en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:");
    pa2m_afirmar(strcmp(resultado, "") == 0, "Devuelve \'\' al ejecutar el comando EQUIPO: en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:Pucci,");
    pa2m_afirmar(strcmp(resultado, "") == 0, "Devuelve \'\' al ejecutar el comando EQUIPO:Pucci, en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:,Lucas");
    pa2m_afirmar(strcmp(resultado, "") == 0, "Devuelve \'\' al ejecutar el comando EQUIPO:,Lucas en un salon");

    if (resultado)
        free(resultado);

    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoEquipo_PermiteEjecutarComandoCorrectamente()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    char *resultado = salon_ejecutar_comando(salon, "EQUIPO:Mariano");

    pa2m_afirmar(strcmp(resultado, "Lapras,46,47,18,29,40\nArticuno,21,12,60,14,15\nDragonair,71,92,71,34,25\nLapras,81,22,90,7,35\n") == 0, "Devuelve correctamente el string \'Lapras,46,47,18,29,40\\nArticuno,21,12,60,14,15\\nDragonair,71,92,71,34,25\\nLapras,81,22,90,7,35\\n\' al ejecutar el comando EQUIPO:Mariano en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:Mauro");
    pa2m_afirmar(strcmp(resultado, "") == 0, "Devuelve correctamente el string \'\' al ejecutar el comando EQUIPO:Mauro en un salon");

    if (resultado)
        free(resultado);

    salon_destruir(salon);
}

void dadoUnSalonNull_SiSolicitoEjecutarComandoReglas_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    char *resultado = salon_ejecutar_comando(salon, "REGLAS");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando REGLAS en un salon NULL");

    if (resultado)
        free(resultado);
    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoReglasMalEscrito_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    char *resultado = salon_ejecutar_comando(salon, "REGL");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando REGL en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "REGLAS:superfuerza");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando REGLAS:superfuerza en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "REGLAS:");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando REGLAS: en un salon");

    if (resultado)
        free(resultado);

    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoReglas_PermiteEjecutarComandoCorrectamente()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    char *resultado = salon_ejecutar_comando(salon, "REGLAS");

    pa2m_afirmar(strcmp(resultado, "MODERNO,las reglas modernas indican que un combate lo gana el Pokemon con el coeficiente de batalla mas alto en base al siguiente cálculo: 0.5 * nivel + 0.9 * defensa + 3 * inteligencia\nCLASICO,las reglas clásicas indican que un combate lo gana el Pokemon con el coeficiente de batalla mas alto en base al siguiente cálculo: 0.8 * nivel + fuerza + 2 * velocidad\n") == 0, "Devuelve correctamente el string al ejecutar el comando REGLAS en un salon");

    printf("%s\n", resultado);
    if (resultado)
        free(resultado);

    salon_destruir(salon);
}

void dadoUnSalonNull_SiSolicitoEjecutarComandoAgregarPokemon_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    char *resultado = salon_ejecutar_comando(salon, "AGREGAR_POKEMON:Stephi,scyther,10, 10, 10, 10");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando AGREGAR_POKEMON:Stephi,scyther,10, 10, 10, 10 en un salon NULL");

    if (resultado)
        free(resultado);
    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoAgregarPokemonMalEscrito_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    char *resultado = salon_ejecutar_comando(salon, "AGREGAR_POKEMO:Stephi,scyther,10, 10, 10, 10, 10");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando AGREGAR_POKEMO:Stephi,scyther,10, 10, 10, 10 en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "AGREGAR_POKEMON:Stephi,scyther,10, 10, 10, 10, 10, 10, 10, 10");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando AGREGAR_POKEMON:Stephi,scyther,10, 10, 10, 10, 10, 10, 10, 10 en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "AGREGAR_POKEMON:Lucas");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando AGREGAR_POKEMON:Lucas en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "AGREGAR_POKEMO:Stephi,scyther,10, 10, 10, 10, 10,");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando AGREGAR_POKEMO:Stephi,scyther,10, 10, 10, 10, 10, en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "AGREGAR_POKEMO:,Stephi,scyther,10, 10, 10, 10, 10");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando AGREGAR_POKEMO:,Stephi,scyther,10, 10, 10, 10, 10 en un salon");

    if (resultado)
        free(resultado);

    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoAgregarPokemon_PermiteEjecutarComandoCorrectamente()
{

    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");

    char *resultado = salon_ejecutar_comando(salon, "EQUIPO:Mariano");

    pa2m_afirmar(strcmp(resultado, "Lapras,46,47,18,29,40\nArticuno,21,12,60,14,15\nDragonair,71,92,71,34,25\nLapras,81,22,90,7,35\n") == 0, "Devuelve correctamente los pokemones de Mariano antes de agregar uno nuevo");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "AGREGAR_POKEMON:Mariano,scyther,10, 10, 10, 10, 10");

    pa2m_afirmar(strcmp(resultado, "OK\n") == 0, "Devuelve correctamente el string \'OK\\n\' al ejecutar el comando AGREGAR_POKEMON:Stephi,scyther,10, 10, 10, 10 en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:Mariano");

    pa2m_afirmar(strcmp(resultado, "Lapras,46,47,18,29,40\nArticuno,21,12,60,14,15\nDragonair,71,92,71,34,25\nLapras,81,22,90,7,35\nscyther,10,10,10,10,10\n") == 0, "Devuelve correctamente los pokemones de Mariano despues de agregar uno nuevo");

    if (resultado)
        free(resultado);

    entrenador_t *entrenador = entrenador_crear("MAURO", 10);
    pokemon_t *pokemon = pokemon_crear("PIKACHU", 10, 10, 10, 10, 10);
    entrenador_cargar_pokemon(entrenador, pokemon);

    salon_agregar_entrenador(salon, entrenador);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:MAURO");

    pa2m_afirmar(strcmp(resultado, "PIKACHU,10,10,10,10,10\n") == 0, "Devuelve correctamente los pokemones de MAURO antes de agregar un pokemon nuevo");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "AGREGAR_POKEMON:MAURO,scyther,10, 10, 10, 10, 10");

    pa2m_afirmar(strcmp(resultado, "OK\n") == 0, "Devuelve correctamente el string \'OK\\n\' al ejecutar el comando AGREGAR_POKEMON:MAURO,scyther,10, 10, 10, 10, 10 en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:MAURO");

    pa2m_afirmar(strcmp(resultado, "PIKACHU,10,10,10,10,10\nscyther,10,10,10,10,10\n") == 0, "Devuelve correctamente los pokemones de MAURO despues de agregar un pokemon nuevo");

    if (resultado)
        free(resultado);

    salon_destruir(salon);
}

int main()
{

    pa2m_nuevo_grupo("Pruebas lectura Archivo Nulo");
    dadoUnSalonNull_siLeoUnArchivoNull_elSalonSigueSiendoNull();

    pa2m_nuevo_grupo("Pruebas lectura Archivo que no existe");
    dadoUnSalonNull_siLeoUnArchivoNoExistente_elSalonSigueSiendoNull();

    pa2m_nuevo_grupo("Pruebas lectura Archivo que existe, pero está vacío");
    dadoUnSalonNull_siLeoUnArchivoExistentePeroVacio_elSalonSigueSiendoNull();

    pa2m_nuevo_grupo("Pruebas lectura Archivo que existe, pero tiene pokemones sin entrenador");
    dadoUnSalonNull_siLeoUnArchivoExistenteConPokemonesSinEntrenador_elSalonSigueSiendoNull();

    pa2m_nuevo_grupo("Pruebas lectura Archivo que existe, pero tiene entrenador sin pokemones");
    dadoUnSalonNull_siLeoUnArchivoExistenteConEntrenadorSinPokemones_elSalonSigueSiendoNull();

    pa2m_nuevo_grupo("Pruebas lectura Archivo valido");
    dadoUnSalonNull_siLeoUnArchivoValido_SeCreaUnSalonDeFormaCorrecta();

    pa2m_nuevo_grupo("Pruebas Guardar Archivo Nulo");
    dadoUnSalonConEntrenadores_siGuardoAUnArchivoNull_elArchivoNoSeGuarda();

    pa2m_nuevo_grupo("Pruebas Guardar Archivo Nombre Invalido");
    dadoUnSalonConEntrenadores_siGuardoAUnArchivoConUnPathInvalido_elArchivoNoSeGuarda();

    pa2m_nuevo_grupo("Pruebas Guardar Archivo en ubicacion válida");
    dadoUnSalonConEntrenadores_siGuardoAUnArchivoConUnPathValido_elArchivoSeGuardaCorrectamente();

    pa2m_nuevo_grupo("Pruebas Guardar Archivo en ubicación válida, pero con salon NULL");
    dadoUnSalonNull_siGuardoAUnArchivoConUnPathValido_NoPermiteGuardarPorqueElSalonEsNull();

    pa2m_nuevo_grupo("Pruebas Agregar Entrenador a un salon NULL");
    dadoUnSalonNull_siAgregoUnEntrenador_NoPermiteAgregarPorqueElSalonEsNull();

    pa2m_nuevo_grupo("Pruebas Agregar Entrenador NULL a un salon");
    dadoUnSalon_siAgregoUnEntrenadorNull_NoPermiteAgregarPorqueElEntrenadorEsNull();

    pa2m_nuevo_grupo("Pruebas Agregar Entrenador sin pokemones a un salon e intentar guardar salon");
    dadoUnSalon_siAgregoUnEntrenadorSinPokemonesYSolicitoGuardarSalon_NoPermiteGuardarPorqueElEntrenadorDebeTenerAlMenosUnPokemon();

    pa2m_nuevo_grupo("Pruebas Agregar Entrenador con pokemones a un salon e intentar guardar salon");
    dadoUnSalon_siAgregoUnEntrenadorConPokemonesYSolicitoGuardarSalon_permiteGuardarCorrectamente();

    pa2m_nuevo_grupo("Pruebas Filtrar Entrenador en salon NULL");
    dadoUnSalonNull_SiSolicitoFiltrarEntrenadores_NoPermiteFiltrarPorqueElSalonEsNull();

    pa2m_nuevo_grupo("Pruebas Filtrar Entrenador en salon con un criterio que no cumple ningun entrenador");
    dadoUnSalon_SiSolicitoFiltrarEntrenadoresYNoEncuentraResultados_permiteFiltrarCorrectamente();

    pa2m_nuevo_grupo("Pruebas Filtrar Entrenador en salon con distintos criterios");
    dadoUnSalon_SiSolicitoFiltrarEntrenadoresConDistintosCriterios_permiteFiltrarCorrectamente();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES en salon NULL");
    dadoUnSalonNull_SiSolicitoEjecutarComandoEntrenadores_NoPermiteEjecutarComando();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES mal escrito en salon");
    dadoUnSalon_SiSolicitoEjecutarComandoEntrenadoresMalEscrito_NoPermiteEjecutarComando();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES en salon");
    dadoUnSalon_SiSolicitoEjecutarComandoEntrenadores_PermiteEjecutarComandoCorrectamente();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES:victorias en salon NULL");
    dadoUnSalonNull_SiSolicitoEjecutarComandoEntrenadoresVictorias_NoPermiteEjecutarComando();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES:victorias mal escrito en salon");
    dadoUnSalon_SiSolicitoEjecutarComandoEntrenadoresVictoriasMalEscrito_NoPermiteEjecutarComando();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES:victorias en salon");
    dadoUnSalon_SiSolicitoEjecutarComandoEntrenadoresVictorias_PermiteEjecutarComandoCorrectamente();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES:pokemon en salon NULL");
    dadoUnSalonNull_SiSolicitoEjecutarComandoEntrenadoresPokemon_NoPermiteEjecutarComando();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES:pokemon mal escrito en salon");
    dadoUnSalon_SiSolicitoEjecutarComandoEntrenadoresPokemonMalEscrito_NoPermiteEjecutarComando();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES:pokemon en salon");
    dadoUnSalon_SiSolicitoEjecutarComandoEntrenadoresPokemon_PermiteEjecutarComandoCorrectamente();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos EQUIPO: en salon NULL");
    dadoUnSalonNull_SiSolicitoEjecutarComandoEquipo_NoPermiteEjecutarComando();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos EQUIPO: mal escrito en salon");
    dadoUnSalon_SiSolicitoEjecutarComandoEquipoMalEscrito_NoPermiteEjecutarComando();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos EQUIPO: en salon");
    dadoUnSalon_SiSolicitoEjecutarComandoEquipo_PermiteEjecutarComandoCorrectamente();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos REGLAS: en salon NULL");
    dadoUnSalonNull_SiSolicitoEjecutarComandoReglas_NoPermiteEjecutarComando();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos REGLAS: mal escrito en salon");
    dadoUnSalon_SiSolicitoEjecutarComandoReglasMalEscrito_NoPermiteEjecutarComando();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos REGLAS: en salon");
    dadoUnSalon_SiSolicitoEjecutarComandoReglas_PermiteEjecutarComandoCorrectamente();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos AGREGAR_POKEMON: en salon NULL");
    dadoUnSalonNull_SiSolicitoEjecutarComandoAgregarPokemon_NoPermiteEjecutarComando();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos AGREGAR_POKEMON: mal escrito en salon");
    dadoUnSalon_SiSolicitoEjecutarComandoAgregarPokemonMalEscrito_NoPermiteEjecutarComando();

    pa2m_nuevo_grupo("Pruebas Ejecutar Comandos AGREGAR_POKEMON: en salon");
    dadoUnSalon_SiSolicitoEjecutarComandoAgregarPokemon_PermiteEjecutarComandoCorrectamente();

    return pa2m_mostrar_reporte();
}
