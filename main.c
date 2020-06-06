//This code handles most general datalogger functionality.

#include "help.h"
#include "settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int run()
{
    while (1)
    {

    }
    return 0;
}

int main(int argc, char **argv)
{
    //Load settings.
    load();

    //In the case of no command entered, ask for a command.
    if (argc == 1)
    {
        printf("No command entered. Type ./dl followed by a command.\n");
        return 0;
    }

    //Interpret command from user.
    if (strcmp(*(argv + 1), "run") == 0)
    {
        run();
    }
    else if (strcmp(*(argv + 1), "view") == 0)
    {
        view();
    }
    else if (strcmp(*(argv + 1), "set") == 0)
    {
        if (argc >= 4)
        {
            set(*(argv + 2), *(argv + 3));
        }
        else
        {
            printf("ERROR: Not a recognized setting.\n");
        }
    }
    else if (strcmp(*(argv + 1), "help") == 0)
    {
        help();
    }
    else
    {
        printf("ERROR: Not a recognized command.\n");
    }

    return 0;
}
