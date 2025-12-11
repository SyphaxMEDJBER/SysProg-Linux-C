#include "../include/tp3.h"

int main(int argc, char *argv[]) {

    if (argc == 2) {
        int n = NbFichier(argv[1]);
        printf("%d\n", n);   // afficher le résultat
        return 0;
    }

    return 0;
}
