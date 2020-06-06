//This code handles settings.

#include "settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define num 6 //Number of settings in total.

//Create a new settings file with default settings.
int restore()
{
    FILE *file = fopen(".datalogger-settings", "w");
    fprintf(file, "MEAS1_ENABLED|0\n");
    fprintf(file, "MEAS1_NAME|MEAS1\n");
    fprintf(file, "MEAS1_COMMAND|0M!\n");
    fprintf(file, "MEAS1_POSITION|0\n");
    fprintf(file, "MEAS1_TIME_INTERVAL|00:10:00\n");
    fprintf(file, "MEAS1_START_TIME|00:00:00\n");
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
    //Create arrays to hold settings and values.
    settings = calloc(num, sizeof(char)*25);
    for (int i = 0; i <= num - 1; i++)
    {
        *(settings + i) = calloc(25, sizeof(char));
    }
    values = calloc(num, sizeof(char)*25);
    for (int i = 0; i <= num - 1; i++)
    {
        *(values + i) = calloc(25, sizeof(char));
    }
    //Read file and fill arrays.
    char c = fgetc(file);
    for (int i = 0; i <= num - 1; i++)
    {
        for (int j = 0; c != '|'; j++)
        {
            *(*(settings + i) + j) = c;
            c = fgetc(file);
        }
        c = fgetc(file);
        for (int j = 0; c != '\n'; j++)
        {
            *(*(values + i) + j) = c;
            c = fgetc(file);
        }
        c = fgetc(file);
    }
    fclose(file);
    return 0;
}

//Save settings to file.
int save()
{
    FILE *file = fopen(".datalogger-settings", "w");
    for (int i = 0; i <= num - 1; i++)
    {
        fprintf(file, "%s|%s\n", *(settings + i), *(values + i));
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
    //Option to restore all settings to defaults.
    if (strcmp(setting, "ALL") == 0 && strcmp(value, "DEFAULT") == 0)
    {
        restore();
        return 0;
    }
    //Search array for setting.
    int found = 0;
    int index = 0;
    while (index <= num - 1 && !found)
    {
        if (strcmp(*(settings + index), setting) == 0)
        {
            found = 1;
        }
        else
        {
            index++;
        }
    }
    //If found, set and save.
    if (found)
    {
        //TODO: Check that the setting is valid.
        *(values + index) = value;
        save();
    }
    else
    {
        printf("ERROR: Not a recognized setting.\n");
    }
    return 0;
}
