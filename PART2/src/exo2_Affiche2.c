#include "../include/tp2.h"

<<<<<<< HEAD
// volatile sig_atomic_t demande_exit = 0;

// void handler(int sig) {
//     demande_exit = 1;
// }

// void affiche2(int n, char *msg) {
//     signal(SIGINT, handler);

//     for (int i = 0; i < n; i++) {

//         if (demande_exit) {
//             char pwd[100];
//             printf("Tapez le mot de passe : ");
//             fflush(stdout);
//             scanf("%s", pwd);

//             if (strcmp(pwd, "bonmotdepasse") == 0)
//                 exit(0);

//             demande_exit = 0;
//         }

//         printf("%s\n", msg);
//         fflush(stdout);
//         sleep(1);
//     }
// }


char* mdp="test";



void fctINT(int sig) {
    char ligne[MAXLINE];

    printf("Mot de passe : ");
    fflush(stdout);

    fgets(ligne, MAXLINE, stdin);

    ligne[strcspn(ligne, "\n")] = 0;  // enlever le \n

    if (strcmp(ligne, mdp) == 0) {
        kill(getpid(), SIGKILL);
    }
}


int main(int argc,char* argv[] ){
    if(argc<2){
        exit(1);
    }

    char* msg=argv[1];


    signal(SIGINT,fctINT);

    while(1){
        printf("%s\n",msg);
        sleep(1);
    }








    



}
=======
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
>>>>>>> origin/sauvegarde-tp
