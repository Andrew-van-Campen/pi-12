//This code handles most general datalogger functionality.

#include "command.h"
#include "settings.h"

void run()
{
    time_t previous;
    time_t current;
    time(&current);
    while (1)
    {
        previous = current;
        while (current == previous)
        {
            time(&current);
        }
        for (int i = 0; i <= num - 1; i++)
        {
            if ((MEAS + i)->ENABLED &&
                    (current - (MEAS + i)->start) % (MEAS + i)->interval == 0)
            {
                printf("%s\n", (MEAS + i)->NAME);
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
