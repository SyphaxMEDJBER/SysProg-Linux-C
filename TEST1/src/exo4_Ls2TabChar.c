#include "../include/test.h"

char **Ls2TabChar(char *rep) {

    char **tab = malloc(sizeof(char *) * 110);   // Tableau pour stocker jusqu'à 110 noms
    int n = 0;                                   // Nombre de fichiers lus

    int p[2];
    pipe(p);                                     // Tube pour récupérer la sortie de "ls"

    int pid = fork();

    if (pid == 0) {                               // --- PROCESSUS FILS ---
        close(p[0]);                              // Ferme lecture du tube
        dup2(p[1], 1);                            // Redirige stdout → tube
        close(p[1]);                              // Ferme écriture du tube
        execlp("ls", "ls", rep, NULL);            // Exécute "ls rep"
        _exit(1);                                 // Si échec exec
    }

    close(p[1]);                                   // Père ferme écriture du tube

    char buf[256];                                 // Lecture caractère par caractère
    char ligne[256];                               // Accumule le nom du fichier
    int i = 0;
    ligne[0] = '\0';

    while (read(p[0], buf, 1) > 0) {               // Lecture d'un caractère

        if (buf[0] == '\n') {                      // Fin d'un nom de fichier
            tab[n] = strdup(ligne);                // Ajoute la ligne au tableau
            n++;                                   // Incrémente le compteur
            i = 0;                                 // Reset index
            ligne[0] = '\0';                       // Reset buffer
        }
        else {
            ligne[i++] = buf[0];                   // Ajoute le caractère
            ligne[i] = '\0';                       // Termine la chaîne
        }
    }

    tab[n] = NULL;                                 // Fin du tableau
    close(p[0]);                                   // Ferme lecture du tube
    wait(NULL);                                    // Attend la fin du fils

    return tab;                                     // Retourne la liste des fichiers
}
