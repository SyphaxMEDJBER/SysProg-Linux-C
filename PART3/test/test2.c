#include "../include/tp3.h"

int main(int argc, char *argv[]) {

    if (argc == 2 && strcmp(argv[1], "init") == 0)
        return Init();

    if (argc == 3 && strcmp(argv[1], "reserve") == 0)
        return Reserve(atoi(argv[2]));

    if (argc == 3 && strcmp(argv[1], "ls") == 0)
        Ls(argv[2]);                   

    return 0;
}
