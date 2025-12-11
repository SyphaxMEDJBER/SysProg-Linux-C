#include "../include/tp1.h"

void execFile(char* file){
  int nbar = 0;                            // Nombre de commandes dans le fichier

  char ***tab = file2TabArgv(file, &nbar); // Récupère toutes les commandes du fichier
                                           // sous forme de tableau de tableaux (argv)

  for(int i = 0; i < nbar; i++){
    int pidtmp;                            // PID du processus exécutant la commande
    executer(tab[i], &pidtmp);             // Exécute chaque commande séquentiellement
  }

  printf("FIN..");                          // Affiche fin d’exécution après toutes les commandes
}
