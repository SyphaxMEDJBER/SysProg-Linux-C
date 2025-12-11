#include "../include/test.h"

void TEE(char *filename, int append) {

    int fd;
    if (append)
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644); // Mode ajout (-a)
    else
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);  // Mode écrasement

    if (fd < 0) {                        // Vérifie que l'ouverture a réussi
        perror("open");
        exit(1);
    }

    char buf[256];                       // Buffer de lecture
    int r;

    while ((r = read(0, buf, sizeof(buf))) > 0) {  // Lit depuis stdin
        write(1, buf, r);               // Copie vers stdout
        write(fd, buf, r);              // Copie aussi vers le fichier
    }

    close(fd);                           // Fermeture du fichier
}

/* ========= MAIN — programme TEE ========= */

int main(int argc, char *argv[]) {

    if (argc == 2) {
        // ./TEE fichier → écrase le fichier et copie dedans
        TEE(argv[1], 0);
    }
    else if (argc == 3 && strcmp(argv[1], "-a") == 0) {
        // ./TEE -a fichier → ajoute à la fin du fichier
        TEE(argv[2], 1);
    }
    else {
        fprintf(stderr, "Usage : TEE [-a] fichier\n"); // Message d'erreur usage
        exit(1);
    }

    return 0;
}
