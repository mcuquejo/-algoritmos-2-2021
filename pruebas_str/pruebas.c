#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum tipo
{
    ROCA,
    AGUA,
    ELECTRICO,
    PLANTA,
    VENENO,
    FUEGO,
    PSIQUICO,
    TIERRA
} pokemon_tipo_t;

char *concat(char *s1, const char *s2)
{
    if (!s1) {
        s1 = calloc(1, sizeof(strlen(s2) + 1));
        strcpy(s1, s2);
        return s1;
    }

    s1 = realloc(s1, sizeof(strlen(s1) + strlen(s2) + 1));

    strcpy(s1, s2);
    return s1;
}

void pruebas_str()
{
    const char *a = "these ";
    const char *b = "strings ";
    const char *c = "are ";
    const char *d = "concatenated.";

    const char **string = calloc(4, sizeof(char *));

    string[0] = a;
    string[1] = b;
    string[2] = c;
    string[3] = d;

    for (size_t i = 0; i < 4; i++) {
        printf("%s", string[i]);
    }
    printf("\n");

    char *stringer = NULL;
    for (size_t i = 0; i < 4; i++) {
        concat(stringer, string[i]);
    }

    printf("%s\n", stringer);

    char *str = malloc(strlen(a) + strlen(b) + strlen(c) + strlen(d) + 1);

    strcpy(str, a);
    strcat(str, b);
    strcat(str, c);
    strcat(str, d);

    printf("%s\n", str);
    free(str);
    free(stringer);
}

int main()
{
    // pruebas_str();
    srand((unsigned int)time(NULL));
    int r = rand() % 10;
    printf("%i\n", r);

    pokemon_tipo_t tipo = FUEGO;

    printf("%d\n", tipo);
    return 0;
}