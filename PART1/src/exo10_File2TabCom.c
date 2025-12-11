#include "../include/tp1.h"

com * file2TabCom(char *filename,int *nbcom){

  FILE *file = fopen(filename, "r");      // Ouverture du fichier contenant les commandes

  com * tab = malloc(sizeof(com) * MAXCMD); // Allocation du tableau de structures com
  char ligne[MAXLINE];                    // Buffer pour lire chaque ligne
  *nbcom = 0;                             // Nombre de commandes initialisé à 0

  if(file == NULL){
    perror("erruer d'ouverture de fichier "); // Erreur si le fichier ne s'ouvre pas
    return NULL;
  } else {
    
    // Lecture du fichier ligne par ligne jusqu'à MAXCMD ou fin du fichier
    while(((*nbcom) < MAXCMD) && (fgets(ligne, MAXLINE, file) != NULL)){
      
      char **argv;                        // Tableau ARGV associé à la commande

      tab[*nbcom].argv = ligne2Argv(ligne); // Transformation ligne → argv
      tab[*nbcom].pid = -1;               // PID non encore défini
      tab[*nbcom].statut = -1;            // Statut : -1 = non exécuté
      tab[*nbcom].retour = -1;            // Code retour initial
      tab[*nbcom].debut = 0;              // Timestamp de début
      tab[*nbcom].fin = 0;                // Timestamp de fin

      (*nbcom)++;                          // Incrément du nombre total de commandes
    }

    fclose(file);                          // Fermeture du fichier
  }

  return tab;                              // Retourne le tableau de structures com
};
