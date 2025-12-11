#include "../include/test.h"

void com1_puis_com2_et_com3(char **com1, char **com2, char **com3) {

    int st;                                 // Statut pour wait()

    int pid1 = fork();                      // Lance la première commande
    if (pid1 == 0) {                        // --- FILS 1 ---
        execvp(com1[0], com1);              // Exécution de com1
        exit(1);                            // En cas d'échec de execvp
    }

    wait(&st);                              // Attend la fin de com1

    int pid2 = fork();                      // Lance la deuxième commande
    if (pid2 == 0) {                        // --- FILS 2 ---
        execvp(com2[0], com2);              // Exécution de com2
        exit(1);
    }

    int pid3 = fork();                      // Lance la troisième commande
    if (pid3 == 0) {                        // --- FILS 3 ---
        execvp(com3[0], com3);              // Exécution de com3
        exit(1);
    }

    wait(&st);                              // Attend la fin de com2
    wait(&st);                              // Attend la fin de com3
}
