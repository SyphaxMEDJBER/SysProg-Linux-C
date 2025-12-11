#include "../include/tp3.h"


void miniBash2() {

    char ligne[MAXLINE];
    char **argv;

    while (1) {

        printf("MiniBash> ");
        fflush(stdout);

        if (fgets(ligne, MAXLINE, stdin) == NULL)
            break;              // CTRL+D

        argv = ligne2Argv(ligne);

        if (argv[0] == NULL)
            continue;           // ligne vide

        int pid = fork();

        if (pid == 0) {         // === FILS ===

            /* -------------------------------------------------------------- */
            /* TRAITEMENT DES REDIRECTIONS (<  >  >>)                         */
            /* -------------------------------------------------------------- */
            for (int i = 0; argv[i] != NULL; i++) {

                /* ----------- < fichier (entrée) ------------- */
                if (strcmp(argv[i], "<") == 0) {

                    int fd = open(argv[i+1], O_RDONLY);
                    if (fd < 0) { perror("open"); exit(1); }

                    close(0);          // fermer stdin
                    dup(fd);           // stdin ← fichier
                    close(fd);

                    argv[i] = NULL;    // couper avant '<'
                    break;
                }

                /* ----------- > fichier (sortie écrasée) ----- */
                if (strcmp(argv[i], ">") == 0) {

                    int fd = open(argv[i+1],
                                  O_WRONLY | O_CREAT | O_TRUNC,
                                  0666);
                    if (fd < 0) { perror("open"); exit(1); }

                    close(1);          // fermer stdout
                    dup(fd);           // stdout ← fichier
                    close(fd);

                    argv[i] = NULL;    // couper la commande ici
                    break;
                }

                /* ----------- >> fichier (append) ------------- */
                if (strcmp(argv[i], ">>") == 0) {

                    int fd = open(argv[i+1],
                                  O_WRONLY | O_CREAT | O_APPEND,
                                  0666);
                    if (fd < 0) { perror("open"); exit(1); }

                    close(1);
                    dup(fd);
                    close(fd);

                    argv[i] = NULL;    // couper la commande ici
                    break;
                }
            }

            execvp(argv[0], argv);  // exécuter la commande
            perror("execvp");
            _exit(1);
        }

        /* === PÈRE === */
        wait(NULL);

        /* libération mémoire */
        for (int i = 0; argv[i] != NULL; i++)
            free(argv[i]);
        free(argv);
    }
}
