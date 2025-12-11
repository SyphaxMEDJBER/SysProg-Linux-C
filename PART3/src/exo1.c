#include "../include/tp3.h"                     // inclut les fonctions et types nécessaires

/* ---------------------------------------------------------------------- */
/* Init : crée base.dat contenant 4 entiers = 100 */
/* ---------------------------------------------------------------------- */
int Init() {
    int fd = open("base.dat",          // nom du fichier
                  O_WRONLY |           // ouverture en écriture
                  O_CREAT  |           // créer le fichier s'il n'existe pas
                  O_TRUNC,             // vider le fichier s'il existe
                  0666);               // droits du fichier
                                       
    int v = 100;                       // valeur initiale de chaque entier

    write(fd, &v, sizeof(int));        // écrire le 1er entier
    write(fd, &v, sizeof(int));        // écrire le 2e entier
    write(fd, &v, sizeof(int));        // écrire le 3e entier
    write(fd, &v, sizeof(int));        // écrire le 4e entier

    close(fd);                         // fermer le fichier
    return 0;                          // succès
}

/* ---------------------------------------------------------------------- */
/* Reserve : décrémente le n-ième entier du fichier, si non nul */
/* ---------------------------------------------------------------------- */
int Reserve(int n) {
    int fd = open("base.dat", O_RDWR); // ouvrir base.dat en lecture/écriture
    int val;                           // valeur lue dans le fichier

    lockf(fd, F_LOCK, 0);              // poser un verrou exclusif sur le fichier, un seul processus peut ecrire , les autres attendent

    lseek(fd,                            // déplacement du curseur
          (n - 1) * sizeof(int),         // position du n-ième entier
          SEEK_SET);                     // depuis le début du fichier

    read(fd, &val, sizeof(int));         // lire la valeur du n-ième entier

    if (val > 0) {                        // si la valeur est positive
        val--;                            // décrémentation
        lseek(fd,                          // repositionner pour réécrire
              (n - 1) * sizeof(int),
              SEEK_SET);
        write(fd, &val, sizeof(int));     // écrire la nouvelle valeur
    }

    lockf(fd, F_ULOCK, 0);                // libérer le verrou

    close(fd);                            // fermer le fichier
    return 0;                             // succès
}
