#include "../include/tp3.h"

int main(int argc, char *argv[]) {



    if (argc == 3 && strcmp(argv[1], "ls") == 0)
        LsDansFichier(argv[2],"data1.txt");                   

    return 0;
}
