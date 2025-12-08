#include "../include/tp1.h"

int executer(char **argv, int *pidcom) {

    int status;
    int pid = fork();

    if (pid == 0) {
        execvp(argv[0], argv);
        perror("exec");
        exit(254);
    }

    if (pid < 0) {
        perror("fork");
        return 255;
    }

    *pidcom = pid;     // pid du fils

    wait(&status);     // attendre le fils

    return WEXITSTATUS(status);
}
