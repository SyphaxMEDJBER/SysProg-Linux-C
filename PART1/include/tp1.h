#ifndef TP1_H
#define TP1_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>





char **ligne2Argv(char* ligne );


void afficherArgv(char** ) ;


char *argv2Ligne(char **argv);

int executer(char** argv);

void miniBash();


#endif
