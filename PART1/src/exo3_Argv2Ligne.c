#include "../include/tp1.h"

char *argv2Ligne(char **argv){

    char *ligne;                       // Contiendra la ligne reconstruite
    size_t taille=0;                   // Taille mémoire à allouer
    int i=0;

    // Calcul de la taille totale nécessaire pour la chaîne finale
    // On additionne la longueur de chaque argument + 1 (pour espace ou '\0')
    for(i=0; argv[i]!=NULL; i++){
        taille += strlen(argv[i]) + 1;
    }

    // Allocation mémoire de la ligne
    ligne = malloc(taille * sizeof(char));
    if(ligne == NULL){
        perror("malloc");              // Affiche l’erreur d’allocation
        exit(1);
    }

    // Construction de la chaîne finale
    ligne[0] = '\0';                   // Initialise la chaîne vide

    for(i=0; argv[i]!=NULL; i++){
        strcat(ligne, argv[i]);        // Ajout de l’argument courant

        if(argv[i+1] != NULL){         // Ajout d’un espace seulement si un argument suit
            strcat(ligne, " ");
        }
    }

    return ligne;                      // Retourne la ligne reconstruite
}
