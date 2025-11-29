#include "../include/tp1.h"

int main() {
    char *argv[] = {"ls", NULL};
    int code = executer(argv);
    printf("\nCode retour : %d\n", code);
    return 0;
}
