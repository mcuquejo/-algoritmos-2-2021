#include "util.h"
#include <string.h>

#define TAM_POS_CORTE_PTR 1
#define TAM_NUEVA_POS 1
#define TAM_STRING_VACIO 1
#define TAM_BUFFER_INI 512


size_t vtrlen(void* ptr){
    if (!ptr)
        return 0;

    void** ptr_aux = (void**)ptr;
    size_t cant = 0;
    size_t pos = 0;

    while (ptr_aux[pos]) {
        cant++;
        pos++;
    }
    return cant;
}

void* vtradd(void* ptr, void* item){
    size_t tam = vtrlen(ptr);
    //si vtrlen devuelve cero, me va a devolver un puntero de tamaño 2 (uno para el nuevo valor, otro para el NULL de corte)
    void** aux_ptr = realloc(ptr, (tam  + TAM_POS_CORTE_PTR +  TAM_NUEVA_POS) * sizeof(ptr));

    if (!aux_ptr)
        return NULL;

    aux_ptr[tam] = item;
    aux_ptr[tam + TAM_NUEVA_POS] = NULL;

    ptr = (void*)aux_ptr;

    return ptr;
}

void vtrfree(void* ptr){
    void** ptr_aux = (void**)ptr;
    for (size_t i = 0; i < vtrlen(ptr); i++) {
        free(ptr_aux[i]);
    }
    free(ptr);
}

char* duplicar_texto_hasta(const char* texto, size_t desde, size_t hasta) {
    size_t tam = hasta - desde + TAM_POS_CORTE_PTR +  TAM_NUEVA_POS;

    char* duplicado = calloc(tam, sizeof(char));
    if(!duplicado)
        return NULL;

    strncpy(duplicado, texto + desde, hasta - desde + 1);
    return duplicado;
}



char** split(const char* str, char separador){
    if (!str)
        return NULL;
    if (strlen(str) == 0)
        return NULL;

    //primero inicializo la posicion actual del string arranco al principio de la linea.
    size_t pos_actual = 0;
    //inicializo la cantidad de elementos que hay en el string original.
    // Como minimo, hay un elemento, que es el que se analiza. (lo dejo en cero por ahora, ya que podria entrar en conflicto con el ultimo vtradd luego del bucle)
    size_t cant_elem = 0;

    //me armo un array que contendr un vector dinamico con los strings spliteados. Por ahora apunta a NULL.
    char** split_str = NULL;

    //voy a recorrer el string hasta su posicion final
    for (size_t i = 0; i < strlen(str); i++) {
        //si encuentro el caracter de split, ejecuto las siguientes instrucciones:
        if(str[i] == separador) {
            //aumento la cantidad de elementos. Por cada separador encontrado, siempre habrá un elemento más.
            cant_elem++;

            //creo una referencia al string cortado, la duplico en memoria.
            char* texto_cortado = duplicar_texto_hasta(str, pos_actual, i-1);
            //si falló la duplicación, debo cortar el proceso. Antes, voy a liberar el resto de textos cortados del vector y, luego, al vector.
            if (!texto_cortado) {
                vtrfree(split_str);
                return NULL;
            }

            //si no falló, puedo agregar un elemento nuevo al vector dinámico, que contendrá el puntero al texto cortado.
            void** resultado = vtradd(split_str, texto_cortado);

            //si falla el proceso de agregar el elemento, debo liberar al vector dinamico, junto con todos los elementos que hayan sido agregados correctamente.
            if (!resultado) {
                vtrfree(split_str);
                return NULL;
            }

            //no se si es necesario realizar esto, pero el puntero que devuelve el vtradd, es void**. Lo casteo a char**
            split_str = (char**)resultado;

            //una vez que terminé de procesar el string, ahora tengo que actualizar la posicion actual, se debe mover al siguiente char luego del separador.
            //esto solo se debe realizar, mientras que la posicion actualizada, permanezca dentro del string a procesar.
            //si la posicion queda por fuera, es porque el ultimo elemento era un separador.
            if (i < strlen(str)) {
                pos_actual = i + 1;
            }
        }
    }

    //siempre que se encontrara un separador, se cortaba todo lo anterior al separador y se armaba un string.
    //Si tenemos 1;2;3. el primer separador va de posicion 0 a pos 0. El segundo separador, va de pos 2 a pos 2.
    // Queda como excedente el 3, que está en posicion 4. Por ello, agregamos un elemento más, que lo va a contener.
    cant_elem++;

    char* texto_cortado = NULL;


    //creamos una nueva referencia a una posicion que contiene el texto restante.
    //Si estamos parados sobre un separador, debemos agregar un nuevo elemento vacío.
    // Sino, agregamos el pedazo de string restante
    const char* str_aux = (str[pos_actual] == separador) ? "" : str;
    size_t pos_actual_aux = (str[pos_actual] == separador) ? 0 : pos_actual;
    texto_cortado = duplicar_texto_hasta(str_aux, pos_actual_aux, strlen(str_aux) - 1);

    if (!texto_cortado) {
        vtrfree(split_str);
        return NULL;
    }

    void** resultado = vtradd(split_str, texto_cortado);
    if (!resultado) {
        vtrfree(split_str);
        return NULL;
    }
    split_str = (char**)resultado;

    return split_str;
}

char* fgets_alloc(FILE* archivo){
    //bytes leidos de la linea del archivo
    size_t bytes_leidos= 0;

    //tamanio del buffer en donde voy a guardar la linea del archivo
    size_t tam_buffer = TAM_BUFFER_INI;

    //reservo memoria para el buffer que estoy leyendo
    char* buffer = malloc(sizeof(char) * tam_buffer);

    //si no pudo reservar, retorno NULL
    if (!buffer)
        return NULL;

    //mientras que pueda leer la linea, continuo. le paso el buffer mas la cantidad de bytes leidos,
    //le pido que lea el buffer menos la cantidad de bytes leidos, y por ultimo
    //le paso el archivo abierto
    while (fgets(buffer + bytes_leidos, (int)(tam_buffer - bytes_leidos), archivo)){
        //me fijo cuantos bytes lei, sumando la longitud del buffer mas la cantidad de bytes que habia leido previamente.
        //este valor deberia ser 0 para el primer ciclo y se actualiza al finalizar cada ciclo.
        size_t leido = strlen(buffer + bytes_leidos);

        //si lei algo y la anteultima posicion es un enter, retorno el buffer, porque llegué al fin de la linea
        if (leido > 0 && *(buffer + bytes_leidos + leido - 1) == '\n') {
            return buffer;
        }
        //si llené el buffer y la anteúltima posición no es un enter, tengo que seguir leyendo, así que duplico el buffer
        else {
            char* auxiliar = realloc(buffer, sizeof(char) * tam_buffer + TAM_BUFFER_INI);

            //si no pude duplicar el buffer, libero lo que tenia leido y retorno NULL
            if(!auxiliar) {
                free(buffer);
                return NULL;
            }

            //si pude duplicar el tamaño, se lo asigno al buffer
            buffer = auxiliar;

            //actualizo la variable del tamaño del buffer
            tam_buffer += TAM_BUFFER_INI;
        }


        //actualizo la cantidad de bytes leidos.
        bytes_leidos += leido;
    }

    //No pude leer nada, EOF
    if(bytes_leidos == 0) {
        free(buffer);
        return NULL;
    }

    //llegue a fin de archivo pero pude leer algo
    return buffer;
}

void fclosen(FILE* archivo){
    if(archivo){
        fclose(archivo);
    }
}
