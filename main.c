//This code handles most general datalogger functionality.

#include "command.h"
#include "settings.h"

void run()
{
    time_t previous;
    time_t current;
    char *command;
    time(&current);
    while (1)
    {
        previous = current;
        //Wait until time changes to check again.
        while (current == previous)
        {
            time(&current);
        }
        //For each sensor that's enabled, check whether it's time to take a measurement.
        for (int i = 0; i <= num - 1; i++)
        {
            if ((MEAS + i)->ENABLED &&
                    (current - (MEAS + i)->start) % (MEAS + i)->interval == 0)
            {
                //Send an SDI-12 command.
                command = (char *) calloc(17, sizeof(char));
                strcat(command, "./sdi-12 ");
                strcat(command, (MEAS + 0)->COMMAND);
                system(command);
                free(command);
            }
        }
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
