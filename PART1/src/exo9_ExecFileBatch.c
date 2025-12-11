#include "../include/tp1.h"

void execFileBatch(char* file){

  int nba;                                   // Nombre total de commandes
  int pids[MAXCMD];                           // Tableau pour stocker les PID des fils
  char *** tab = file2TabArgv(file, &nba);    // Lecture des commandes du fichier

  // --- Lancement simultané de toutes les commandes ---
  for (int i = 0; i < nba; i++){
    pids[i] = executerBatch(tab[i]);          // Lance chaque commande sans attendre
  }

  // --- Attente de la fin de toutes les commandes ---
  for(int i = 0; i < nba; i++){
    wait(NULL);                               // Attend la terminaison de chaque fils
  }

  printf("----------------FIN---------------");
}
