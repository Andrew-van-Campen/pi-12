//This code interprets commands from the user.

#include "global.h"
#include "command.h"
#include "settings.h"

/*Take input from user; return an integer to main() function, indicating which function to run
  0 - do nothing (ERROR or invalid input)
  1 - run()
  2 - view()
  3 - set()
  4 - reset()
  */
int command(int number, char **args)
{
    if (number == 1)
    {
        printf("No commands entered. Type ./datalogger followed by a command.\n");
    }
    else if (strcmp(*(args + 1), "run") == 0)
    {
        return 1;
    }
    else if (strcmp(*(args + 1), "view") == 0)
    {
        return 2;
    }
    else if (strcmp(*(args + 1), "set") == 0)
    {
        if (number < 5)
        {
            printf("ERROR: Invalid setting.\n");
            return 0;
        }
        if (*(*(args + 2) + 0) != 'M' ||
                    *(*(args + 2) + 1) != 'E' ||
                    *(*(args + 2) + 2) != 'A' ||
                    *(*(args + 2) + 3) != 'S' ||
                    *(*(args + 2) + 4) - 48 < 0 || *(*(args + 2) + 4) - 48 > num - 1)
        {
            printf("ERROR: Invalid setting.\n");
            return 0;
        }
        if (strcmp(*(args + 3), "ENABLED") == 0)
        {
            if (strlen(*(args + 4)) > 1)
            {
                printf("ERROR: Invalid setting.\n");
                return 0;
            }
            if (*(*(args + 4) + 0) - 48 != 0 && *(*(args + 4) + 0) - 48 != 1)
            {
                printf("ERROR: Invalid setting.\n");
                return 0;
            }
        }
        else if (strcmp(*(args + 3), "NAME") == 0)
        {
            if (strlen(*(args + 4)) > 8)
            {
                printf("ERROR: Invalid setting.\n");
                return 0;
            }
        }
        else if (strcmp(*(args + 3), "COMMAND") == 0)
        {
            if (strlen(*(args + 4)) > 8)
            {
                printf("ERROR: Invalid setting.\n");
                return 0;
            }
            if (*(*(args + 4) + 0) - 48 < 0 || *(*(args + 4) + 0) - 48 > 9 ||
                    *(*(args + 4) + strlen(*(args + 4)) - 1) != '!')
            {
                printf("ERROR: Invalid setting.\n");
                return 0;
            }
        }
        else if (strcmp(*(args + 3), "MEASUREMENT") == 0)
        {
            if (strlen(*(args + 4)) > 1)
            {
                printf("ERROR: Invalid setting.\n");
                return 0;
            }
            if (*(*(args + 4) + 0) - 48 < 0 || *(*(args + 4) + 0) - 48 > 9)
            {
                printf("ERROR: Invalid setting.\n");
                return 0;
            }
        }
        else if (strcmp(*(args + 3), "INTERVAL") == 0)
        {
            if (strlen(*(args + 4)) != 8)
            {
                printf("ERROR: Invalid setting.\n");
                return 0;
            }
            if (*(*(args + 4) + 0) - 48 < 0 || *(*(args + 4) + 0) - 48 > 2 ||
                    *(*(args + 4) + 1) - 48 < 0 || *(*(args + 4) + 1) - 48 > 9 ||
                    (*(*(args + 4) + 0) - 48 == 2 && *(*(args + 4) + 1) - 48 > 3) ||
                    *(*(args + 4) + 2) != ':' ||
                    *(*(args + 4) + 3) - 48 < 0 || *(*(args + 4) + 3) - 48 > 5 ||
                    *(*(args + 4) + 4) - 48 < 0 || *(*(args + 4) + 4) - 48 > 9 ||
                    *(*(args + 4) + 5) != ':' ||
                    *(*(args + 4) + 6) - 48 < 0 || *(*(args + 4) + 6) - 48 > 5 ||
                    *(*(args + 4) + 7) - 48 < 0 || *(*(args + 4) + 7) - 48 > 9)
            {
                printf("ERROR: Invalid setting.\n");
                return 0;
            }
        }
        else if (strcmp(*(args + 3), "START") == 0)
        {
            if (strlen(*(args + 4)) != 8)
            {
                printf("ERROR: Invalid setting.\n");
                return 0;
            }
            if (*(*(args + 4) + 0) - 48 < 0 || *(*(args + 4) + 0) - 48 > 2 ||
                    *(*(args + 4) + 1) - 48 < 0 || *(*(args + 4) + 1) - 48 > 9 ||
                    (*(*(args + 4) + 0) - 48 == 2 && *(*(args + 4) + 1) - 48 > 3) ||
                    *(*(args + 4) + 2) != ':' ||
                    *(*(args + 4) + 3) - 48 < 0 || *(*(args + 4) + 3) - 48 > 5 ||
                    *(*(args + 4) + 4) - 48 < 0 || *(*(args + 4) + 4) - 48 > 9 ||
                    *(*(args + 4) + 5) != ':' ||
                    *(*(args + 4) + 6) - 48 < 0 || *(*(args + 4) + 6) - 48 > 5 ||
                    *(*(args + 4) + 7) - 48 < 0 || *(*(args + 4) + 7) - 48 > 9)
            {
                printf("ERROR: Invalid setting.\n");
                return 0;
            }
        }
        else
        {
            printf("ERROR: Invalid setting.\n");
            return 0;
        }
        return 3;
    }
    else if (strcmp(*(args + 1), "reset") == 0)
    {
        printf("Restore all settings to default values? [y/n]: ");
        char y;
        scanf("%c", &y);
        if (y == 89 || y == 121)
        {
            return 4;
        }
    }
    else
    {
        printf("ERROR: Not a recognized command.\n");
    }
    return 0;
}
