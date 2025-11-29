#include"../include/tp1.h"
#define MAXCMD 500

void miniBash(){

  char ligne[MAXCMD];
  char **argv;





  printf("MiniBash> \n");
  while(1){
    printf("entrer commande>");
    fflush(stdout);//forcer l'affichage immediat sur l'ecran 


    if(fgets(ligne,MAXCMD,stdin)==NULL){ // si ctrl D
      break;
    };

    argv=ligne2Argv(ligne);
    if(argv[0]==NULL){
      continue; // si ligne vide
    }
    executer(argv);

    //liberation mémoire
    for(int i=0;argv[i]==NULL;i++){
      free(argv[i]);
    }
    free(argv)


  }

}