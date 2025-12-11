#include "../include/test.h"

int minutes = 0;                        // Compteur de minutes écoulées

void h1(int s) {
    printf("5 secondes\n");             // Message pour SIGUSR1
    fflush(stdout);
}

void h2(int s) {
    minutes++;                           // Incrémente le nombre de minutes
    printf("%d minute\n", minutes);      // Affiche le compteur
    fflush(stdout);
}

void exo2_signaux() {

    signal(SIGUSR1, h1);                 // Associe SIGUSR1 → h1
    signal(SIGUSR2, h2);                 // Associe SIGUSR2 → h2

    int pid1 = fork();                   // Premier fils
    if (pid1 == 0) {
        while (1) {
            sleep(5);                    // Attend 5 secondes
            kill(getppid(), SIGUSR1);    // Envoie SIGUSR1 au père
        }
    }

    int pid2 = fork();                   // Deuxième fils
    if (pid2 == 0) {
        while (1) {
            sleep(60);                   // Attend 60 secondes
            kill(getppid(), SIGUSR2);    // Envoie SIGUSR2 au père
        }
    }

    for (int i = 0; i < 300; i++) {      // Boucle de 300 secondes = 5 minutes
        printf("bonjour\n");             // Affiche chaque seconde
        fflush(stdout);
        sleep(1);
    }

    kill(pid1, SIGKILL);                 // Tue le premier fils
    kill(pid2, SIGKILL);                 // Tue le deuxième fils
}
