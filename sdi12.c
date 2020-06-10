//This code handles communication with SDI-12 sensors.

#include "global.h"
#include "sdi-12.h"

void test()
{
    int dev = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    if (dev == -1)
    {
        printf("ERROR: Could not open port %s.\n", port);
        return;
    }
    fcntl(dev, F_SETFL, FNDELAY);
    close(dev);
}
