#include "../include/tp1.h"

char *argv2Ligne(char **argv){

    char *ligne;
    size_t taille=0;
    int i=0;



    //calculer la taille a allouer
  for(i=0;argv[i]!=NULL;i++){
    taille+=strlen(argv[i])+1;  //+1 pour l'espace ou \0
  }


  //allocation mémoire
  ligne=malloc(taille* sizeof(char));
  if(ligne==NULL){
    perror("malloc");
    exit(1);
  }


  //transformation
  ligne[0]="\0";// <=> ligne[0]="";
  for(i=0;argv[i]!=NULL;i++){
    strcat(ligne,argv[i]);
    if(argv[i+1]!=NULL){
      strcat(ligne," ");
    }

  }




  return ligne;



}

