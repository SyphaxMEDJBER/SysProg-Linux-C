#include "../include/tp1.h"



void execFileBatch(char* file){

  int nba;
  int pids[MAXCMD];
  char *** tab=file2TabArgv(file,&nba);

  for (int i=0;i<nba;i++){
    pids[i]=executerBatch(tab[i]);
  }


  for(int i=0;i<nba;i++){
    wait(NULL);
  }

  printf("----------------FIN---------------");



}
