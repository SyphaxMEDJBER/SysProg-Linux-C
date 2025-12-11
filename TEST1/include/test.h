#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>


/* EXO 1 */
void com1_puis_com2_et_com3(char **com1, char **com2, char **com3);

/* EXO 2 */
void exo2_signaux();

/* EXO 3 */
void TEE(char *filename, int append);

/* EXO 4 */
char **Ls2TabChar(char *rep);

#endif
