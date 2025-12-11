#include "../include/tp1.h"

int executerBatch(char **argv){

  int pid = fork();                      // Création d’un processus fils

  if(pid == 0){                          // --- PROCESSUS FILS ---
    execvp(argv[0], argv);               // Exécute la commande sans attendre la fin
    perror("exec");                      // Si exec échoue, affichage de l’erreur
    exit(254);                           // Code d’erreur standard pour exec raté
  }
  else if(pid < 0){                      // --- ERREUR DE FORK ---
    perror("fork");                      // Impossible de créer un processus
    return 255;                          // Code de retour en cas d'échec de fork
  }

  return pid;                            // --- PROCESSUS PÈRE ---
                                         // Renvoie immédiatement le PID du fils
}
