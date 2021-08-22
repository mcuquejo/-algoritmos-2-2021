#include "pa2mm.h"
#include "src/salon.h"
#include "utils.h"
#include <string.h>

bool filtrar_entrenadores_por_victorias(entrenador_t *entrenador, void *cant_victorias)
{
    if (!entrenador)
        return false;
    return entrenador_obtener_victorias(entrenador) > *(int *)cant_victorias;
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

void dadoUnSalonNull_siLeoUnArchivoExistenteConEntrenadoresRepetidos_elSalonSigueSiendoNull()
{
    salon_t *salon = NULL;
    pa2m_afirmar(!salon, "El salon es NULL antes de leer el archivo");
    salon = salon_leer_archivo("salones/archivo_dos_entrenadores_iguales.txt");
    pa2m_afirmar(!salon, "Luego de leer un archivo que que existe pero con dos entrenadores con el mismo nombre, el salon sigue siendo NULL");
    pa2m_afirmar(salon_guardar_archivo(salon, "salones/archivo_dos_entrenadores_iguales_nuevo.txt") == -1, "No se pudo guardar el salón, porque el path informado es NULL");
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

    char *resultado = salon_ejecutar_comando(salon, "EQUIPO");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando EQUIP:Dani en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIP:Dani");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando EQUIP:Dani en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:Lucia,Stephi");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando EQUIPO:Lucia,Stephi en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando EQUIPO: en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:Pucci,");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando EQUIPO:Pucci, en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:,Lucas");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando EQUIPO:,Lucas en un salon");

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
    pa2m_afirmar(!resultado, "Devuelve correctamente NULL al ejecutar el comando EQUIPO:Mauro en un salon");

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

    pa2m_afirmar(strcmp(resultado, "MODERNO,las reglas modernas indican que un combate lo gana el Pokemon con el coeficiente de batalla mas alto en base al siguiente cálculo: 0.5 * nivel + 0.9 * defensa + 3 * inteligencia\nPELEADITTO,Te cambiaron a tu equipo por Dittos y cada uno imita a un pokemon que puede ser de AGUA FUEGO o PLANTA (DLC proximamente: El Salon MejoraDitto - pls no me bajen puntos por esto D:). NEUTRAL: +0% DEBIL: -10% FUERTE: +10%\nDIRTY_HARRY,Los pokemones atacan 10 veces. La fuerza del ataque se calcula con el coeficiente de la batalla moderna pero afectado por un valor aleatorio de SUERTE (de 1 a 10)\nYANKENPON,A cada entrenador se le asigna un Gimnasio aleatoriamente: AGUA FUEGO o PLANTA (el resto sale en el nuevo DLC: Salon de la fama ReReloaded. La venganza de Magikarp). Se aplican coeficientes Clasicos pero se le suma la efectividad por tipo de gimnasio. NEUTRAL: +0% DEBIL: -10% FUERTE: +10%\nCLASICO,las reglas clásicas indican que un combate lo gana el Pokemon con el coeficiente de batalla mas alto en base al siguiente cálculo: 0.8 * nivel + fuerza + 2 * velocidad\n") == 0, "Devuelve correctamente el string al ejecutar el comando REGLAS en un salon");

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

    resultado = salon_ejecutar_comando(salon, "AGREGAR_POKEMON:,Stephi,scyther,a,b,c,d,e");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando AGREGAR_POKEMON:,Stephi,scyther,a, b, c, d, e en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "AGREGAR_POKEMON:Moriano,Poke,1,2,3,4,5");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando AGREGAR_POKEMON:Moriano,Poke,1,2,3,4,5 en un salon");

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

    pa2m_afirmar(strcmp(resultado, STR_OK) == 0, "Devuelve correctamente el string \'OK\' al ejecutar el comando AGREGAR_POKEMON:Stephi,scyther,10, 10, 10, 10 en un salon");

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

    pa2m_afirmar(strcmp(resultado, "PIKACHU,10,10,10,10,10\n") == 0, "Devuelve correctamente los pokemones de MAURO (Entrenador recien creado) antes de agregar un pokemon nuevo");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "AGREGAR_POKEMON:MAURO,scyther,10, 10, 10, 10, 10");

    pa2m_afirmar(strcmp(resultado, STR_OK) == 0, "Devuelve correctamente el string \'OK\' al ejecutar el comando AGREGAR_POKEMON:MAURO,scyther,10, 10, 10, 10, 10 en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:MAURO");

    pa2m_afirmar(strcmp(resultado, "PIKACHU,10,10,10,10,10\nscyther,10,10,10,10,10\n") == 0, "Devuelve correctamente los pokemones de MAURO despues de agregar un pokemon nuevo");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "AGREGAR_POKEMON:Reynaldo,scyther,10, 10, 10, 10, 10");

    pa2m_afirmar(!resultado, "Devuelve correctamente NULL al ejecutar el comando AGREGAR_POKEMON:Reynaldo,scyther,10, 10, 10, 10 en un salon");

    if (resultado)
        free(resultado);

    entrenador = entrenador_crear("JORGE", 10);
    salon_agregar_entrenador(salon, entrenador);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:JORGE");

    pa2m_afirmar(!resultado, "Devuelve NULL (Entrenador recien creado) porque no se le cargó ningun pokemon aún");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "AGREGAR_POKEMON:JORGE,scyther,10, 10, 10, 10, 10");

    pa2m_afirmar(strcmp(resultado, STR_OK) == 0, "Devuelve correctamente el string \'OK\' al ejecutar el comando AGREGAR_POKEMON:JORGE,scyther,10, 10, 10, 10, 10 en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:JORGE");

    pa2m_afirmar(strcmp(resultado, "scyther,10,10,10,10,10\n") == 0, "Devuelve correctamente los pokemones de JORGE despues de agregar un pokemon nuevo");

    if (resultado)
        free(resultado);

    salon_destruir(salon);
}

void dadoUnSalonNull_SiSolicitoEjecutarComandoQuitarPokemon_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    char *resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Pucci,Gengar");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando QUITAR_POKEMON:Pucci,Gengar en un salon NULL");

    if (resultado)
        free(resultado);
    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoQuitarPokemonMalEscrito_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    char *resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMO:Pucci,Gengar");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando QUITAR_POKEMO:Pucci,Gengar en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Lucas,Nidoking,Zapdos");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando QUITAR_POKEMON:Lucas,Nidoking,Zapdos en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Mariano");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando QUITAR_POKEMON:Mariano en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Lucas,Nidoking,");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando QUITAR_POKEMON:Lucas,Nidoking, en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:,Dani,Barboach");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando QUITAR_POKEMON:,Dani,Barboach en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Mariano,NO_ESISTI'");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando QUITAR_POKEMON:Mariano,NO_ESISTI' en un salon");

    if (resultado)
        free(resultado);

    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoQuitarPokemon_PermiteEjecutarComandoCorrectamente()
{

    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");

    char *resultado = salon_ejecutar_comando(salon, "EQUIPO:Mariano");

    pa2m_afirmar(strcmp(resultado, "Lapras,46,47,18,29,40\nArticuno,21,12,60,14,15\nDragonair,71,92,71,34,25\nLapras,81,22,90,7,35\n") == 0, "Devuelve correctamente los pokemones de Mariano antes de quitar uno");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Mariano,Chikorita");

    pa2m_afirmar(!resultado, "Devuelve correctamente NULL al ejecutar el comando QUITAR_POKEMON:Mariano,Chikorita en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:Mariano");

    pa2m_afirmar(strcmp(resultado, "Lapras,46,47,18,29,40\nArticuno,21,12,60,14,15\nDragonair,71,92,71,34,25\nLapras,81,22,90,7,35\n") == 0, "Devuelve correctamente los pokemones de Mariano despues de intentar quitar uno que no estaba en el equipo");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Mariano,Lapras");

    pa2m_afirmar(strcmp(resultado, STR_OK) == 0, "Devuelve correctamente el string \'OK\' al ejecutar el comando QUITAR_POKEMON:Mariano,Lapras en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:Mariano");

    pa2m_afirmar(strcmp(resultado, "Articuno,21,12,60,14,15\nDragonair,71,92,71,34,25\nLapras,81,22,90,7,35\n") == 0, "Devuelve correctamente los pokemones de Mariano despues de eliminar uno");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Mariano,Lapras");

    pa2m_afirmar(strcmp(resultado, STR_OK) == 0, "Devuelve correctamente el string \'OK\' al ejecutar el comando QUITAR_POKEMON:Mariano,Lapras en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:Mariano");

    pa2m_afirmar(strcmp(resultado, "Articuno,21,12,60,14,15\nDragonair,71,92,71,34,25\n") == 0, "Devuelve correctamente los pokemones de Mariano despues de eliminar uno");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Mariano,Dragonair");

    pa2m_afirmar(strcmp(resultado, STR_OK) == 0, "Devuelve correctamente el string \'OK\' al ejecutar el comando QUITAR_POKEMON:Mariano,Dragonair en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:Mariano");

    pa2m_afirmar(strcmp(resultado, "Articuno,21,12,60,14,15\n") == 0, "Devuelve correctamente los pokemones de Mariano despues de eliminar uno");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Mariano,Articuno");

    pa2m_afirmar(!resultado, "Devuelve correctamente NULL al ejecutar el comando QUITAR_POKEMON:Mariano,Articuno en un salon, porque un entrenador no puede quedar sin pokemones");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:Mariano");

    pa2m_afirmar(strcmp(resultado, "Articuno,21,12,60,14,15\n") == 0, "Devuelve correctamente los pokemones de Mariano despues de intentar eliminar uno");

    if (resultado)
        free(resultado);

    entrenador_t *entrenador = entrenador_crear("MAURO", 10);
    pokemon_t *pokemon = pokemon_crear("PIKACHU", 10, 10, 10, 10, 10);
    entrenador_cargar_pokemon(entrenador, pokemon);

    salon_agregar_entrenador(salon, entrenador);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:MAURO");

    pa2m_afirmar(strcmp(resultado, "PIKACHU,10,10,10,10,10\n") == 0, "Devuelve correctamente los pokemones de MAURO (Entrenador recien creado) antes de intentar eliminar un pokemon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:MAURO,PIKACHU");

    pa2m_afirmar(!resultado, "Devuelve correctamente NULL al ejecutar el comando QUITAR_POKEMON:MAURO,PIKACHU en un salon, porque no se puede dejar sin pokemones a un entrenador");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:MAURO");

    pa2m_afirmar(strcmp(resultado, "PIKACHU,10,10,10,10,10\n") == 0, "Devuelve correctamente los pokemones de MAURO despues de intentar eliminar un pokemon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "AGREGAR_POKEMON:MAURO,scyther,10, 10, 10, 10, 10");

    pa2m_afirmar(strcmp(resultado, STR_OK) == 0, "Devuelve correctamente el string \'OK\' al ejecutar el comando AGREGAR_POKEMON:MAURO,scyther,10, 10, 10, 10, 10 en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:MAURO");

    pa2m_afirmar(strcmp(resultado, "PIKACHU,10,10,10,10,10\nscyther,10,10,10,10,10\n") == 0, "Devuelve correctamente los pokemones de MAURO despues de agregar un pokemon nuevo");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:MAURO,scyther");

    pa2m_afirmar(strcmp(resultado, STR_OK) == 0, "Devuelve correctamente el string \'OK\' al ejecutar el comando QUITAR_POKEMON:MAURO,PIKACHU en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "EQUIPO:MAURO");

    pa2m_afirmar(strcmp(resultado, "PIKACHU,10,10,10,10,10\n") == 0, "Devuelve correctamente los pokemones de MAURO despues de eliminar un pokemon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Tai,Agumon");

    pa2m_afirmar(!resultado, "Devuelve correctamente NULL al ejecutar el comando QUITAR_POKEMON:Tai,Agumon en un salon, porque te equivocaste de serie >:( (y porque no existe en el salon)");

    if (resultado)
        free(resultado);

    salon_destruir(salon);
}

void dadoUnSalonNull_SiSolicitoEjecutarComandoGuardar_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    char *resultado = salon_ejecutar_comando(salon, "GUARDAR:salones/guardar_comando_salon_null.txt");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando GUARDAR:guardar_comando_salon_null.txt en un salon NULL");

    if (resultado)
        free(resultado);
    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoGuardarMalEscrito_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    char *resultado = salon_ejecutar_comando(salon, "GUARDA:archivo_salon_comando_mal.txt");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando GUARDA:archivo_salon_comando_mal.txt en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "GUARDAR:");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando GUARDAR: en un salon");

    if (resultado)
        free(resultado);

    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoGuardar_PermiteEjecutarComandoCorrectamente()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    char *resultado = salon_ejecutar_comando(salon, "GUARDAR:archivo_salon_comando_correcto.txt");
    pa2m_afirmar(strcmp(resultado, STR_OK) == 0, "Devuelve \'OK\' al ejecutar el comando GUARDAR:archivo_salon_comando_correcto.txt en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Mariano,Lapras");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "GUARDAR:archivo_salon_comando_correcto_modificado.txt");
    pa2m_afirmar(strcmp(resultado, "OK") == 0, "Devuelve \'OK\' al ejecutar el comando GUARDAR:archivo_salon_comando_correcto_modificado.txt en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "AGREGAR_POKEMON:Mariano,scyther,10, 10, 10, 10, 10");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "GUARDAR:archivo_salon_comando_correcto_modificado_2.txt");
    pa2m_afirmar(strcmp(resultado, STR_OK) == 0, "Devuelve \'OK\' al ejecutar el comando GUARDAR:archivo_salon_comando_correcto_modificado_2.txt en un salon");

    if (resultado)
        free(resultado);

    salon_destruir(salon);
}

void dadoUnSalonNull_SiSolicitoEjecutarComandoComparar_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    char *resultado = salon_ejecutar_comando(salon, "COMPARAR:Mariano,Lucas,CLASICO");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando COMPARAR:Mariano,Lucas,CLASICO en un salon NULL");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:Mariano,Lucas,MODERNO");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando COMPARAR:Mariano,Lucas,MODERNO en un salon NULL");

    if (resultado)
        free(resultado);
    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoCompararMalEscrito_NoPermiteEjecutarComando()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    char *resultado = salon_ejecutar_comando(salon, "COMPRAR:Mariano,Lucas,CLASICO");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando COMPRAR:Mariano,Lucas,CLASICO en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando COMPARAR: en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando COMPARAR: en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:Lucas,,CLASICO");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando COMPARAR:Lucas,,CLASICO en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:,Mariano,CLASICO");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando COMPARAR:,Mariano,CLASICO en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:Lucas,Mariano,");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando COMPARAR:Lucas,Mariano, en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:Lucas,Mariano,LAUNICAREGLAESQUENOHAYREGLAS");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando COMPARAR:Lucas,Mariano,LAUNICAREGLAESQUENOHAYREGLAS en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:Stephi,QUIEN_SO,MODERNO");
    pa2m_afirmar(!resultado, "Devuelve NULL al ejecutar el comando COMPARAR:Stephi,QUIEN_SO,MODERNO en un salon");

    if (resultado)
        free(resultado);

    salon_destruir(salon);
}

void dadoUnSalon_SiSolicitoEjecutarComandoComparar_PermiteEjecutarComandoCorrectamente()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");
    char *resultado = salon_ejecutar_comando(salon, "COMPARAR:Lucas,Mariano,CLASICO");

    pa2m_afirmar(strcmp(resultado, "1\n1\n2\n2\n2\n2\n2\n2\n") == 0, "El resultado obtenido es el esperado al comparar a Lucas Contra Mariano en enfrentamiento clásico");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:Lucas,Mariano,MODERNO");

    pa2m_afirmar(strcmp(resultado, "2\n1\n1\n2\n2\n2\n2\n1\n1\n") == 0, "El resultado obtenido es el esperado al comparar a Lucas Contra Mariano en enfrentamiento MODERNO");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:Lucas,Lucas,MODERNO");

    pa2m_afirmar(strcmp(resultado, "1\n2\n1\n1\n1\n1\n2\n2\n2\n2\n1\n") == 0, "El resultado obtenido es el esperado al comparar a Lucas Contra Lucas en enfrentamiento MODERNO");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:Lucas,Lucas,CLASICO");

    pa2m_afirmar(strcmp(resultado, "1\n1\n1\n2\n2\n2\n1\n1\n1\n") == 0, "El resultado obtenido es el esperado al comparar a Lucas Contra Lucas en enfrentamiento CLASICO");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:Stephi,Pucci,DIRTY_HARRY");

    pa2m_afirmar(resultado, "Se ejecuta: COMPARAR:Stephi,Pucci,DIRTY_HARRY. El enfrentamiento con suerte es aleatorio. Se valida que haya devuelto un String distinto de NULL");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:Stephi,Pucci,YANKENPON");

    pa2m_afirmar(resultado, "Se ejecuta: COMPARAR:Stephi,Pucci,YANKENPON. El gimnasio es aleatorio. Se valida que haya devuelto un String distinto de NULL");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:Mariano,Pucci,YANKENPON");

    pa2m_afirmar(resultado, "Se ejecuta: COMPARAR:Mariano,Pucci,YANKENPON. El gimnasio es aleatorio. Se valida que haya devuelto un String distinto de NULL");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:Pucci,Lucas,PELEADITTO");

    pa2m_afirmar(resultado, "Se ejecuta: COMPARAR:Pucci,Lucas,PELEADITTO. El tipo de cada pokemon es aleatorio. Se valida que haya devuelto un String distinto de NULL");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:Stephi,Pucci,PELEADITTO");

    pa2m_afirmar(resultado, "Se ejecuta: COMPARAR:Stephi,Pucci,PELEADITTO. El tipo de cada pokemon es aleatorio. Se valida que haya devuelto un String distinto de NULL");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:Mariano,Pucci,PELEADITTO");

    pa2m_afirmar(resultado, "Se ejecuta: COMPARAR:Mariano,Pucci,PELEADITTO. El tipo de cada pokemon es aleatorio. Se valida que haya devuelto un String distinto de NULL");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "COMPARAR:Pucci,Lucas,PELEADITTO");

    pa2m_afirmar(resultado, "Se ejecuta: COMPARAR:Pucci,Lucas,PELEADITTO. El tipo de cada pokemon es aleatorio. Se valida que haya devuelto un String distinto de NULL");

    if (resultado)
        free(resultado);

    salon_destruir(salon);
}

void dadoUnSalonConEntrenadores_siModificoElSalonYGuardoAUnArchivoConUnPathValido_elArchivoSeGuardaCorrectamente()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");

    char *resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Mariano,Dragonair");

    pa2m_afirmar(strcmp(resultado, STR_OK) == 0, "Devuelve correctamente el string \'OK\' al ejecutar el comando QUITAR_POKEMON:Mariano,Dragonair en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Mariano,Lapras");

    pa2m_afirmar(strcmp(resultado, STR_OK) == 0, "Devuelve correctamente el string \'OK\' al ejecutar el comando QUITAR_POKEMON:Mariano,Dragonair en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Mariano,Lapras");

    pa2m_afirmar(strcmp(resultado, STR_OK) == 0, "Devuelve correctamente el string \'OK\' al ejecutar el comando QUITAR_POKEMON:Mariano,Dragonair en un salon");

    if (resultado)
        free(resultado);

    pa2m_afirmar(salon_guardar_archivo(salon, "salones/salon_estandar_nuevo.txt") == 5, "Se pudo guardar el salón correctamente en un archivo, habia 5 entrenadores");

    salon_t *salon2 = salon_leer_archivo("salones/salon_estandar_nuevo.txt");
    pa2m_afirmar(salon2, "Luego de guardar el archivo, se pudo leer sin problemas y crear un nuevo salon");

    resultado = salon_ejecutar_comando(salon2, "EQUIPO:Mariano");

    pa2m_afirmar(strcmp(resultado, "Articuno,21,12,60,14,15\n") == 0, "Devuelve correctamente el string \'Lapras;46;47;18;29;40\\nArticuno;21;12;60;14;15\\nLapras;81;22;90;7;35\\n\' al ejecutar el comando EQUIPO:Mariano en un salon");

    if (resultado)
        free(resultado);

    pa2m_afirmar(salon_guardar_archivo(salon, "salones/salon_estandar_nuevo_bis.txt") == 5, "Se pudo guardar el salón correctamente en un archivo, habia 5 entrenadores");

    resultado = salon_ejecutar_comando(salon2, "QUITAR_POKEMON:Mariano,Lapras");

    pa2m_afirmar(!resultado, "Devuelve correctamente NULL al ejecutar el comando QUITAR_POKEMON:Mariano,Lapras en un salon");

    if (resultado)
        free(resultado);

    pa2m_afirmar(salon_guardar_archivo(salon2, "salones/salon_estandar_nuevo_bis.txt") == 5, "Se pudo guardar el salón correctamente en un archivo, pisando el anterior archivo generado");
    pa2m_afirmar(salon_guardar_archivo(salon, "salones/salon_estandar_nuevo_bis_bis.txt") == 5, "Se pudo guardar el salón correctamente en un archivo, habia 5 entrenadores");

    salon_t *salon3 = salon_leer_archivo("salones/salon_estandar_nuevo_bis.txt");
    salon_t *salon4 = salon_leer_archivo("salones/salon_estandar_nuevo_bis_bis.txt");

    salon_destruir(salon);
    salon_destruir(salon2);
    salon_destruir(salon3);
    salon_destruir(salon4);
}

void dadoUnSalonConEntrenadores_SiEliminoYAgregoEntrenadoresYPokemones_LosCambiosSeReflejanCorrectamenteEnElSalonYEnLosArchivos()
{
    salon_t *salon = salon_leer_archivo("salones/salon_estandar.txt");

    entrenador_t *entrenador = entrenador_crear("Mauro", 31);

    pokemon_t *pokemon = pokemon_crear("Pikachu", 10, 10, 10, 10, 10);

    entrenador_cargar_pokemon(entrenador, pokemon);

    salon_agregar_entrenador(salon, entrenador);

    char *resultado = salon_ejecutar_comando(salon, "AGREGAR_POKEMON:Mariano,Sudowoodo");
    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Stephi,Lucario");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon, "GUARDAR:prueba_chanutron.txt");

    if (resultado)
        free(resultado);

    salon_t *salon2 = salon_leer_archivo("prueba_chanutron.txt");

    char *resultado_equipo_salon = salon_ejecutar_comando(salon, "EQUIPO:Mauro");
    char *resultado_equipo_salon2 = salon_ejecutar_comando(salon2, "EQUIPO:Mauro");

    pa2m_afirmar(strcmp(resultado_equipo_salon, resultado_equipo_salon2) == 0, "Los datos guardados en el nuevo archivo son correctos");

    if (resultado_equipo_salon)
        free(resultado_equipo_salon);

    if (resultado_equipo_salon2)
        free(resultado_equipo_salon2);

    salon_destruir(salon);
    salon_destruir(salon2);
}

void dadoUnSalonConEntrenadores_siAgregoYQuitoPokemones_elSalonSeActualizaDeFormaCorrecta()
{
    salon_t *salon = NULL;
    salon = salon_leer_archivo("salones/salon_estandar.txt");

    char *resultado = salon_ejecutar_comando(salon, "QUITAR_POKEMON:Mariano,Dragonair");

    pa2m_afirmar(strcmp(resultado, STR_OK) == 0, "Devuelve correctamente el string \'OK\' al ejecutar el comando QUITAR_POKEMON:Mariano,Dragonair en un salon");

    if (resultado)
        free(resultado);

    pa2m_afirmar(salon_guardar_archivo(salon, "salones/salon_estandar_nuevo.txt") == 5, "Se pudo guardar el salón correctamente en un archivo, habia 5 entrenadores");

    salon_t *salon2 = salon_leer_archivo("salones/salon_estandar_nuevo.txt");

    pa2m_afirmar(salon2, "Luego de guardar el archivo, se pudo leer sin problemas y crear un nuevo salon");

    resultado = salon_ejecutar_comando(salon2, "EQUIPO:Mariano");

    pa2m_afirmar(strcmp(resultado, "Lapras,46,47,18,29,40\nArticuno,21,12,60,14,15\nLapras,81,22,90,7,35\n") == 0, "Devuelve correctamente el string \'Lapras;46;47;18;29;40\\nArticuno;21;12;60;14;15\\nLapras;81;22;90;7;35\\n\' al ejecutar el comando EQUIPO:Mariano en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon2, "QUITAR_POKEMON:Mariano,Lapras");

    pa2m_afirmar(strcmp(resultado, STR_OK) == 0, "Devuelve correctamente el string \'OK\' al ejecutar el comando QUITAR_POKEMON:Mariano,Lapras en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon2, "QUITAR_POKEMON:Mariano,Lapras");

    pa2m_afirmar(strcmp(resultado, STR_OK) == 0, "Devuelve correctamente el string \'OK\' al ejecutar el comando QUITAR_POKEMON:Mariano,Lapras en un salon");

    if (resultado)
        free(resultado);

    resultado = salon_ejecutar_comando(salon2, "QUITAR_POKEMON:Mariano,Articuno");

    pa2m_afirmar(!resultado, "Devuelve correctamente NULL al ejecutar el comando QUITAR_POKEMON:Mariano,Articuno en un salon siendo el ultimo pokemon");

    if (resultado)
        free(resultado);

    pa2m_afirmar(salon_guardar_archivo(salon2, "salones/salon_estandar_nuevo_bis.txt") == 5, "Se pudo guardar el salón correctamente en un archivo, habia 5 entrenadores");
    pa2m_afirmar(salon_guardar_archivo(salon2, "salones/salon_estandar_nuevo_bis.txt") == 5, "Se pudo guardar el salón correctamente en un archivo, pisando el anterior archivo generado");

    salon_destruir(salon);
    salon_destruir(salon2);
}

// void pruebasConcatPokemon()
// {
//     pokemon_t *pokemon = pokemon_crear("PIKACHU", 1, 2, 3, 4, 5);
//     pokemon_t *pokemon2 = pokemon_crear("CHARMANDER", 6, 7, 8, 9, 10);

//     //inicializo resultado a NULL.
//     char *resultado = malloc(sizeof(char) * 2);
//     //resultado por ahora es un string vacio
//     strcpy(resultado, "");

//     concatenar_pokemon(pokemon, &resultado, ";");
//     printf("el resultado es:\n%s", resultado);
//     concatenar_pokemon(pokemon2, &resultado, ";");

//     printf("el resultado es:\n%s", resultado);

//     pokemon_destruir(pokemon);
//     pokemon_destruir(pokemon2);
//     free(resultado);
// }

// void pruebasConcatEntrenador()
// {

//     entrenador_t *entrenador = entrenador_crear("PEPE", 10);
//     entrenador_t *entrenador2 = entrenador_crear("JORGE", 7);

//     //inicializo resultado a NULL.
//     char *resultado = malloc(sizeof(char) * 2);
//     //resultado por ahora es un string vacio
//     strcpy(resultado, "");

//     concatenar_entrenador(entrenador, &resultado, ";", true);
//     printf("el resultado es:\n%s", resultado);
//     concatenar_entrenador(entrenador2, &resultado, ";", true);
//     printf("el resultado es:\n%s", resultado);

//     entrenador_destruir(entrenador);
//     entrenador_destruir(entrenador2);
//     free(resultado);
// }

// void pruebasConcatEntrenadorSinVictorias()
// {

//     entrenador_t *entrenador = entrenador_crear("PEPE", 10);
//     entrenador_t *entrenador2 = entrenador_crear("JORGE", 7);

//     //inicializo resultado a NULL.
//     char *resultado = malloc(sizeof(char) * 2);
//     //resultado por ahora es un string vacio
//     strcpy(resultado, "");

//     concatenar_entrenador(entrenador, &resultado, ";", false);
//     printf("el resultado es:\n%s", resultado);
//     concatenar_entrenador(entrenador2, &resultado, ";", false);
//     printf("el resultado es:\n%s", resultado);

//     entrenador_destruir(entrenador);
//     entrenador_destruir(entrenador2);
//     free(resultado);
// }

void dadoUnVectorDinamicoNull_SiSolicitoConcatenarLosStrings_NoPermiteConcatenar()
{
    void **vector_dinamico = NULL;
    char *salida_str = malloc(sizeof(char) * 2);
    strcpy(salida_str, "");
    concatenar_str(vector_dinamico, 10, &salida_str, ",", false);
    pa2m_afirmar(strcmp(salida_str, "") == 0, "El string de salida sigue siendo un string vacio porque no se puede concatenar con un vector dinamico NULL");
    free(salida_str);
    free(vector_dinamico);
}

void dadoUnVectorDinamicoDeStrings_SiSolicitoConcatenarLosStrings_LosStringsSeConcatenanCorrectamente()
{
    void **vector_dinamico = NULL;
    char *salida_str = malloc(sizeof(char) * 2);
    strcpy(salida_str, "");

    char elemento_1[10];
    strcpy(elemento_1, "valor 1");
    char elemento_2[10];
    strcpy(elemento_2, "valor 2");
    char elemento_3[10];
    strcpy(elemento_3, "valor 3");

    size_t tam_buffer = strlen(elemento_1) + strlen(elemento_2) + strlen(elemento_3) + 2;

    vector_dinamico = vtradd(vector_dinamico, elemento_1);
    vector_dinamico = vtradd(vector_dinamico, elemento_2);
    vector_dinamico = vtradd(vector_dinamico, elemento_3);

    concatenar_str(vector_dinamico, tam_buffer, &salida_str, ",", false);
    pa2m_afirmar(strcmp(salida_str, "valor 1,valor 2,valor 3") == 0, "El string de salida se concateno correctamente con valor \'valor 1,valor 2,valor 3\'");

    printf("%s", salida_str);
    free(salida_str);
    free(vector_dinamico);
}

int main()
{

    // pa2m_nuevo_grupo("Pruebas lectura Archivo Nulo");
    // dadoUnSalonNull_siLeoUnArchivoNull_elSalonSigueSiendoNull();

    // pa2m_nuevo_grupo("Pruebas lectura Archivo que no existe");
    // dadoUnSalonNull_siLeoUnArchivoNoExistente_elSalonSigueSiendoNull();

    // pa2m_nuevo_grupo("Pruebas lectura Archivo que existe, pero está vacío");
    // dadoUnSalonNull_siLeoUnArchivoExistentePeroVacio_elSalonSigueSiendoNull();

    // pa2m_nuevo_grupo("Pruebas lectura Archivo que existe, pero tiene pokemones sin entrenador");
    // dadoUnSalonNull_siLeoUnArchivoExistenteConPokemonesSinEntrenador_elSalonSigueSiendoNull();

    // pa2m_nuevo_grupo("Pruebas lectura Archivo que existe, pero tiene entrenador sin pokemones");
    // dadoUnSalonNull_siLeoUnArchivoExistenteConEntrenadorSinPokemones_elSalonSigueSiendoNull();

    // pa2m_nuevo_grupo("Pruebas lectura Archivo que existe, pero tiene entrenadores repetidos");
    // dadoUnSalonNull_siLeoUnArchivoExistenteConEntrenadoresRepetidos_elSalonSigueSiendoNull();

    // pa2m_nuevo_grupo("Pruebas lectura Archivo valido");
    // dadoUnSalonNull_siLeoUnArchivoValido_SeCreaUnSalonDeFormaCorrecta();

    // pa2m_nuevo_grupo("Pruebas Guardar Archivo Nulo");
    // dadoUnSalonConEntrenadores_siGuardoAUnArchivoNull_elArchivoNoSeGuarda();

    // pa2m_nuevo_grupo("Pruebas Guardar Archivo Nombre Invalido");
    // dadoUnSalonConEntrenadores_siGuardoAUnArchivoConUnPathInvalido_elArchivoNoSeGuarda();

    // pa2m_nuevo_grupo("Pruebas Guardar Archivo en ubicacion válida");
    // dadoUnSalonConEntrenadores_siGuardoAUnArchivoConUnPathValido_elArchivoSeGuardaCorrectamente();

    // pa2m_nuevo_grupo("Pruebas Guardar Archivo en ubicación válida, pero con salon NULL");
    // dadoUnSalonNull_siGuardoAUnArchivoConUnPathValido_NoPermiteGuardarPorqueElSalonEsNull();

    // pa2m_nuevo_grupo("Pruebas Agregar Entrenador a un salon NULL");
    // dadoUnSalonNull_siAgregoUnEntrenador_NoPermiteAgregarPorqueElSalonEsNull();

    // pa2m_nuevo_grupo("Pruebas Agregar Entrenador NULL a un salon");
    // dadoUnSalon_siAgregoUnEntrenadorNull_NoPermiteAgregarPorqueElEntrenadorEsNull();

    // pa2m_nuevo_grupo("Pruebas Agregar Entrenador sin pokemones a un salon e intentar guardar salon");
    // dadoUnSalon_siAgregoUnEntrenadorSinPokemonesYSolicitoGuardarSalon_NoPermiteGuardarPorqueElEntrenadorDebeTenerAlMenosUnPokemon();

    // pa2m_nuevo_grupo("Pruebas Agregar Entrenador con pokemones a un salon e intentar guardar salon");
    // dadoUnSalon_siAgregoUnEntrenadorConPokemonesYSolicitoGuardarSalon_permiteGuardarCorrectamente();

    // pa2m_nuevo_grupo("Pruebas Filtrar Entrenador en salon NULL");
    // dadoUnSalonNull_SiSolicitoFiltrarEntrenadores_NoPermiteFiltrarPorqueElSalonEsNull();

    // pa2m_nuevo_grupo("Pruebas Filtrar Entrenador en salon con un criterio que no cumple ningun entrenador");
    // dadoUnSalon_SiSolicitoFiltrarEntrenadoresYNoEncuentraResultados_permiteFiltrarCorrectamente();

    // pa2m_nuevo_grupo("Pruebas Filtrar Entrenador en salon con distintos criterios");
    // dadoUnSalon_SiSolicitoFiltrarEntrenadoresConDistintosCriterios_permiteFiltrarCorrectamente();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES en salon NULL");
    // dadoUnSalonNull_SiSolicitoEjecutarComandoEntrenadores_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES mal escrito en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoEntrenadoresMalEscrito_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoEntrenadores_PermiteEjecutarComandoCorrectamente();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES:victorias en salon NULL");
    // dadoUnSalonNull_SiSolicitoEjecutarComandoEntrenadoresVictorias_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES:victorias mal escrito en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoEntrenadoresVictoriasMalEscrito_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES:victorias en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoEntrenadoresVictorias_PermiteEjecutarComandoCorrectamente();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES:pokemon en salon NULL");
    // dadoUnSalonNull_SiSolicitoEjecutarComandoEntrenadoresPokemon_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES:pokemon mal escrito en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoEntrenadoresPokemonMalEscrito_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos ENTRENADORES:pokemon en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoEntrenadoresPokemon_PermiteEjecutarComandoCorrectamente();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos EQUIPO: en salon NULL");
    // dadoUnSalonNull_SiSolicitoEjecutarComandoEquipo_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos EQUIPO: mal escrito en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoEquipoMalEscrito_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos EQUIPO: en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoEquipo_PermiteEjecutarComandoCorrectamente();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos REGLAS: en salon NULL");
    // dadoUnSalonNull_SiSolicitoEjecutarComandoReglas_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos REGLAS: mal escrito en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoReglasMalEscrito_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos REGLAS: en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoReglas_PermiteEjecutarComandoCorrectamente();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos AGREGAR_POKEMON: en salon NULL");
    // dadoUnSalonNull_SiSolicitoEjecutarComandoAgregarPokemon_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos AGREGAR_POKEMON: mal escrito en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoAgregarPokemonMalEscrito_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos AGREGAR_POKEMON: en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoAgregarPokemon_PermiteEjecutarComandoCorrectamente();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos QUITAR_POKEMON: en salon NULL");
    // dadoUnSalonNull_SiSolicitoEjecutarComandoQuitarPokemon_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos QUITAR_POKEMON: mal escrito en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoQuitarPokemonMalEscrito_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos QUITAR_POKEMON: en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoQuitarPokemon_PermiteEjecutarComandoCorrectamente();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos GUARDAR: en salon NULL");
    // dadoUnSalonNull_SiSolicitoEjecutarComandoGuardar_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos GUARDAR: mal escrito en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoGuardarMalEscrito_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos GUARDAR: en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoGuardar_PermiteEjecutarComandoCorrectamente();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos COMPARAR: en salon NULL");
    // dadoUnSalonNull_SiSolicitoEjecutarComandoComparar_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos COMPARAR: mal escrito en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoCompararMalEscrito_NoPermiteEjecutarComando();

    // pa2m_nuevo_grupo("Pruebas Ejecutar Comandos COMPARAR: (clásico) en salon");
    // dadoUnSalon_SiSolicitoEjecutarComandoComparar_PermiteEjecutarComandoCorrectamente();

    // pa2m_nuevo_grupo("Pruebas Lectura y escritura Archivos con edicion de equipos");
    // dadoUnSalonConEntrenadores_siModificoElSalonYGuardoAUnArchivoConUnPathValido_elArchivoSeGuardaCorrectamente();

    // pa2m_nuevo_grupo("Pruebas Lectura y escritura Archivos con edicion de equipos CHANUTRON version");
    // dadoUnSalonConEntrenadores_SiEliminoYAgregoEntrenadoresYPokemones_LosCambiosSeReflejanCorrectamenteEnElSalonYEnLosArchivos();

    // pa2m_nuevo_grupo("Pruebas Agregar y eliminar pokemones en salon");
    // dadoUnSalonConEntrenadores_siAgregoYQuitoPokemones_elSalonSeActualizaDeFormaCorrecta();

    // // pruebasConcatPokemon();
    // // pruebasConcatEntrenador();
    // // pruebasConcatEntrenadorSinVictorias();

    pa2m_nuevo_grupo("Pruebas Concatenar Strings con un Vector dinámico NULL");
    dadoUnVectorDinamicoNull_SiSolicitoConcatenarLosStrings_NoPermiteConcatenar();

    pa2m_nuevo_grupo("Pruebas Concatenar Strings con un Vector dinámico");
    dadoUnVectorDinamicoDeStrings_SiSolicitoConcatenarLosStrings_LosStringsSeConcatenanCorrectamente();

    return pa2m_mostrar_reporte();
}
