#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

// ===============================
// EXO 1
// ===============================

void Init() {
    int fd = open("base.dat", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int val = 100;
    for (int i = 0; i < 4; i++) write(fd, &val, sizeof(int));
    close(fd);
}

void Reserve(int n) {
    int fd = open("base.dat", O_RDWR);
    lockf(fd, F_LOCK, 0);
    lseek(fd, (n-1)*sizeof(int), SEEK_SET);
    int val;
    read(fd, &val, sizeof(int));
    if (val > 0) {
        val--;
        lseek(fd, (n-1)*sizeof(int), SEEK_SET);
        write(fd, &val, sizeof(int));
    }
    lockf(fd, F_ULOCK, 0);
    close(fd);
}

// ===============================
// EXO 2
// ===============================

void Ls(char *rep) {
    int pid = fork();
    if (pid == 0) execlp("ls", "ls", rep, NULL);
    wait(NULL);
}

// ===============================
// EXO 3
// ===============================

void LsDansFichier(char *rep, char *fichier) {
    int pid = fork();
    if (pid == 0) {
        int fd = open(fichier, O_WRONLY|O_CREAT|O_TRUNC, 0644);
        dup2(fd, 1);
        close(fd);
        execlp("ls", "ls", rep, NULL);
        exit(1);
    }
    wait(NULL);
}

// ===============================
// EXO 4
// ===============================

void NbFichierAff(char *rep) {
    int p1[2];
    pipe(p1);

    int pid = fork();
    if (pid == 0) {
        close(p1[0]);
        dup2(p1[1], 1);
        close(p1[1]);
        execlp("ls", "ls", rep, NULL);
        exit(1);
    }

    close(p1[1]);

    int p2[2];
    pipe(p2);

    int pid2 = fork();
    if (pid2 == 0) {
        dup2(p1[0], 0);
        close(p1[0]);
        dup2(p2[1], 1);
        close(p2[1]);
        execlp("wc", "wc", "-l", NULL);
        exit(1);
    }

    close(p1[0]);
    close(p2[1]);

    char buf[64];
    int r = read(p2[0], buf, 63);
    buf[r] = '\0';
    printf("%s", buf);
    close(p2[0]);

    wait(NULL); wait(NULL);
}

// ===============================
// EXO 5
// ===============================

int NbFichier(char *rep) {
    int p1[2]; pipe(p1);

    int pid = fork();
    if (pid == 0) {
        close(p1[0]);
        dup2(p1[1], 1);
        close(p1[1]);
        execlp("ls", "ls", rep, NULL);
        exit(1);
    }

    close(p1[1]);

    int p2[2]; pipe(p2);

    int pid2 = fork();
    if (pid2 == 0) {
        dup2(p1[0], 0);
        close(p1[0]);
        dup2(p2[1], 1);
        close(p2[1]);
        execlp("wc", "wc", "-l", NULL);
        exit(1);
    }

    close(p1[0]);
    close(p2[1]);

    char buf[64];
    int r = read(p2[0], buf, 63);
    buf[r] = '\0';
    close(p2[0]);

    wait(NULL); wait(NULL);

    return atoi(buf);
}

// ===============================
// EXO 6 — MiniBash redirections
// ===============================

void executer_redir(char **argv) {

    int i = 0;
    int fd;

    while (argv[i]) {

        if (strcmp(argv[i], ">") == 0) {
            fd = open(argv[i+1], O_WRONLY|O_CREAT|O_TRUNC, 0644);
            argv[i] = NULL;
            dup2(fd, 1);
            close(fd);
        }

        else if (strcmp(argv[i], ">>") == 0) {
            fd = open(argv[i+1], O_WRONLY|O_CREAT|O_APPEND, 0644);
            argv[i] = NULL;
            dup2(fd, 1);
            close(fd);
        }

        else if (strcmp(argv[i], "<") == 0) {
            fd = open(argv[i+1], O_RDONLY);
            argv[i] = NULL;
            dup2(fd, 0);
            close(fd);
        }

        i++;
    }

    execvp(argv[0], argv);
    exit(1);
}

void MiniBash_redir() {

    char ligne[256];

    while (1) {
        printf("> ");
        fflush(stdout);

        if (!fgets(ligne, 256, stdin)) break;

        char *argv[50];
        int i = 0;

        char *tok = strtok(ligne, " \t\n");
        while (tok) {
            argv[i++] = tok;
            tok = strtok(NULL, " \t\n");
        }
        argv[i] = NULL;

        int pid = fork();
        if (pid == 0) executer_redir(argv);

        wait(NULL);
    }
}

// ===============================
// EXO 7 — MiniBash avec pipes
// ===============================

void executer_pipe(char **cmd1, char **cmd2) {

    int p[2];
    pipe(p);

    if (fork() == 0) {
        dup2(p[1], 1);
        close(p[0]); close(p[1]);
        execvp(cmd1[0], cmd1);
        exit(1);
    }

    if (fork() == 0) {
        dup2(p[0], 0);
        close(p[0]); close(p[1]);
        execvp(cmd2[0], cmd2);
        exit(1);
    }

    close(p[0]);
    close(p[1]);
    wait(NULL); wait(NULL);
}

void MiniBash_pipe() {

    char ligne[256];

    while (1) {

        printf("> ");
        fflush(stdout);

        if (!fgets(ligne, 256, stdin)) break;

        if (!strstr(ligne, "|")) continue;

        char *cmd1[20], *cmd2[20];

        char *left = strtok(ligne, "|");
        char *right = strtok(NULL, "|");

        int i = 0;
        char *tok = strtok(left, " \t\n");
        while (tok) { cmd1[i++] = tok; tok = strtok(NULL, " \t\n"); }
        cmd1[i] = NULL;

        i = 0;
        tok = strtok(right, " \t\n");
        while (tok) { cmd2[i++] = tok; tok = strtok(NULL, " \t\n"); }
        cmd2[i] = NULL;

        executer_pipe(cmd1, cmd2);
    }
}

// ===============================
// EXO 8 — ExecFile avec sorties séparées
// ===============================

void ExecFile_sauvegarde(char *file) {

    FILE *f = fopen(file, "r");
    if (!f) return;

    time_t now = time(NULL);

    char dirname[256];
    sprintf(dirname, "%s.%ld", file, now);

    char cmdmkdir[256];
    sprintf(cmdmkdir, "mkdir %s", dirname);

    int pid = fork();
    if (pid == 0) execlp("sh", "sh", "-c", cmdmkdir, NULL);
    wait(NULL);

    char ligne[256];

    while (fgets(ligne, 256, f)) {

        char *argv[20];
        int i = 0;

        char *tok = strtok(ligne, " \t\n");
        while (tok) { argv[i++] = tok; tok = strtok(NULL, " \t\n"); }
        argv[i] = NULL;

        int pido = fork();

        if (pido == 0) {

            char out[256], err[256];
            sprintf(out, "%s/%d.out", dirname, getpid());
            sprintf(err, "%s/%d.err", dirname, getpid());

            int fd1 = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            int fd2 = open(err, O_WRONLY | O_CREAT | O_TRUNC, 0644);

            dup2(fd1, 1);
            dup2(fd2, 2);

            close(fd1);
            close(fd2);

            execvp(argv[0], argv);
            exit(1);
        }
    }

    fclose(f);

    while (wait(NULL) > 0);

    char rapport[256];
    sprintf(rapport, "%s/rapport.log", dirname);

    int fd = open(rapport, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, "FIN\n", 4);
    close(fd);
}

