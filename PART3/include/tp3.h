#ifndef TP3_H
#define TP3_H

/* --- includes système pour tout le TP --- */
#include <fcntl.h>      // open, lockf
#include <unistd.h>     // read, write, close, lseek, fork, pipe, dup
#include <stdlib.h>     // malloc, free, atoi, exit
#include <stdio.h>      // printf, fprintf, perror
#include <string.h>     // strlen, strcmp
#include <sys/wait.h>   // wait


#define MAXCMD 100
#define MAXLINE 400


/* ===================== EXO 1 ===================== */
int Init();             // crée base.dat
int Reserve(int n);     // décrémente n-ième entier

/* ===================== EXO 2 ===================== */
void Ls(char *rep);     // exécute ls rep

/* ===================== EXO 3 ===================== */
void LsDansFichier(char *rep, char *fich);  // ls rep > fichier

/* ===================== EXO 4 ===================== */
void NbFichierPrint(char *rep);   // affiche ls rep | wc -l

/* ===================== EXO 5 ===================== */
int NbFichier(char *rep);           // retourne le nombre (ls | wc -l)

/* ===================== EXO 6 ===================== */
void miniBash2();                    // minibash amélioré redirections
char **ligne2Argv(char *ligne);


void miniBash3();  

#endif
