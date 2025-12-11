#include "../include/tp2.h"

char* mdp = "test";                       // Mot de passe attendu

void fctINT(int sig) {
    char ligne[MAXLINE];                  // Buffer pour lire le mot de passe

    printf("Mot de passe : ");            // Demande du mot de passe
    fflush(stdout);                       // Affichage immédiat

    fgets(ligne, MAXLINE, stdin);         // Lecture saisie utilisateur

    ligne[strcspn(ligne, "\n")] = 0;      // Suppression du '\n' final

    if (strcmp(ligne, mdp) == 0) {        // Vérification du mot de passe
        kill(getpid(), SIGKILL);          // Si correct → tuer le processus
    }
}

int main(int argc, char* argv[] ){
    if(argc < 2){                         // Vérification du nombre d’arguments
        exit(1);
    }

    char* msg = argv[1];                  // Message à afficher en boucle

    signal(SIGINT, fctINT);               // Associe Ctrl+C à fctINT

    while(1){
        printf("%s\n", msg);              // Affiche le message
        sleep(1);                         // Pause 1 seconde
    }
}
