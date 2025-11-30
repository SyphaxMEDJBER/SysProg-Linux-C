#ifndef TP1_H
#define TP1_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

#define MAXCMD 100
#define MAXLINE 400





char **ligne2Argv(char* ligne );


void afficherArgv(char** ) ;


char *argv2Ligne(char **argv);

int executer(char** argv);

void miniBash();


char ***file2TabArgv(char *file,int *nbarg);

void execFile(char* file);


#endif
