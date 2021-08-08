#include "pa2mm.h"
#include "src/salon.h"

bool filtrar_entrenadores_por_victorias(entrenador_t *entrenador, void *cant_victorias)
{
    if (!entrenador)
        return false;
    printf("entrenador: %s, victorias: %i\n", entrenador_obtener_nombre(entrenador), entrenador_obtener_victorias(entrenador));
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

    return pa2m_mostrar_reporte();
}
