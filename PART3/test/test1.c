#include "../include/tp3.h"                   // prototypes Init() et Reserve()

int main(int argc, char *argv[]) { // argc = nb arguments, argv = liste des arguments

    if (argc == 2 &&                // si on a 2 arguments
        strcmp(argv[1], "init") == 0)  // et que le mot est "init"
        return Init();              // exécuter Init()

    if (argc == 3 &&                // si on a 3 arguments
        strcmp(argv[1], "reserve") == 0) // et que le 1er mot est "reserve"
        return Reserve(atoi(argv[2]));   // convertir n et appeler Reserve(n)

    return 0;                      // aucun cas, on quitte
}
