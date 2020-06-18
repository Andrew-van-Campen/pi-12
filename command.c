//This code interprets commands from the user.

#include "global.h"
#include "command.h"

//Print invalid setting message.
void settingError()
{
    printf("ERROR: Invalid setting.\n");
}

/*Take input from user; return an integer to main() function, indicating which function to run
  0 - do nothing (ERROR or invalid input)
  1 - run()
  2 - view()
  3 - reset()
  4 - setMeas()
  5 - setSite()
  6 - setPath()
  7 - setPort()
  8 - setBaud()
  9 - setFormat()
  10 - sendCommand()
  */
int command(int number, char **args)
{
    //No commands entered; return 0.
    if (number == 1)
    {
        printf("No commands entered. Type ./pi-12 followed by a command.\n");
        return 0;
    }
    //'run' entered; return 1.
    if (strcmp(*(args + 1), "run") == 0)
    {
        return 1;
    }
    //'view' entered; return 2.
    else if (strcmp(*(args + 1), "view") == 0)
    {
        return 2;
    }
    //'reset' entered; double check with user.
    else if (strcmp(*(args + 1), "reset") == 0)
    {
        printf("Restore all settings to default values? [y/n]: ");
        char c = getc(stdin);
        //If user confirms reset, return 3; if not, return 0.
        if (c == 'y' || c == 'Y')
        {
            return 3;
        }
        else
        {
            return 0;
        }
    }
    //'set' entered; determine whether setting is valid.
    else if (strcmp(*(args + 1), "set") == 0)
    {
        //Not enough arguments for this to be a valid setting; return 0.
        if (number < 4)
        {
            settingError();
            return 0;
        }
        //'set MEAS#' entered.
        if (*(*(args + 2) + 0) == 'M' &&
                *(*(args + 2) + 1) == 'E' &&
                *(*(args + 2) + 2) == 'A' &&
                *(*(args + 2) + 3) == 'S' &&
                *(*(args + 2) + 4) - 48 >= 0 && *(*(args + 2) + 4) - 48 <= num - 1)
        {
            //Not enough arguments for this to be a valid setting; return 0.
            if (number < 5)
            {
                settingError();
                return 0;
            }
            //'set MEAS# ENABLED' entered.
            if (strcmp(*(args + 3), "ENABLED") == 0)
            {
                //Should have string length of 1.
                if (strlen(*(args + 4)) != 1)
                {
                    settingError();
                    return 0;
                }
                //If the value is 0 or 1, return 4; otherwise return 0.
                if (**(args + 4) == '0' || **(args + 4) == '1')
                {
                    return 4;
                }
                else
                {
                    settingError();
                    return 0;
                }
            }
            //'set MEAS# NAME' entered.
            else if (strcmp(*(args + 3), "NAME") == 0)
            {
                //If name is not too long, return 4; otherwise return 0.
                if (strlen(*(args + 4)) <= 8)
                {
                    return 4;
                }
                else
                {
                    settingError();
                    return 0;
                }
            }
            //'set MEAS# COMMAND' entered.
            else if (strcmp(*(args + 3), "COMMAND") == 0)
            {
                //Check that the command is not too long.
                if (strlen(*(args + 4)) > 8)
                {
                    settingError();
                    return 0;
                }
                //The first character must be a valid SDI-12 address.
                if (**(args + 4) - 48 < 0 || **(args + 4) - 48 > 9)
                {
                    settingError();
                    return 0;
                }
                //The last character must be '!'.
                if (*(*(args + 4) + strlen(*(args + 4)) - 1) != '!')
                {
                    settingError();
                    return 0;
                }
                //If the above checks are passed, return 4.
                return 4;
            }
            //'set MEAS# MEASUREMENT' entered.
            else if (strcmp(*(args + 3), "MEASUREMENT") == 0)
            {
                //Should have string length of 1.
                if (strlen(*(args + 4)) != 1)
                {
                    settingError();
                    return 0;
                }
                //If the value is an integer between 1 and 9, return 4; otherwise return 0.
                if (**(args + 4) - 48 >= 1 && **(args + 4) - 48 <= 9)
                {
                    return 4;
                }
                else
                {
                    settingError();
                    return 0;
                }
            }
            //'set MEAS# INTERVAL' or 'set MEAS# START' entered.
            else if (strcmp(*(args + 3), "INTERVAL") == 0 || strcmp(*(args + 3), "START") == 0)
            {
                //Should have string length of 8.
                if (strlen(*(args + 4)) != 8)
                {
                    settingError();
                    return 0;
                }
                //The string should represent a time:
                //Check for colons.
                if (*(*(args + 4) + 2) != ':' || *(*(args + 4) + 5) != ':')
                {
                    settingError();
                    return 0;
                }
                //Check the hour digits.
                if (**(args + 4) - 48 == 0 || **(args + 4) - 48 == 1)
                {
                    if (*(*(args + 4) + 1) - 48 < 0 || *(*(args + 4) + 1) - 48 > 9)
                    {
                        settingError();
                        return 0;
                    }
                }
                else if (**(args + 4) - 48 == 2)
                {
                    if (*(*(args + 4) + 1) - 48 < 0 || *(*(args + 4) + 1) - 48 > 3)
                    {
                        settingError();
                        return 0;
                    }
                }
                else
                {
                    settingError();
                    return 0;
                }
                //Check the minute and second digits.
                if (*(*(args + 4) + 3) - 48 < 0 || *(*(args + 4) + 3) - 48 > 5 ||
                        *(*(args + 4) + 4) - 48 < 0 || *(*(args + 4) + 4) - 48 > 9 ||
                        *(*(args + 4) + 6) - 48 < 0 || *(*(args + 4) + 6) - 48 > 5 ||
                        *(*(args + 4) + 7) - 48 < 0 || *(*(args + 4) + 7) - 48 > 9)
                {
                    settingError();
                    return 0;
                }
                //If the above checks are passed, return 4.
                return 4;
            }
            //None of the above 'set MEAS#' options entered; invalid setting; return 0.
            else
            {
                settingError();
                return 0;
            }
        }
        //'set SITE' entered.
        else if (strcmp(*(args + 2), "SITE") == 0)
        {
            //Check that the name is not too long.
            if (strlen(*(args + 3)) > 20)
            {
                settingError();
                return 0;
            }
            //Check that the name contains no spaces.
            for (int i = 0; i <= strlen(*(args + 3)) - 1; i++)
            {
                if (*(*(args + 3) + i) == ' ')
                {
                    settingError();
                    return 0;
                }
            }
            //If the above checks are passed, return 5.
            return 5;
        }
        //'set PATH' entered.
        else if (strcmp(*(args + 2), "PATH") == 0)
        {
            //If path name is not too long, return 6; otherwise return 0.
            if (strlen(*(args + 3)) <= 30)
            {
                return 6;
            }
            else
            {
                settingError();
                return 0;
            }
        }
        //'set PORT' entered.
        else if (strcmp(*(args + 2), "PORT") == 0)
        {
            //If port name is not too long, return 7; otherwise return 0.
            if (strlen(*(args + 3)) <= 12)
            {
                return 7;
            }
            else
            {
                settingError();
                return 0;
            }
        }
        //'set BAUD' entered.
        else if (strcmp(*(args + 2), "BAUD") == 0)
        {
            //Check that the string doesn't have too many characters.
            if (strlen(*(args + 3)) > 6)
            {
                settingError();
                return 0;
            }
            //Check that every character is a digit.
            for (int i = 0; i <= strlen(*(args + 3)) - 1; i++)
            {
                if (*(*(args + 3) + i) - 48 < 0 || *(*(args + 3) + i) - 48 > 9)
                {
                    settingError();
                    return 0;
                }
            }
            //If the above checks are passed, return 8.
            return 8;
        }
        //'set FORMAT' entered.
        else if (strcmp(*(args + 2), "FORMAT") == 0)
        {
            //Check that the string has the right number of characters.
            if (strlen(*(args + 3)) != 3)
            {
                settingError();
                return 0;
            }
            //Check that the string is the correct format:
            //The first character must be 5-8.
            if (**(args + 3) - 48 < 5 || **(args + 3) - 48 > 8)
            {
                settingError();
                return 0;
            }
            //The second character must be E, O, or N.
            if (*(*(args + 3) + 1) != 'E' && *(*(args + 3) + 1) != 'O' && *(*(args + 3) + 1) != 'N')
            {
                settingError();
                return 0;
            }
            //The last character must be 1 or 2.
            if (*(*(args + 3) + 2) - 48 != 1 && *(*(args + 3) + 2) - 48 != 2)
            {
                settingError();
                return 0;
            }
            //If the above checks are passed, return 9.
            return 9;
        }
        //None of the above 'set' options entered; invalid setting; return 0.
        else
        {
            settingError();
            return 0;
        }
    }
    //'send' entered; return 10;
    else if (strcmp(*(args + 1), "send") == 0)
    {
        //If no SDI-12 command was entered, return 0; otherwise return 10.
        if (number < 3)
        {
            printf("ERROR: No SDI-12 command entered.\n");
            return 0;
        }
        else
        {
            return 10;
        }
    }
    //None of the above commands entered; not a recognized command; return 0.
    else
    {
        printf("ERROR: Not a recognized command.\n");
        return 0;
    }
    //Return 0 here as a fail-safe.
    return 0;
}
