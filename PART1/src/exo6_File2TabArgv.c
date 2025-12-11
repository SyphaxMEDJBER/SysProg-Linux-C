#include "../include/tp1.h"

char *** file2TabArgv(char *filename,int *nbarg){

  FILE *file = fopen(filename,"r");          // Ouverture du fichier en lecture

  char *** tab = malloc(sizeof(char**) * MAXCMD);   // Tableau de commandes (ARGV)
  char ligne[MAXLINE];                       // Buffer pour lire chaque ligne du fichier
  *nbarg = 0;                                // Nombre de commandes trouvées

  if(file == NULL){
    perror("erruer d'ouverture de fichier "); // Erreur si le fichier est introuvable
    return NULL;
  } else {

    // Lecture ligne par ligne jusqu'à MAXCMD ou fin du fichier
    while(((*nbarg) < MAXCMD) && (fgets(ligne, MAXLINE, file) != NULL)){
      tab[*nbarg] = ligne2Argv(ligne);       // Convertit chaque ligne en tableau argv
      (*nbarg)++;                             // Incrémente le compteur de commandes
    }

    fclose(file);                             // Fermeture du fichier après lecture
  }

  return tab;                                 // Retourne le tableau de commandes
};
