#include "../include/tp1.h"

void execFileBatchCom(char *file) {

    int nb;
    com *tab = file2TabCom(file, &nb);

    int status;
    int total = 0;

    //  LANCER TOUTES LES COMMANDES EN PARALLÈLE
    for (int i = 0; i < nb; i++) {

        time(&tab[i].debut);
        tab[i].statut = 1;

        int pid = fork();
        tab[i].pid = pid;

        if (pid == 0) {
            execvp(tab[i].argv[0], tab[i].argv);
            perror("exec");
            exit(254);
        }
    }

    //  À CHAQUE FIN DE COMMANDE → RAPPORT
    int restant = nb;      // combien il reste de commandes

    while (restant > 0) {

        int pid = wait(&status);     // attend 1 commande
        time_t fin; 
        time(&fin);

        // retrouver quelle commande est terminée
        for (int i = 0; i < nb; i++) {

            if (tab[i].pid == pid) {

                tab[i].statut = 0;
                tab[i].retour = WEXITSTATUS(status);
                tab[i].fin = fin;

                long duree = tab[i].fin - tab[i].debut;
                total += duree;

                // RAPPORT IMMÉDIAT
                printf("%s : %d %d %ld %ld %ld\n",
                       tab[i].argv[0],
                       tab[i].pid,
                       tab[i].retour,
                       tab[i].debut,
                       tab[i].fin,
                       duree);

                restant--;
                break;
            }
        }
    }

    //  RAPPORT FINAL
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

    printf("temps total : %d\n", total);
}
