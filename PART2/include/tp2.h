#ifndef TP2_H
#define TP2_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

#define MAXCMD 100
#define MAXLINE 400


void affiche(int n, char *msg);

void affiche2(int n, char *msg);

void timeout_run(int n, char **cmd);

void execFileBatchRapport(char *file);

#endif
