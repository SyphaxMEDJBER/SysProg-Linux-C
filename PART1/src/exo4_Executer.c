#include "../include/tp1.h"

int executer(char **argv, int *pidcom) {

    int status;                     // Contiendra le statut de fin du fils
    int pid = fork();               // Création du processus fils

    if (pid == 0) {                 // --- PROCESSUS FILS ---
        execvp(argv[0], argv);      // Remplace le programme courant par la commande
        perror("exec");             // Si exec échoue, on arrive ici
        exit(254);                  // Code d'erreur conventionnel pour exec raté
    }

    if (pid < 0) {                  // --- ERREUR DE FORK ---
        perror("fork");             // Impossible de créer un processus
        return 255;                 // Valeur d'échec pour fork
    }

    *pidcom = pid;                  // Enregistrer le PID du fils dans pidcom

    wait(&status);                  // --- PROCESSUS PÈRE ---
                                   // Attend la fin du processus fils

    return WEXITSTATUS(status);     // Retourne le code de retour réel du fils
}
