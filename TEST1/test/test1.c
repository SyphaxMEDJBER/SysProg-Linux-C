#include "../include/test.h"

int main() {

    char *com1[] = {"./Affiche", "2", "Com1", NULL};
    char *com2[] = {"./Affiche", "3", "Com2", NULL};
    char *com3[] = {"./Affiche", "5", "Com3", NULL};

    com1_puis_com2_et_com3(com1, com2, com3);

    return 0;
}
