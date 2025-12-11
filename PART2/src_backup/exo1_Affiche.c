#include "../include/tp2.h"
int fin=0;
char *msg;
void fctALRM(int sig){
    fin=1;
}

int main(int argc,char* argv[]){
    if(argc<3) exit(1);

    int N=atoi(argv[1]);
    msg=argv[2];

    signal(SIGALRM,fctALRM);//quand SIGALRM arrive appel fctALRM 
    alarm(N);//un signal SIGALRM apres N secondes 
    while(fin!=1){
        printf("%s\n",msg);
        fflush(stdout);
        sleep(1);
    }



    return 0;

}