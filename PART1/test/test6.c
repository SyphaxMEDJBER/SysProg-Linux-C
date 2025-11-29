#include "../include/tp1.h"

int main() {
    int nb;
    char ***tab = file2TabArgv("data.txt", &nb);

    printf("Nb commandes : %d\n", nb);

    for (int i = 0; i < nb; i++) {
        afficherArgv(tab[i]);   // ta fonction de l'exo 2
        printf("\n");
    }

    return 0;
}
