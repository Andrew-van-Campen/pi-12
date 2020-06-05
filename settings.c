//This code handles settings.

#include "settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define num 5 //Number of settings in total.

//Create a new settings file with default settings.
int restore()
{
    FILE *file = fopen(".datalogger-settings", "w");
    fprintf(file, "MEAS1_ENABLED|0\n");
    fprintf(file, "MEAS1_START_TIME|00:00:00\n");
    fprintf(file, "MEAS1_TIME_INTERVAL|01:00:00\n");
    fprintf(file, "MEAS1_COMMAND|0M!\n");
    fprintf(file, "MEAS1_POSITION|0\n");
    fclose(file);
    return 0;
}

//Load settings from file.
int load()
{
    //Create a settings file if one doesn't exist.
    FILE *file = fopen(".datalogger-settings", "r");
    if (file == NULL)
    {
        restore();
        file = fopen(".datalogger-settings", "r");
    }
    //Load settings titles in an array.
    settings = calloc(num, sizeof(int));
    for (int i = 0; i <= num - 1; i++)
    {
        *(settings + i) = calloc(25, sizeof(char));
    }
    //Load settings values in an array.
    values = calloc(num, sizeof(int));
    for (int i = 0; i <= num - 1; i++)
    {
        *(values + i) = calloc(10, sizeof(char));
    }
    fclose(file);
    return 0;
}

//Print settings to the screen.
int view()
{
    FILE *file = fopen(".datalogger-settings", "r");
    char c;
    while (!feof(file))
    {
        c = getc(file);
        if (c != EOF)
        {
            putc(c, stdout);
        }
    }
    fclose(file);
    return 0;
}

//Change a setting.
int set(char *setting, char *value)
{
    if (strcmp(setting, "ALL") == 0 && strcmp(value, "DEFAULT") == 0)
    {
        restore();
    }
    else
    {
        printf("ERROR: Not a recognized setting.\n");
    }
    return 0;
}
