#include "../include/tp2.h"

void execFileBatchRapport(char *file) {

    FILE *f = fopen(file, "r");            // Ouverture du fichier de commandes
    if (!f) {
        perror("fopen");                   // Erreur si ouverture impossible
        return;
    }

    char ligne[256];                       // Buffer pour lire chaque ligne
    int pids[100];                         // Tableau des PID lancés
    int actif[100];                        // État : 1 = actif, 0 = terminé
    int nb = 0;                            // Nombre total de commandes

    while (fgets(ligne, sizeof(ligne), f) != NULL) {   // Lecture ligne par ligne

        char *argv[10];                    // Tableau argv temporaire
        int i = 0;
        char *token = strtok(ligne, " \t\n"); // Découpe des arguments

        while (token) {                    // Construction du argv[]
            argv[i++] = token;
            token = strtok(NULL, " \t\n");
        }
        argv[i] = NULL;                    // Fin de tableau argv

        int pid = fork();                  // Création du processus

        if (pid == 0) {                    // --- PROCESSUS FILS ---
            execvp(argv[0], argv);         // Exécution
            perror("exec");
            exit(1);
        }

        pids[nb] = pid;                    // Enregistre le PID
        actif[nb] = 1;                     // Marque comme actif
        nb++;
    }

    fclose(f);                              // Fermeture du fichier

    int restants = nb;                      // Commandes encore en cours
    int status;

    while (restants > 0) {                  // Tant qu'il reste des processus actifs

        printf("=== Rapport ===\n");

        for (int i = 0; i < nb; i++) {
            if (actif[i] == 0) continue;    // Ignore ceux déjà terminés

            int ret = waitpid(pids[i], &status, WNOHANG); // Vérifie sans bloquer

            if (ret == 0) {                 // Process encore actif
                printf("PID %d : en cours\n", pids[i]);
            }
            else {                           // Process terminé
                printf("PID %d : terminé\n", pids[i]);
                actif[i] = 0;
                restants--;                 // Un de moins à surveiller
            }
        }

        sleep(1);                            // Rapport toutes les 1 seconde
    }

    printf("FIN\n");                         // Tous les processus sont terminés
}
