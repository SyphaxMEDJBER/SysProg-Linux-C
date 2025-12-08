#include "../include/tp1.h"

void execFile(char* file){
  int nbar=0;

    char ***tab=file2TabArgv(file,&nbar);
    for(int i=0;i<nbar;i++){
      int pidtmp;
      executer(tab[i], &pidtmp);

    }


    printf("FIN..");


  







}