#include "../include/tp1.h"

void execFileBatchCom(char *file) {

    int nb;  // Nombre total de commandes
    com *tab = file2TabCom(file, &nb);        // Lecture des commandes dans la structure com

    int status;  // Statut de terminaison d’un fils
    int total = 0;    // Temps total cumulé

    //  --- LANCEMENT DE TOUTES LES COMMANDES EN PARALLÈLE ---
    for (int i = 0; i < nb; i++) {

        time(&tab[i].debut);   // Enregistre l'instant du lancement
        tab[i].statut = 1;  // Commande en cours

        int pid = fork();   // Création du processus fils
        tab[i].pid = pid;  // Stocke le PID du processus associé

        if (pid == 0) {    // --- PROCESSUS FILS ---
            execvp(tab[i].argv[0], tab[i].argv); // Exécute la commande
            perror("exec");   // Si exec échoue
            exit(254);   // Code d'erreur exec
        }
    }

    //  --- TRAITEMENT DES COMMANDES TERMINÉES UNE PAR UNE ---
    int restant = nb;  // Nombre de commandes encore actives

    while (restant > 0) {

        int pid = wait(&status); // Attend qu'un fils se termine
        time_t fin; 
        time(&fin);  // Capture l’instant exact de fin

        // Recherche de la commande correspondant au PID terminé
        for (int i = 0; i < nb; i++) {

            if (tab[i].pid == pid) {          // On a trouvé la commande terminée

                tab[i].statut = 0;            // Statut = terminé
                tab[i].retour = WEXITSTATUS(status);  // Code retour réel
                tab[i].fin = fin;             // Timestamp de fin

                long duree = tab[i].fin - tab[i].debut; // Durée de la commande
                total += duree;               // Ajout au temps total

                // --- RAPPORT IMMÉDIAT ---
                printf("%s : %d %d %ld %ld %ld\n",
                       tab[i].argv[0],       // Nom de la commande
                       tab[i].pid,           // PID
                       tab[i].retour,        // Code retour
                       tab[i].debut,         // Epoch début
                       tab[i].fin,           // Epoch fin
                       duree);               // Durée

                restant--;                    // Une commande en moins à attendre
                break;
            }
        }
    }

    //  --- RAPPORT FINAL COMPLET ---
    printf("FIN\n");

    for (int i = 0; i < nb; i++) {
        long duree = tab[i].fin - tab[i].debut;

        printf("%s : %d %d %ld %ld %ld\n",
               tab[i].argv[0],
               tab[i].pid,
               tab[i].retour,
               tab[i].debut,
               tab[i].fin,
               duree);
    }

    printf("temps total : %d\n", total);  // Temps cumulé de toutes les commandes
}
