#include "util.h"
#include <string.h>

#define TAM_POS_CORTE_PTR 1
#define TAM_NUEVA_POS 1

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
    printf("Tamaño vector dinamico = %zu\n", tam  + TAM_POS_CORTE_PTR + TAM_NUEVA_POS);

    if (!aux_ptr)
        return NULL;

    //void** aux_aux_ptr = (void**)aux_ptr;

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
    size_t tam = hasta - desde + 2;
    // printf("Tamaño malloc del string: %zu\n", (tam) * sizeof(char));
    // printf("texto: %s\n", texto);
    printf("valores desde: %zu, hasta: %zu, tam: %zu\n", desde, hasta, tam);
    char* duplicado = calloc(tam, sizeof(char));
    if(!duplicado)
        return NULL;

    // printf("texto mas desde: %s", texto + desde);
    printf("tam strncopy: %zu\n", hasta - desde + 1);
    strncpy(duplicado, texto + desde, hasta - desde + 1);
    printf("duplicado: \'%s\'\n", duplicado);
    return duplicado;
}

/**
 * Divide un string cada vez que encuentra el separador dado y devuelve un
 * vector de strings.
 */
char** split(const char* str, char separador){
    if (!str)
        return NULL;
    if (strlen(str) == 0)
        return NULL;
    printf("el string completo es: \'%s\'\n",str);
    //primero inicializo la posicion actual del string arranco al principio de la linea.
    size_t pos_actual = 0;
    //inicializo la cantidad de elementos que hay en el string original.
    // Como minimo, hay un elemento, que es el que se analiza. (lo dejo en cero por ahora, ya que podria entrar en conflicto con el ultimo vtradd luego del bucle)
    size_t cant_elem = 0;

    //me armo un array que contendr un vector dinamico con los strings spliteados. Por ahora apunta a NULL.
    char** split_str = NULL;

    //voy a recorrer el string hasta su posicion final
    printf("pos_actual: %zu\n", pos_actual);
    for (size_t i = 0; i < strlen(str); i++) {
        printf("i: %zu-----------------------------------------------------\n", i);
        //si encuentro el caracter de split, ejecuto las siguientes instrucciones:
        if(str[i] == separador) {
            //aumento la cantidad de elementos. Por cada separador encontrado, siempre habrá un elemento más.
            cant_elem++;

            //creo una referencia al string cortado, la duplico en memoria.
            printf("duplicado dentro del bucle\n");
            char* texto_cortado = duplicar_texto_hasta(str, pos_actual, i-1);
            //si falló la duplicación, debo cortar el proceso. Antes, voy a liberar el resto de textos cortados del vector y, luego, al vector.
            if (!texto_cortado) {
                //para ello, recorro cada elemento del vector y voy liberando.
                for (size_t j = 0; j < vtrlen(split_str); j++) {
                    free(split_str[j]);
                }
                //una vez que termine de eliminar los elementos, libero el vector y retorno NULL.
                free(split_str);
                return NULL;
            }

            //si no falló, puedo agregar un elemento nuevo al vector dinámico, que contendrá el puntero al texto cortado.
            void** resultado = vtradd(split_str, texto_cortado);

            //si falla el proceso de agregar el elemento, debo liberar al vector dinamico, junto con todos los elementos que hayan sido agregados correctamente.
            if (!resultado) {
                for (size_t j = 0; j < vtrlen(split_str); j++) {
                    free(split_str[j]);
                }
                    free(split_str);
                    return NULL;
            }

            //no se si es necesario realizar esto, pero el puntero que devuelve el vtradd, es void**. Lo casteo a char**
            split_str = (char**)resultado;

            //una vez que terminé de procesar el string, ahora tengo que actualizar la posicion actual, se debe mover al siguiente char luego del separador.
            //esto solo se debe realizar, mientras que la posicion actualizada, permanezca dentro del string a procesar.
            if (i < strlen(str) -1) {
                pos_actual = i + 1;
            } else if ( i == strlen(str) - 1) {
                pos_actual = i;
            }
            printf("pos_actual: %zu\n", pos_actual);
        }
    }

    //siempre que se encontrara un separador, se cortaba todo lo anterior al separador y se armaba un string.
    //Si tenemos 1;2;3. el primer separador va de posicion 0 a pos 0. El segundo separador, va de pos 2 a pos 2.
    // Queda como excedente el 3, que está en posicion 4. Por ello, agregamos un elemento más, que lo va a contener.
    cant_elem++;

    printf("duplicado fuera del bucle\n");
    char* texto_cortado = NULL;
    if(pos_actual < strlen(str) - 1 || str[pos_actual] != separador) {
        //creamos una nueva referencia a una posicion que contiene el texto restante.
        texto_cortado = duplicar_texto_hasta(str, pos_actual, strlen(str) - 1);
        if (!texto_cortado) {
            for (size_t j = 0; j < vtrlen(split_str); j++) {
                free(split_str[j]);
            }
            free(split_str);
            return NULL;
        }
    } else {
        //creamos una nueva referencia a una posicion que contiene el texto restante.
        texto_cortado = duplicar_texto_hasta("", 0, 0);
        if (!texto_cortado) {
            for (size_t j = 0; j < vtrlen(split_str); j++) {
                free(split_str[j]);
            }
            free(split_str);
            return NULL;
        }
    }

    void** resultado = vtradd(split_str, texto_cortado);
    if (!resultado) {
        for (size_t j = 0; j < vtrlen(split_str); j++) {
            free(split_str[j]);
        }
        free(split_str);
        return NULL;
    }
    split_str = (char**)resultado;

    size_t pos = 0;
    printf("deberia mostrarme algo\n");
    while (split_str[pos]) {
        printf("%s\n", split_str[pos]);
        pos++;
    }
    printf("fin deberia mostrarme algo\n");
    // printf("%s cant elem: %zu \n", str + pos_actual, cant_elem);
    // printf("\n");
    return split_str;
}

char* fgets_alloc(FILE* archivo){
    return NULL;
}

void fclosen(FILE* archivo){

}
