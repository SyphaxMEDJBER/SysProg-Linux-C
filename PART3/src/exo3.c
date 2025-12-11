#include "../include/tp3.h"     // includes système + prototypes

/* ---------------------------------------------------------------------- */
/* Ls : exécute "ls repertoire" en utilisant fork + execlp  + redirection de la sortie vers un fichier               */
/* ---------------------------------------------------------------------- */
void LsDansFichier(char *rep,char* fichres) {
    int pid = fork();                  // créer un processus fils


    if (pid == 0) {                    // code du fils
      int file=open(fichres,O_WRONLY |           // ouverture en écriture
                  O_CREAT  |           // créer le fichier s'il n'existe pas
                  O_TRUNC,             // vider le fichier s'il existe
                  0666);
        close(1);
        dup(file);
        close(file);
        execlp("ls", "ls", rep, NULL); // exécuter la commande ls rep
        _exit(1);                      // si execlp échoue, sortir proprement
    }

    wait(NULL);                        // père : attendre la fin du fils
}
