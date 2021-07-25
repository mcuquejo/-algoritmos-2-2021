#include <stdlib.h>

char* strdup_c99(const char* string){
  if(!string)
    return NULL;
  char* copia = malloc(strlen(string) + 1);
  strcpy(copia, string);
  return copia;
}