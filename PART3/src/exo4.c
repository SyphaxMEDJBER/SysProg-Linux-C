#include "../include/tp3.h"     // includes système + prototypes




/* ---------------------------------------------------------------------- */
/* NbFichierPrint : affiche le résultat de "ls repertoire | wc -l"             */
/* ---------------------------------------------------------------------- */
void NbFichierPrint(char *rep) {

    int t[2];                               // tube entre ls → wc -l, ce tab t[2] contient les descripteurs des fichiers 
    pipe(t); 
    int res=-1;                               // créer le tube, il remplit le tab t tq :t[0] coté lecteur , et t[1] cote ecriture 

    int pid1 = fork();                      // 1er fils : ls
    if (pid1 == 0) {                        // === FILS 1 : ls ===
        close(1);                           // fermer stdout
        dup(t[1]);                          // rediriger stdout vers l'entrée du tube
        close(t[0]);                        // fermer lecture du tube
        close(t[1]);                        // fermer l'écriture duplicée (inutile)

        execlp("ls", "ls", rep, NULL);      // exécuter ls rep
        _exit(1);                           // sécurité si execlp échoue
    }

    int pid2 = fork();                      // 2e fils : wc -l
    if (pid2 == 0) {                        // === FILS 2 : wc -l ===
        close(0);                           // fermer stdin
        dup(t[0]);                          // rediriger stdin vers la sortie du tube
        close(t[1]);                        // fermer écriture
        close(t[0]);                        // fermer lecture

        execlp("wc", "wc", "-l", NULL);     // exécuter wc -l
        
        _exit(1);                           // sécurité si execlp échoue
    }

    close(t[0]);                             // pere ferme lecture du tube
    close(t[1]);                             // pere ferme écriture du tube

    wait(NULL);                              // attendre ls
    wait(NULL);                              // attendre wc -l

}
