#include "../include/tp1.h"

int main(int argc,char* argv[]){
  if(argc=!2){
   printf("il faut un deux argument : fichier a executer et fichier a traiter");
    return -1;
  }
execFile(argv[1]);

}