#include "../include/test.h"

int main() {

    char **t = Ls2TabChar(".");

    for (int i = 0; t[i] != NULL; i++) {
        printf("[%d] %s\n", i, t[i]);
        free(t[i]);            // libérer chaque chaine
    }

    free(t);                   // libérer tableau

    return 0;
}
