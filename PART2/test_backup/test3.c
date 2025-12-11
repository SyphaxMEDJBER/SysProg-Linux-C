#include "../include/tp2.h"

int main(int argc, char *argv[]) {

    if (argc < 3) exit(1);

    int n = atoi(argv[1]);
    char **cmd = &argv[2];//l'adresse de premier element de la commande 

    timeout_run(n, cmd);

    return 0;
}
