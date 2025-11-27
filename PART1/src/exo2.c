#include "../include/tp1.h"

void afficherArgv(char **arg){
    int i=0;
    while (arg[i]!=NULL)
    {
     printf("Arg %d : %s\n",i,arg[i]);
     i++;

    }
    
}