#include "../include/tp1.h"

void afficherArgv(char **arg){
    int i=0;                          // Index pour parcourir le tableau argv

    while (arg[i]!=NULL)              // On boucle jusqu'à rencontrer le pointeur NULL de fin
    {
        printf("Arg %d : %s\n",i,arg[i]); // Affiche l’index et la valeur de l’argument
        i++;                               // Passage à l’argument suivant
    }
}
