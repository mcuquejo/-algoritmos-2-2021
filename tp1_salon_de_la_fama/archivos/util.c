#include "util.h"
#include <string.h>

#define TAM_POS_CORTE_PTR 1
#define TAM_NUEVA_POS 1
#define TAM_STRING_VACIO 1
#define TAM_BUFFER_INI 512


size_t vtrlen(void* ptr){
    //si me pasan un puntero NULL, retorno 0.
    if (!ptr)
        return 0;

    //sino, me creo un auxiliar de tipo void**, porque se que voy a recibir un vector dinamico para recorrer..
    void** ptr_aux = (void**)ptr;

    size_t cant = 0;
    size_t pos = 0;

    //mientras el contenido del vector no sea NULL, voy acumulando cant
    while (ptr_aux[pos]) {
        cant++;
        pos++;
    }
    //retorno la cant de elementos acumulada
    return cant;
}

void* vtradd(void* ptr, void* item){
    //primero me fijo el tamaño del puntero.
    size_t tam = vtrlen(ptr);

    //me creo un puntero auxiliar del tamaño del puntero original, mas dos posiciones. Una para el item nuevo, y otra para el elemento NULL
    // que vtrlen no tiene en cuenta al momento de dar el tamaño del vector dinamico.
    void** aux_ptr = realloc(ptr, (tam  + TAM_POS_CORTE_PTR +  TAM_NUEVA_POS) * sizeof(ptr));

    //si falla el realloc, retorno NULL.
    if (!aux_ptr)
        return NULL;

    //en la nueva posicion creada, agrego el item
    aux_ptr[tam] = item;

    //ahora asigno al ultimo elemento, el valor NULL.
    aux_ptr[tam + TAM_NUEVA_POS] = NULL;

    //apunto al puntero original a la nueva direccion de memoria.
    ptr = (void*)aux_ptr;

    //retorno el puntero
    return ptr;
}

void vtrfree(void* ptr){

    //me creo un auxiliar para recorrer el vector dinamico.
    void** ptr_aux = (void**)ptr;

    //recorro el puntero y voy liberando su contenido. Si el puntero fuera null, el ciclo no se ejecuta porque vtrlen == 0
    for (size_t i = 0; i < vtrlen(ptr); i++) {
        free(ptr_aux[i]);
    }
    //una vez liberado el contenido del vector dinamico, libero el puntero al vector.
    free(ptr);
}

char* duplicar_texto_hasta(const char* texto, size_t desde, size_t hasta) {
    //me fijo el tamaño
    size_t tam = hasta - desde + TAM_POS_CORTE_PTR +  TAM_NUEVA_POS;

    //reservo con calloc memoria por el tamaño del string a copiar. Esto es para que se inicialice en 0 cada elemento.
    char* duplicado = calloc(tam, sizeof(char));

    //si falla el calloc, retorno NULL
    if(!duplicado)
        return NULL;

    //sino, copio el texto desde la posicion "desde", hasta la posicion hasta - desde + 1. La última posicion que se reservó, debería quedar con un 0.
    strncpy(duplicado, texto + desde, hasta - desde + 1);

    //retorno el string duplicado
    return duplicado;
}



char** split(const char* str, char separador){
    //si el puntero es nulo, retorno NULL
    if (!str)
        return NULL;
    //si el largo del string es 0, retorno NULL
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
                free(texto_cortado);
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
        free(texto_cortado);
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
