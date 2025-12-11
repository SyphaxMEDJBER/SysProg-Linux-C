#include"../include/tp1.h"

void miniBash(){

  char ligne[MAXLINE];          // Buffer pour lire la ligne de commande
  char **argv;                  // Tableau d’arguments après découpe

  printf("MiniBash> \n");

  while(1){
    printf("entrer commande>");
    fflush(stdout);             // Force l’affichage immédiat du prompt

    if(fgets(ligne, MAXLINE, stdin) == NULL){  // Lecture ligne ; NULL = <Ctrl+D>
      break;                                   // Sort du minibash
    }

    argv = ligne2Argv(ligne);   // Transformation de la ligne en tableau argv
    if(argv[0] == NULL){
      continue;                 // Ligne vide → on relance le prompt
    }

    int pidtmp;
    executer(argv, &pidtmp);    // Exécute la commande synchroniquement,

    // Libération mémoire pour chaque argument
    for(int i = 0; argv[i] != NULL; i++){
      free(argv[i]);            // Libère chaque chaîne
    }
    free(argv);                 // Libère le tableau argv
  }

}
