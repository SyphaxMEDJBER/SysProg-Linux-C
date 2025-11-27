#include "../include/tp1.h"

int main(){
  char ligne[256];

  printf("commande : ");
  fgets(ligne,sizeof(ligne),stdin);//lire une ligne tapée par l'utilisateur 

 // transformer la ligne en tab d'arguments
  char **argv=ligne2Argv(ligne);


  printf("resultat:   \n");
  afficherArgv(argv);


  //liberation mémoire

  for(int i=0;argv[i] != NULL;i++){
    free(argv[i]);
  }

  free(argv);

  return 0;
}