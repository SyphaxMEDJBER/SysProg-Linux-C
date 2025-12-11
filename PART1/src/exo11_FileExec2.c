#include "../include/tp1.h"
#include <time.h>

void execFile2(char *file) {

    int nb;                                  // Nombre total de commandes
    com *tab = file2TabCom(file, &nb);       // Lecture des commandes dans une structure com
    int status;                              // Statut de fin pour wait()
    int total = 0;                           // Accumulateur du temps total d’exécution

    for (int i = 0; i < nb; i++) {

        time(&tab[i].debut);                 // Enregistre l'instant exact de lancement
        tab[i].statut = 1;                   // 1 = commande en cours d’exécution

        int pid = fork();                    // Création du processus fils
        tab[i].pid = pid;                    // Stocke le PID associé à la commande

        if (pid == 0) {                      // --- PROCESSUS FILS ---
            execvp(tab[i].argv[0], tab[i].argv);  // Exécute la commande
            perror("exec");                  // Si exec échoue, message d’erreur
            exit(254);                       // Code d'échec exec
        }

        wait(&status);                       // --- PROCESSUS PÈRE ---
                                              // Attend la fin du fils

        tab[i].statut = 0;                   // 0 = commande terminée
        tab[i].retour = WEXITSTATUS(status); // Code de retour réel du programme exécuté
        time(&tab[i].fin);                   // Timestamp exact de fin d’exécution

        total += (tab[i].fin - tab[i].debut); // Ajout de la durée au total
    }

    printf("FIN\n");

    // Affichage du rapport pour chaque commande
    for (int i = 0; i < nb; i++) {
        long duree = tab[i].fin - tab[i].debut;   // Durée d'exécution de la commande
        printf("%s : %d %d %ld %ld %ld\n",
               tab[i].argv[0],                    // Nom de la commande exécutée
               tab[i].pid,                        // PID du processus
               tab[i].retour,                     // Valeur de retour
               tab[i].debut,                      // Epoch début
               tab[i].fin,                        // Epoch fin
               duree);                            // Durée d’exécution
    }

    printf("temps total : %d\n", total);          // Temps cumulé de toutes les commandes
}
