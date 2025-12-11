#include "../include/tp1.h"
#include <time.h>

void execFileBatchLimite(char *file, int N) {

    int nb;// Nombre total de commandes
    com *tab = file2TabCom(file, &nb);  // Chargement des commandes

    int en_cours = 0;  // Nombre de processus actuellement actifs
    int lance = 0;    // Nombre de commandes déjà lancées
    int total = 0;    // Temps total cumulé
    int status;     // Statut pour wait()

    // --- LANCER JUSQU'À N COMMANDES AU DÉBUT ---
    while (lance < nb && en_cours < N) {   // Tant qu'il reste des commandes et que la limite N n'est pas atteinte

        time(&tab[lance].debut); // Timestamp début
        tab[lance].statut = 1;  // En cours d'exécution

        int pid = fork();   // Création d'un fils
        tab[lance].pid = pid;// Associer le PID à la commande

        if (pid == 0) {   // --- PROCESSUS FILS ---
            execvp(tab[lance].argv[0], tab[lance].argv); // Exécution de la commande
            perror("exec"); // Si exec échoue
            exit(254);
        }

        en_cours++;  // On a un processus de plus en cours
        lance++;    // Une commande de plus lancée
    }

    // --- BOUCLE PRINCIPALE : TRAITER CHAQUE FIN DE PROCESSUS ---
    while (en_cours > 0) {    // Tant qu'il reste des commandes à terminer

        int pidf = wait(&status); // Attend la fin d'un seul processus
        time_t fin;
        time(&fin); // Timestamp de fin
        en_cours--;   // Un processus vient de se terminer

        // --- IDENTIFIER LA COMMANDE TERMINÉE ---
        for (int i = 0; i < nb; i++) {

            if (tab[i].pid == pidf) {  // On retrouve la commande par PID

                tab[i].statut = 0; // Commande terminée
                tab[i].retour = WEXITSTATUS(status); // Code de retour
                tab[i].fin = fin; // Timestamp fin

                long duree = tab[i].fin - tab[i].debut; // Durée d'exécution
                total += duree;

                // --- RAPPORT IMMÉDIAT ---
                printf("%s : %d %d %ld %ld %ld\n",
                       tab[i].argv[0],
                       tab[i].pid,
                       tab[i].retour,
                       tab[i].debut,
                       tab[i].fin,
                       duree);

                // --- LANCER UNE NOUVELLE COMMANDE SI POSSIBLE ---
                if (lance < nb) { // Il reste des commandes à lancer

                    time(&tab[lance].debut);    // Timestamp début nouvelle commande
                    tab[lance].statut = 1;

                    int pid2 = fork(); // Nouveau lancement
                    tab[lance].pid = pid2;

                    if (pid2 == 0) {   // Processus fils
                        execvp(tab[lance].argv[0], tab[lance].argv);
                        perror("exec");
                        exit(254);
                    }

                    en_cours++;    // Nouveau processus actif
                    lance++;    // Une commande de plus lancée
                }

                break;    // On sort du for, PID trouvé
            }
        }
    }

    // --- RAPPORT FINAL ---
    printf("FIN\n");

    for (int i = 0; i < nb; i++) {

        long duree = tab[i].fin - tab[i].debut; // Durée d'exécution individuelle

        printf("%s : %d %d %ld %ld %ld\n",
               tab[i].argv[0],
               tab[i].pid,
               tab[i].retour,
               tab[i].debut,
               tab[i].fin,
               duree);
    }

    printf("temps total : %d\n", total); // Temps cumulé
}
