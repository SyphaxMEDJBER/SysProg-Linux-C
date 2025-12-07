#include "../include/tp1.h"

int main() {

    int nb;
    com *tab = file2TabCom("data1.txt", &nb);

    printf("Nb commandes : %d\n", nb);

    for (int i = 0; i < nb; i++) {
        afficherArgv(tab[i].argv);
        printf("\n");
    }

    return 0;
}
