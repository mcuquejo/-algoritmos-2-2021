#include <stdlib.h>

int main(){
    char vector1[6];
    char* vector2 = malloc(6);

    if (vector2==NULL) {
        return -1;
    }

    vector1[51] = 1;

    vector2[6] = 1;
    *(vector2+1) = 1;

    free(vector2);

    return 0;
}