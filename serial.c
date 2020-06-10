//This code handles communication with the hardware device.

#include "global.h"
#include "settings.h"
#include "serial.h"

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int send(char *string)
{
    //Open serial port.
    int fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    //If unsuccessful...
    if (fd == -1)
    {
        printf("ERROR: Unable to open port %s\n", port);
        return -1;
    }
}
