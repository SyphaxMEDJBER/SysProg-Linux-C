#ifndef TP1_H
#define TP1_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include <time.h>


#define MAXCMD 100
#define MAXLINE 400





char **ligne2Argv(char* ligne );


void afficherArgv(char** ) ;


char *argv2Ligne(char **argv);

int executer(char **argv, int *pidcom);

void miniBash();


char ***file2TabArgv(char *file,int *nbarg);

void execFile(char* file);
int executerBatch(char **);

void execFileBatch(char* file);


// Epoch : la gestion du temps en informatique se fait généralement à l'aide d'une valeur (nommée 
// Epoch). Elle représente le nombre de secondes écoulées depuis le 1er janvier 1970. Son type de time_t
// sous UNIX mais c'est en fait un entier.
// Pour obtenir le temps actuel il faut utiliser la fonction time(time_t *) qui retourne l'Epoch de moment 
// de l'appel. Elle est déclarée dans le fichier time.h. 
// #include <stdio.h>
// #include <time.h>
// int main()
// {
// time_t now ;
// time(&now) ;
// printf(" l\'epoch actuel est : %d\n",now) ;
// }



typedef struct commande{
  int pid;//numero de processus dans lequel sexecute la commande 
  int statut;//son statut : -1 pas encore executé , 0 terminé , 1 en execution
  int retour;//son retour EXITSTATUS
  time_t debut;//'epoch à laquelle la commande a été lancée
  time_t fin;//'epoch à laquelle la commande s'est terminée
  char **argv;//son tableau argv 


}com;

com* file2TabCom(char *filename,int *nbcom);

com* file2TabCom(char *filename,int *nbcom);

void execFile2(char *file);            
void execFileBatchCom(char *file);       
void execFileBatchLimite(char *file, int N);  




#endif
