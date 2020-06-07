//This code handles most general datalogger functionality.

#include "command.h"
#include "settings.h"
#include <time.h>

void run()
{
    while (1)
    {

    }
}

int main(int argc, char **argv)
{
    //Load settings.
    load();
    //Interpret command from user.
    switch(command(argc, argv))
    {
        case 0:
            break;
        case 1:
            run();
            break;
        case 2:
            view();
            break;
        case 3:
            set(*(argv + 2), *(argv + 3), *(argv + 4));
            break;
        case 4:
            reset();
            break;
    }
    return 0;
}
