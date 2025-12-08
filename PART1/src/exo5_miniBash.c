#include"../include/tp1.h"

void miniBash(){

  char ligne[MAXLINE];
  char **argv;





  printf("MiniBash> \n");
  while(1){
    printf("entrer commande>");
    fflush(stdout);//forcer l'affichage immediat sur l'ecran 


    if(fgets(ligne,MAXLINE,stdin)==NULL){ // si ctrl D
      break;
    };

    argv=ligne2Argv(ligne);
    if(argv[0]==NULL){
      continue; // si ligne vide
    }

    int pidtmp;
    executer(argv, &pidtmp);


    //liberation mémoire
    for(int i=0;argv[i]==NULL;i++){
      free(argv[i]);
    }
    free(argv);


  }

}