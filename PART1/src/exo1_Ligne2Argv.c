#include "../include/tp1.h"

#define MAX_ARG 100

char **ligne2Argv(char *ligne)
{ 
  char * li;               // Copie de la ligne car strtok modifie la chaîne originale
  char **arg;             // Tableau final de pointeurs vers les arguments
  char * p;               // Pointeur courant utilisé par strtok
  int i=0;                // Compteur d'arguments

  li=strdup(ligne);       // Duplique la ligne pour la rendre modifiable
  if (li==NULL)
  {
    perror("strdup");     // Affiche l’erreur si l’allocation échoue
    exit(1);
  }

  arg=(char**)malloc(sizeof(char *) * MAX_ARG);   // Alloue le tableau de pointeurs
  if(arg==NULL){
    perror("malloc");     // Gestion de l'échec de malloc
    exit(1);
  }

  p=strtok(li," \t\n");   // Récupère le premier token (séparateurs : espace, tab, retour ligne)
  while((p!=NULL)&&(i<MAX_ARG-1)){
    arg[i]=strdup(p);     // Duplique chaque argument individuellement
    if(arg[i]==NULL){
      perror("strdup");
      exit(1);
    }
    p=strtok(NULL," \t\n");   // Passe au token suivant
    i++;
  }

  arg[i]=NULL;            // Termine le tableau par NULL comme argv
  free(li);               // Libère la chaîne temporaire utilisée par strtok

  return arg;             // Retourne le tableau d’arguments
}
