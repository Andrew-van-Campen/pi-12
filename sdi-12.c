//This code handles communication with the hardware device.

#include "global.h"
#include "sdi-12.h"

int send(char *string)
{
    //Open serial port.
    int dev = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    //If unsuccessful, print an error statement.
    if (dev == -1)
    {
        printf("ERROR: Unable to open port %s\n", port);
        return -1;
    }
    //Write to port.
    int w = write(dev, string, strlen(string));
}
