//This code handles settings.

#include <stdio.h>

//Print settings to the screen.
int view()
{
    FILE *settings = fopen(".datalogger-settings", "r");
    char c;
    while (!feof(settings))
    {
        c = getc(settings);
        if (c != EOF)
        {
            putc(c, stdout);
        }
    }
    fclose(settings);
    return 0;
}

//Change a setting.
int set(char *setting, char *value)
{
    if (0)
    {

    }
    else
    {
        printf("ERROR: Not a recognized setting.\n");
    }
    return 0;
}
