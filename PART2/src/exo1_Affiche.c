#include "../include/tp2.h"

int fin = 0;                 // Indique si l'alarme a été reçue
char *msg;                   // Message à afficher

void fctALRM(int sig){
    fin = 1;                 // Quand SIGALRM arrive → fin = 1
}

int main(int argc, char* argv[]){
    if(argc < 3) exit(1);    // Besoin de 2 arguments min : N et message

    int N = atoi(argv[1]);   // Durée avant arrêt
    msg = argv[2];           // Message à afficher

    signal(SIGALRM, fctALRM); // Associe SIGALRM → fctALRM
    alarm(N);                 // Déclenche SIGALRM dans N secondes

    while(fin != 1){          // Tant que SIGALRM pas reçu
        printf("%s\n", msg);  // Affiche le message
        fflush(stdout);       // Assure l'affichage immédiat
        sleep(1);             // Attend 1 seconde
    }

    return 0;
}
