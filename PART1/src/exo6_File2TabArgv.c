#include "../include/tp1.h"


char *** file2TabArgv(char *filename,int *nbarg){

  FILE *file=fopen(filename,"r");

  char *** tab=malloc(sizeof(char**)*MAXCMD);
  char ligne[MAXLINE];
  *nbarg=0;

  if(file==NULL){
    perror("erruer d'ouverture de fichier ");
    return NULL;
  }else{
    
    while(((*nbarg)<MAXCMD)&&(fgets(ligne,MAXLINE,file)!=NULL)){
      tab[(*nbarg)]=ligne2Argv(ligne);
      (*nbarg)++;
     
    }


    fclose(file);
  }



  return tab;


};
