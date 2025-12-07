#include "../include/tp1.h"


com * file2TabCom(char *filename,int *nbcom){

  FILE *file=fopen(filename,"r");

  com * tab=malloc(sizeof(com)*MAXCMD);
  char ligne[MAXLINE];
  *nbcom=0;

  if(file==NULL){
    perror("erruer d'ouverture de fichier ");
    return NULL;
  }else{
    
    while(((*nbcom)<MAXCMD)&&(fgets(ligne,MAXLINE,file)!=NULL)){
  char **argv;//son tableau argv 
        tab[*nbcom].argv = ligne2Argv(ligne);
        tab[*nbcom].pid = -1;
        tab[*nbcom].statut = -1;
        tab[*nbcom].retour = -1;
        tab[*nbcom].debut = 0;
        tab[*nbcom].fin = 0;
      

      (*nbcom)++;
     
    }


    fclose(file);
  }



  return tab;


};
