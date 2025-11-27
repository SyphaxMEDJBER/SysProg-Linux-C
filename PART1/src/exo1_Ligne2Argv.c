
#include "../include/tp1.h"


#define MAX_ARG 100

char **ligne2Argv(char *ligne)
{ 
  char * li;
  char **arg;
  char * p;
  int i=0;


  li=strdup(ligne);
  if (li==NULL)
  {
    perror("strdup");
    exit(1);

  }


  arg=(char**)malloc(sizeof(char *) * MAX_ARG);
  if(arg==NULL){
    perror("malloc");
    exit(1);
  }



  p=strtok(li," \t\n");
  while((p!=NULL)&&(i<MAX_ARG-1)){
    arg[i]=strdup(p);
    if(arg[i]==NULL){
      perror("strdup");
      exit(1);
    }
    p=strtok(NULL," \t\n");//Découpe la chaîne à chaque espace, tabulation ou retour à la ligne.
    i++;
  }
  arg[i]=NULL;
  free(li);

  return arg;

}

