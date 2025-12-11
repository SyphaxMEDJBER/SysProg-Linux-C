#include "../include/tp2.h"

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