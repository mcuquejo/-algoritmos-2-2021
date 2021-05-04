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
    void** aux_ptr = realloc(ptr, (tam  + TAM_POS_CORTE_PTR +  TAM_NUEVA_POS) * sizeof(ptr));

    if (!aux_ptr) {
        return NULL;
    }

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

    size_t pos_actual = 0;
    size_t cant_elem = 0;

    char** split_str = NULL;

    for (size_t i = 0; i < strlen(str); i++) {
        if(str[i] == separador) {
            cant_elem++;

            char* texto_cortado = duplicar_texto_hasta(str, pos_actual, i-1);
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

            if (i < strlen(str)) {
                pos_actual = i + 1;
            }
        }
    }

    cant_elem++;
    char* texto_cortado = NULL;

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
    size_t bytes_leidos= 0;
    size_t tam_buffer = TAM_BUFFER_INI;

    char* buffer = malloc(sizeof(char) * tam_buffer);
    if (!buffer)
        return NULL;

    while (fgets(buffer + bytes_leidos, (int)(tam_buffer - bytes_leidos), archivo)){
        size_t leido = strlen(buffer + bytes_leidos);
        if (leido > 0 && *(buffer + bytes_leidos + leido - 1) == '\n') {
            return buffer;
        }
        else {
            char* auxiliar = realloc(buffer, sizeof(char) * tam_buffer + TAM_BUFFER_INI);
            if(!auxiliar) {
                free(buffer);
                return NULL;
            }
            buffer = auxiliar;
            tam_buffer += TAM_BUFFER_INI;
        }

        bytes_leidos += leido;
    }

    if(bytes_leidos == 0) {
        free(buffer);
        return NULL;
    }

    return buffer;
}

void fclosen(FILE* archivo){
    if(archivo){
        fclose(archivo);
    }
}
