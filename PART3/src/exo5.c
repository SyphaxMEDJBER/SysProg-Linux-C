#include "../include/tp3.h"

/* -----------------------------------------------------------------------
   NbFichier : retourne le résultat de "ls rep | wc -l"
   ----------------------------------------------------------------------- */
int NbFichier(char *rep) {

    int t[2];                     // tube 1 : ls → wc
    int r[2];                     // tube 2 : wc → père
    pipe(t);                     // créer tube t
    pipe(r);                     // créer tube r

    /* ------------------------ FILS 1 : exécute ls rep ------------------------ */
    int pid1 = fork();           
    if (pid1 == 0) {             // FILS 1

        close(1);                // fermer stdout
        dup(t[1]);               // rediriger stdout → t[1]
        close(t[0]);             // fermer lecture tube t
        close(t[1]);             // fermer écriture (déjà dupliquée)

        close(r[0]);             // inutile
        close(r[1]);             // inutile

        execlp("ls", "ls", rep, NULL);  // exécuter ls rep
        _exit(1);                // sécurité si execlp échoue
    }

    /* ------------------------ FILS 2 : exécute wc -l ------------------------ */
    int pid2 = fork();
    if (pid2 == 0) {             // FILS 2

        close(0);                // fermer stdin
        dup(t[0]);               // rediriger stdin → t[0]

        close(1);                // fermer stdout
        dup(r[1]);               // rediriger stdout → r[1]

        close(t[0]);             // fermer tube t
        close(t[1]);
        close(r[0]);             // fermer lecture tube r
        close(r[1]);             // fermer écriture (déjà dupliquée)

        execlp("wc", "wc", "-l", NULL);  // exécuter wc -l
        _exit(1);
    }

    /* ----------------------------- PERE ------------------------------------ */

    close(t[0]);                 // père : ne lit pas ls
    close(t[1]);                 // père : n'écrit pas dans ls→wc

    close(r[1]);                 // père : ne doit pas écrire dans wc→père

    char buffer[50];             // pour lire le résultat
    int n = read(r[0], buffer, 50);   // lire ce que wc -l a envoyé
    buffer[n] = '\0';            // terminer la chaîne

    close(r[0]);                 // fermer la lecture du tube r

    wait(NULL);                  // attendre ls
    wait(NULL);                  // attendre wc -l

    return atoi(buffer);         // convertir chaîne → int et retourner
}
