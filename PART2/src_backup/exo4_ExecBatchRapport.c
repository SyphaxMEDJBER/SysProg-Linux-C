#include "../include/tp2.h"

void execFileBatchRapport(char *file) {

    FILE *f = fopen(file, "r");
    if (!f) {
        perror("fopen");
        return;
    }

    char ligne[256];
    int pids[100];
    int actif[100];
    int nb = 0;

    while (fgets(ligne, sizeof(ligne), f) != NULL) {

        char *argv[10];
        int i = 0;
        char *token = strtok(ligne, " \t\n");

        while (token) {
            argv[i++] = token;
            token = strtok(NULL, " \t\n");
        }
        argv[i] = NULL;

        int pid = fork();

        if (pid == 0) {
            execvp(argv[0], argv);
            perror("exec");
            exit(1);
        }

        pids[nb] = pid;
        actif[nb] = 1;
        nb++;
    }

    fclose(f);

    int restants = nb;
    int status;

    while (restants > 0) {

        printf("=== Rapport ===\n");

        for (int i = 0; i < nb; i++) {
            if (actif[i] == 0) continue;

            int ret = waitpid(pids[i], &status, WNOHANG);

            if (ret == 0) {
                printf("PID %d : en cours\n", pids[i]);
            }
            else {
                printf("PID %d : terminé\n", pids[i]);
                actif[i] = 0;
                restants--;
            }
        }

        sleep(1);
    }

    printf("FIN\n");
}
