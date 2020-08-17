//This code interprets commands from the user.

#include "global.h"
#include "command.h"

//Print invalid setting message.
void settingError()
{
    printf("ERROR: Invalid setting.\n");
}

/*Take input from user; return an integer to main() function, indicating which function to run:
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
  10 - printResponse()
  11 - setPrepend()
  12 - setAppend()
  13 - setSkip()
  */
int command(int argc, char **argv)
{
    //No commands entered; return 0.
    if (argc == 1)
    {
        printf("No commands entered. Type ./pi-12 followed by a command.\n");
        return 0;
    }
    //'run' entered; return 1.
    if (strcmp(*(argv + 1), "run") == 0)
    {
        return 1;
    }
    //'view' entered; return 2.
    else if (strcmp(*(argv + 1), "view") == 0)
    {
        return 2;
    }
    //'reset' entered; double check with user.
    else if (strcmp(*(argv + 1), "reset") == 0)
    {
        printf("Restore all settings to default values? [y/n] ");
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
    else if (strcmp(*(argv + 1), "set") == 0)
    {
        //Not enough arguments for this to be a valid setting; return 0.
        if (argc < 4)
        {
            settingError();
            return 0;
        }
        //'set MEAS#' entered.
        if (*(*(argv + 2) + 0) == 'M' &&
                *(*(argv + 2) + 1) == 'E' &&
                *(*(argv + 2) + 2) == 'A' &&
                *(*(argv + 2) + 3) == 'S' &&
                *(*(argv + 2) + 4) - 48 >= 0 && *(*(argv + 2) + 4) - 48 <= num - 1)
        {
            //Not enough arguments for this to be a valid setting; return 0.
            if (argc < 5)
            {
                settingError();
                return 0;
            }
            //'set MEAS# ENABLED' entered.
            if (strcmp(*(argv + 3), "ENABLED") == 0)
            {
                //Should have string length of 1.
                if (strlen(*(argv + 4)) != 1)
                { settingError(); return 0; } //If the value is 0 or 1, return 4; otherwise return 0.
                if (**(argv + 4) == '0' || **(argv + 4) == '1')
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
            else if (strcmp(*(argv + 3), "NAME") == 0)
            {
                //If name is not too long, return 4; otherwise return 0.
                if (strlen(*(argv + 4)) <= 8)
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
            else if (strcmp(*(argv + 3), "COMMAND") == 0)
            {
                //Check that the command is not too long.
                if (strlen(*(argv + 4)) > 8)
                {
                    settingError();
                    return 0;
                }
                //The first character must be a valid SDI-12 address.
                if (**(argv + 4) - 48 < 0 || **(argv + 4) - 48 > 9)
                {
                    settingError();
                    return 0;
                }
                //The last character must be '!'.
                if (*(*(argv + 4) + strlen(*(argv + 4)) - 1) != '!')
                {
                    settingError();
                    return 0;
                }
                //If the above checks are passed, return 4.
                return 4;
            }
            //'set MEAS# MEASUREMENT' entered.
            else if (strcmp(*(argv + 3), "MEASUREMENT") == 0)
            {
                //Should have string length of 1.
                if (strlen(*(argv + 4)) != 1)
                {
                    settingError();
                    return 0;
                }
                //If the value is an integer between 1 and 9, return 4; otherwise return 0.
                if (**(argv + 4) - 48 >= 1 && **(argv + 4) - 48 <= 9)
                {
                    return 4;
                }
                else
                {
                    settingError();
                    return 0;
                }
            }
            //'set MEAS# INTERVAL' entered.
            else if (strcmp(*(argv + 3), "INTERVAL") == 0)
            {
                //Should have string length of 8.
                if (strlen(*(argv + 4)) != 8)
                {
                    settingError();
                    return 0;
                }
                //The string should represent a time:
                //Check for colons.
                if (*(*(argv + 4) + 2) != ':' || *(*(argv + 4) + 5) != ':')
                {
                    settingError();
                    return 0;
                }
                //Check the hour digits.
                if (**(argv + 4) - 48 == 0 || **(argv + 4) - 48 == 1)
                {
                    if (*(*(argv + 4) + 1) - 48 < 0 || *(*(argv + 4) + 1) - 48 > 9)
                    {
                        settingError();
                        return 0;
                    }
                }
                else if (**(argv + 4) - 48 == 2)
                {
                    if (*(*(argv + 4) + 1) - 48 < 0 || *(*(argv + 4) + 1) - 48 > 3)
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
                if (*(*(argv + 4) + 3) - 48 < 0 || *(*(argv + 4) + 3) - 48 > 5 ||
                        *(*(argv + 4) + 4) - 48 < 0 || *(*(argv + 4) + 4) - 48 > 9 ||
                        *(*(argv + 4) + 6) - 48 < 0 || *(*(argv + 4) + 6) - 48 > 5 ||
                        *(*(argv + 4) + 7) - 48 < 0 || *(*(argv + 4) + 7) - 48 > 9)
                {
                    settingError();
                    return 0;
                }
                //Can't be 00:00:00.
                if (*(*(argv + 4) + 0) - 48 == 0 && *(*(argv + 4) + 1) - 48 == 0 &&
                        *(*(argv + 4) + 3) - 48 == 0 && *(*(argv + 4) + 4) - 48 == 0 &&
                        *(*(argv + 4) + 6) - 48 == 0 && *(*(argv + 4) + 7) - 48 == 0)
                {
                    settingError();
                    return 0;
                }
                //If the above checks are passed, return 4.
                return 4;
            }
            //'set MEAS# START' entered.
            else if (strcmp(*(argv + 3), "START") == 0)
            {
                //Should have string length of 8.
                if (strlen(*(argv + 4)) != 8)
                {
                    settingError();
                    return 0;
                }
                //The string should represent a time:
                //Check for colons.
                if (*(*(argv + 4) + 2) != ':' || *(*(argv + 4) + 5) != ':')
                {
                    settingError();
                    return 0;
                }
                //Check the hour digits.
                if (**(argv + 4) - 48 == 0 || **(argv + 4) - 48 == 1)
                {
                    if (*(*(argv + 4) + 1) - 48 < 0 || *(*(argv + 4) + 1) - 48 > 9)
                    {
                        settingError();
                        return 0;
                    }
                }
                else if (**(argv + 4) - 48 == 2)
                {
                    if (*(*(argv + 4) + 1) - 48 < 0 || *(*(argv + 4) + 1) - 48 > 3)
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
                if (*(*(argv + 4) + 3) - 48 < 0 || *(*(argv + 4) + 3) - 48 > 5 ||
                        *(*(argv + 4) + 4) - 48 < 0 || *(*(argv + 4) + 4) - 48 > 9 ||
                        *(*(argv + 4) + 6) - 48 < 0 || *(*(argv + 4) + 6) - 48 > 5 ||
                        *(*(argv + 4) + 7) - 48 < 0 || *(*(argv + 4) + 7) - 48 > 9)
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
        else if (strcmp(*(argv + 2), "SITE") == 0)
        {
            //Check that the name is not too long.
            if (strlen(*(argv + 3)) > 20)
            {
                settingError();
                return 0;
            }
            //Check that the name contains no spaces.
            for (int i = 0; i <= strlen(*(argv + 3)) - 1; i++)
            {
                if (*(*(argv + 3) + i) == ' ')
                {
                    settingError();
                    return 0;
                }
            }
            //If the above checks are passed, return 5.
            return 5;
        }
        //'set PATH' entered.
        else if (strcmp(*(argv + 2), "PATH") == 0)
        {
            //If path name is not too long, return 6; otherwise return 0.
            if (strlen(*(argv + 3)) <= 30)
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
        else if (strcmp(*(argv + 2), "PORT") == 0)
        {
            //If port name is not too long, return 7; otherwise return 0.
            if (strlen(*(argv + 3)) <= 12)
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
        else if (strcmp(*(argv + 2), "BAUD") == 0)
        {
            //Check that the string doesn't have too many characters.
            if (strlen(*(argv + 3)) > 6)
            {
                settingError();
                return 0;
            }
            //Check that every character is a digit.
            for (int i = 0; i <= strlen(*(argv + 3)) - 1; i++)
            {
                if (*(*(argv + 3) + i) - 48 < 0 || *(*(argv + 3) + i) - 48 > 9)
                {
                    settingError();
                    return 0;
                }
            }
            //If the number is a valid baud rate, return 8; otherwise return 0.
            int b = atoi(*(argv + 3));
            if (b == 0 || b == 50 || b == 75 ||
                    b == 110 || b == 134 || b == 150 || b == 200 || b == 300 || b == 600 ||
                    b == 1200 || b == 1800 || b == 2400 || b == 4800 || b == 9600 ||
                    b == 19200 || b == 38400 || b == 57600 ||
                    b == 115200 || b == 230400)
            {
                return 8;
            }
            else
            {
                settingError();
                return 0;
            }
        }
        //'set FORMAT' entered.
        else if (strcmp(*(argv + 2), "FORMAT") == 0)
        {
            //Check that the string has the right number of characters.
            if (strlen(*(argv + 3)) != 3)
            {
                settingError();
                return 0;
            }
            //Check that the string is the correct format:
            //The first character must be 5-8.
            if (**(argv + 3) - 48 < 5 || **(argv + 3) - 48 > 8)
            {
                settingError();
                return 0;
            }
            //The second character must be E, O, or N.
            if (*(*(argv + 3) + 1) != 'E' && *(*(argv + 3) + 1) != 'O' && *(*(argv + 3) + 1) != 'N')
            {
                settingError();
                return 0;
            }
            //The last character must be 1 or 2.
            if (*(*(argv + 3) + 2) - 48 != 1 && *(*(argv + 3) + 2) - 48 != 2)
            {
                settingError();
                return 0;
            }
            //If the above checks are passed, return 9.
            return 9;
        }
        //'set PREPEND' entered.
        else if (strcmp(*(argv + 2), "PREPEND") == 0)
        {
            //Check that the string isn't too long.
            if (strlen(*(argv + 3)) > 20)
            {
                settingError();
                return 0;
            }
            //Do not allow '|' character.
            for (int i = 0; *(*(argv + 3) + i) != '\0'; i++)
            {
                if (*(*(argv + 3) + i) == '|')
                {
                    settingError();
                    return 0;
                }
            }
            //If the above checks are passed, return 11.
            return 11;
        }
        //'set APPEND' entered.
        else if (strcmp(*(argv + 2), "APPEND") == 0)
        {
            //Check that the string isn't too long.
            if (strlen(*(argv + 3)) > 20)
            {
                settingError();
                return 0;
            }
            //Do not allow '|' character.
            for (int i = 0; *(*(argv + 3) + i) != '\0'; i++)
            {
                if (*(*(argv + 3) + i) == '|')
                {
                    settingError();
                    return 0;
                }
            }
            //If the above checks are passed, return 12.
            return 12;
        }
        //'set SKIP' entered.
        else if (strcmp(*(argv + 2), "SKIP") == 0)
        {
            //Check the the number of characters to skip makes sense.
            if (atoi(*(argv + 3)) < 0 || atoi(*(argv + 3)) > 9)
            {
                settingError();
                return 0;
            }
            //If the above checks are passed, return 13.
            return 13;
        }
        //None of the above 'set' options entered; invalid setting; return 0.
        else
        {
            settingError();
            return 0;
        }
    }
    //'send' entered.
    else if (strcmp(*(argv + 1), "send") == 0)
    {
        //If no SDI-12 command was entered, return 0; otherwise return 10.
        if (argc < 3)
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
