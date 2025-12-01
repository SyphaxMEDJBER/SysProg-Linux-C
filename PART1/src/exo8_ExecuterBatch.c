#include "../include/tp1.h"

int executerBatch(char **argv){

  int pid=fork();
  if(pid==0){
    execvp(argv[0],argv);
    perror("exec");
    exit(254);
  }else if(pid<0){
    perror("fork");
    return 255;
  }
  return pid;
}