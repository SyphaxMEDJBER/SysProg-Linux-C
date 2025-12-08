#include "../include/tp1.h"
#include <time.h>

void execFileBatchLimite(char *file, int N) {

    int nb;
    com *tab = file2TabCom(file, &nb);

    int en_cours = 0;     // nombre de processus actifs
    int lance = 0;        // combien de commandes lancées
    int total = 0;        // temps total
    int status;

    // Lancer jusqu'à N commandes au début
    while (lance < nb && en_cours < N) {

        time(&tab[lance].debut);
        tab[lance].statut = 1;

        int pid = fork();
        tab[lance].pid = pid;

        if (pid == 0) {
            execvp(tab[lance].argv[0], tab[lance].argv);
            perror("exec");
            exit(254);
        }

        en_cours++;
        lance++;
    }

    // Pendant qu'il reste des commandes à terminer
    while (en_cours > 0) {

        int pidf = wait(&status);   // attend UNE commande
        time_t fin;
        time(&fin);
        en_cours--;

        // retrouver laquelle vient de finir
        for (int i = 0; i < nb; i++) {

            if (tab[i].pid == pidf) {

                tab[i].statut = 0;
                tab[i].retour = WEXITSTATUS(status);
                tab[i].fin = fin;

                long duree = tab[i].fin - tab[i].debut;
                total += duree;

                // rapport immédiat :
                printf("%s : %d %d %ld %ld %ld\n",
                       tab[i].argv[0],
                       tab[i].pid,
                       tab[i].retour,
                       tab[i].debut,
                       tab[i].fin,
                       duree);

                // Lancer nouvelle commande si dispo
                if (lance < nb) {

                    time(&tab[lance].debut);
                    tab[lance].statut = 1;

                    int pid2 = fork();
                    tab[lance].pid = pid2;

                    if (pid2 == 0) {
                        execvp(tab[lance].argv[0], tab[lance].argv);
                        perror("exec");
                        exit(254);
                    }

                    en_cours++;
                    lance++;
                }

                break;
            }
        }
    }

    // RAPPORT FINAL
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
