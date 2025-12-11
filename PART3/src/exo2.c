#include "../include/tp3.h"     // includes système + prototypes

/* ---------------------------------------------------------------------- */
/* Ls : exécute "ls repertoire" en utilisant fork + execlp                */
/* ---------------------------------------------------------------------- */
void Ls(char *rep) {
    int pid = fork();                  // créer un processus fils

    if (pid == 0) {                    // code du fils
        execlp("ls", "ls", rep, NULL); // exécuter la commande ls rep
        _exit(1);                      // si execlp échoue, sortir proprement
    }

    wait(NULL);                        // père : attendre la fin du fils
}
