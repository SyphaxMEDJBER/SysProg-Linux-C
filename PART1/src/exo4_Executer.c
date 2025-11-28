#include"../include/tp1.h"

int executer(char** argv){
  int ret;
  int pid=fork();

  if(pid==0){
    execvp(argv[0],argv);
    perror("execvp");


  }else if(pid>0){
    printf("en attente d'execution:  \n");
    wait(&ret);
    printf("execution terminée,code= %d",WEXITSTATUS(ret));

  }else{
    perror("fork");
    return 255;
  }

  return WEXITSTATUS(ret);

}
