#include "../include/tp1.h"
#include <time.h>

void execFile2(char *file) {

    int nb;
    com *tab = file2TabCom(file, &nb);
    int status;
    int total = 0;

    for (int i = 0; i < nb; i++) {

        time(&tab[i].debut);//stok l'instant precis ou la comande commence dans tab[i].debut   
        tab[i].statut = 1;//en cours

        int pid = fork();//fis execution de la com
        tab[i].pid = pid;//le proceccus qui execute la com

        if (pid == 0) {
            execvp(tab[i].argv[0], tab[i].argv);
            perror("exec");
            exit(254);
        }

        wait(&status);

        tab[i].statut = 0;
        tab[i].retour = WEXITSTATUS(status);
        time(&tab[i].fin);

        total += (tab[i].fin - tab[i].debut);
    }

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
