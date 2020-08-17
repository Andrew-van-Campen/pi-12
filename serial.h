#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

char *getResponse(char *command);
void printResponse(char *command);
