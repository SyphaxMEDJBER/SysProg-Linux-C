#include "../include/tp2.h"

static int pid_fils = -1;        // PID du processus enfant
static int tue = 0;              // Indique si le processus a été tué

void handlerALRM(int sig) {
    if (pid_fils > 0) {          // Si le fils existe encore
        kill(pid_fils, SIGKILL); // Tue le processus enfant
        tue = 1;                 // Marque qu'il a été tué
    }
}

void timeout_run(int n, char **cmd) {

    pid_fils = fork();           // Création du processus fils

    if (pid_fils == 0) {         // --- PROCESSUS FILS ---
        execvp(cmd[0], cmd);     // Exécute la commande
        perror("execvp");        // Affiche erreur si exec échoue
        exit(2);                 // Sort du fils avec erreur
    }

    signal(SIGALRM, handlerALRM); // Associe SIGALRM au handler
    alarm(n);                      // Déclenche SIGALRM dans n sec

    int status;
    wait(&status);                // Attend la fin du fils
                                  // (réveillé si SIGALRM tue le fils)

    if (tue)
        printf("Processus tué au bout de %d secondes car il n'est pas terminé.\n", n);
    else
        printf("Processus terminé\n");
}
