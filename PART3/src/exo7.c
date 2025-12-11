#include "../include/tp3.h"

void miniBash3() {

    char ligne[MAXLINE];                     // Buffer d'entrée utilisateur
    char **argv;                             // Tableau d'arguments

    while (1) {

        printf("MiniBash> ");                // Prompt
        fflush(stdout);

        if (fgets(ligne, MAXLINE, stdin) == NULL)  // Lecture ligne ; NULL = Ctrl+D
            break;

        argv = ligne2Argv(ligne);            // Conversion en tableau argv

        if (argv[0] == NULL)                 // Ligne vide
            continue;

        /* ---------------------- detecter | ---------------------- */
        int posPipe = -1;                    // Position du symbole "|"
        for (int i = 0; argv[i] != NULL; i++) {
            if (strcmp(argv[i], "|") == 0) { // Pipe trouvé
                posPipe = i;
                break;
            }
        }

        /* ---------------------- pas de pipe ----------------------- */
        if (posPipe == -1) {
            int pid = fork();                // Processus pour exécuter la commande
            if (pid == 0) {                  // Fils
                execvp(argv[0], argv);       // Exécution directe
                perror("exec");
                _exit(1);
            }
            wait(NULL);                      // Père attend la fin
        }

        /* ---------------------- pipe present ----------------------- */
        else {

            argv[posPipe] = NULL;            // Coupe argv en deux commandes
            char **cmd1 = argv;              // Première commande
            char **cmd2 = &argv[posPipe + 1];// Deuxième commande

            /* SECURITE : commandes vides */
            if (cmd1[0] == NULL || cmd2[0] == NULL ||
                cmd1[0][0] == '\0' || cmd2[0][0] == '\0') {
                printf("Erreur: pipe incomplet\n"); // Gestion erreur syntaxique
                continue;
            }

            int t[2];
            pipe(t);                         // Création du tube

            int pid1 = fork();               // Processus 1
            if (pid1 == 0) {
                close(1);                    // Redirection stdout → tube
                dup(t[1]);
                close(t[0]); close(t[1]);
                execvp(cmd1[0], cmd1);       // Exécute la première commande
                perror("exec cmd1");
                _exit(1);
            }

            int pid2 = fork();               // Processus 2
            if (pid2 == 0) {
                close(0);                    // Redirection stdin ← tube
                dup(t[0]);
                close(t[1]); close(t[0]);
                execvp(cmd2[0], cmd2);       // Exécute la deuxième commande
                perror("exec cmd2");
                _exit(1);
            }

            close(t[0]);                      // Fermeture des deux extrémités dans le père
            close(t[1]);
            wait(NULL);                       // Attente des deux processus
            wait(NULL);
        }

        for (int i = 0; argv[i] != NULL; i++) // Libération mémoire argv
            free(argv[i]);
        free(argv);
    }
}
