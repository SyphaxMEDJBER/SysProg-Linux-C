#include "../include/tp2.h"

static int pid_fils = -1;
static int tue = 0;

void handlerALRM(int sig) {
    if (pid_fils > 0) {
        kill(pid_fils, SIGKILL);
        tue = 1;
    }
}

void timeout_run(int n, char **cmd) {

    pid_fils = fork();

    if (pid_fils == 0) {
        execvp(cmd[0], cmd);
        perror("execvp");
        exit(2);
    }

    signal(SIGALRM, handlerALRM);
    alarm(n);

    int status;
    wait(&status);//si le signal SIGALRM arrive le wait se reveille 

    if (tue)
        printf("Processus tué au bout de %d secondes car il n'est pas terminé.\n", n);
    else
        printf("Processus terminé\n");
}
