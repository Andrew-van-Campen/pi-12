//This code handles settings.

#include "global.h"
#include "settings.h"

//Create a new settings settings_file with default settings.
void reset()
{
    settings_file = fopen(".settings", "w");
    for (int i = 0; i <= num - 1; i++)
    {
        fprintf(settings_file, "0 MEAS%d 0M! 1 01:00:00 00:00:00\n", i);
    }
    fclose(settings_file);
}

//Load settings from file.
void load()
{
    port = "/dev/ttyACM0";
    //Allocate space in memory for settings.
    MEAS = (struct measurement *) calloc(num, sizeof(struct measurement));
    //Create a settings file if one doesn't exist.
    settings_file = fopen(".settings", "r");
    if (settings_file == NULL)
    {
        reset();
        settings_file = fopen(".settings", "r");
    }
    //Read settings from file.
    char c = fgetc(settings_file);
    int pos = 0;
    for (int i = 0; i <= num - 1; i++)
    {
        //ENABLED
        (MEAS + i)->ENABLED = c - 48;
        c = fgetc(settings_file);
        c = fgetc(settings_file);
        //NAME
        (MEAS + i)->NAME = (char *) calloc(9, sizeof(char));
        while (c != ' ')
        {
            *((MEAS + i)->NAME + pos) = c;
            pos++;
            c = fgetc(settings_file);
        }
        *((MEAS + i)->NAME + pos) = '\0';
        pos = 0;
        c = fgetc(settings_file);
        //COMMAND
        (MEAS + i)->COMMAND = (char *) calloc(9, sizeof(char));
        while (c != ' ')
        {
            *((MEAS + i)->COMMAND + pos) = c;
            pos++;
            c = fgetc(settings_file);
        }
        *((MEAS + i)->COMMAND + pos) = '\0';
        pos = 0;
        c = fgetc(settings_file);
        //MEASUREMENT
        (MEAS + i)->MEASUREMENT = c - 48;
        c = fgetc(settings_file);
        c = fgetc(settings_file);
        //INTERVAL
        (MEAS + i)->INTERVAL = (char *) calloc(9, sizeof(char));
        while (c != ' ')
        {
            *((MEAS + i)->INTERVAL + pos) = c;
            pos++;
            c = fgetc(settings_file);
        }
        *((MEAS + i)->INTERVAL + pos) = '\0';
        pos = 0;
        c = fgetc(settings_file);
        //START
        (MEAS + i)->START = (char *) calloc(9, sizeof(char));
        while (c != '\n')
        {
            *((MEAS + i)->START + pos) = c;
            pos++;
            c = fgetc(settings_file);
        }
        *((MEAS + i)->START + pos) = '\0';
        pos = 0;
        c = fgetc(settings_file);
        //interval
        (MEAS + i)->interval = 0;
        (MEAS + i)->interval += (*((MEAS + i)->INTERVAL + 0) - 48) * 10 * 3600;
        (MEAS + i)->interval += (*((MEAS + i)->INTERVAL + 1) - 48) * 1 * 3600;
        (MEAS + i)->interval += (*((MEAS + i)->INTERVAL + 3) - 48) * 10 * 60;
        (MEAS + i)->interval += (*((MEAS + i)->INTERVAL + 4) - 48) * 1 * 60;
        (MEAS + i)->interval += (*((MEAS + i)->INTERVAL + 6) - 48) * 10;
        (MEAS + i)->interval += (*((MEAS + i)->INTERVAL + 7) - 48) * 1;
        //start
        (MEAS + i)->start = 0;
        (MEAS + i)->start += (*((MEAS + i)->START + 0) - 48) * 10 * 3600;
        (MEAS + i)->start += (*((MEAS + i)->START + 1) - 48) * 1 * 3600;
        (MEAS + i)->start += (*((MEAS + i)->START + 3) - 48) * 10 * 60;
        (MEAS + i)->start += (*((MEAS + i)->START + 4) - 48) * 1 * 60;
        (MEAS + i)->start += (*((MEAS + i)->START + 6) - 48) * 10;
        (MEAS + i)->start += (*((MEAS + i)->START + 7) - 48) * 1;
    }
    fclose(settings_file);
}

//Print settings to the screen.
void view()
{
    printf("               ");
    for (int i = 0; i <= num - 1; i++)
    {
        printf("MEAS%d       ", i);
    }
    printf("\n");
    printf("ENABLED        ");
    for (int i = 0; i <= num - 1; i++)
    {
        printf("%d           ", (MEAS + i)->ENABLED);
    }
    printf("\n");
    printf("NAME           ");
    for (int i = 0; i <= num - 1; i++)
    {
        printf("%s    ", (MEAS + i)->NAME);
        for (int j = 1; j <= 8 - strlen((MEAS + i)->NAME); j++)
        {
            printf(" ");
        }
    }
    printf("\n");
    printf("COMMAND        ");
    for (int i = 0; i <= num - 1; i++)
    {
        printf("%s    ", (MEAS + i)->COMMAND);
        for (int j = 1; j <= 8 - strlen((MEAS + i)->COMMAND); j++)
        {
            printf(" ");
        }
    }
    printf("\n");
    printf("MEASUREMENT    ");
    for (int i = 0; i <= num - 1; i++)
    {
        printf("%d           ", (MEAS + i)->MEASUREMENT);
    }
    printf("\n");
    printf("INTERVAL       ");
    for (int i = 0; i <= num - 1; i++)
    {
        printf("%s    ", (MEAS + i)->INTERVAL);
    }
    printf("\n");
    printf("START          ");
    for (int i = 0; i <= num - 1; i++)
    {
        printf("%s    ", (MEAS + i)->START);
    }
    printf("\n");
}

//Change a setting.
void set(char *label, char *setting, char *value)
{
    //Change the setting.
    int index = *(label + 4) - 48;
    if (strcmp(setting, "ENABLED") == 0)
    {
        (MEAS + index)->ENABLED = *value - 48;
    }
    else if (strcmp(setting, "NAME") == 0)
    {
        (MEAS + index)->NAME = value;
    }
    else if (strcmp(setting, "COMMAND") == 0)
    {
        (MEAS + index)->COMMAND = value;
    }
    else if (strcmp(setting, "MEASUREMENT") == 0)
    {
        (MEAS + index)->MEASUREMENT = *value - 48;
    }
    else if (strcmp(setting, "INTERVAL") == 0)
    {
        (MEAS + index)->INTERVAL = value;
    }
    else if (strcmp(setting, "START") == 0)
    {
        (MEAS + index)->START = value;
    }
    //Save settings in file.
    settings_file = fopen(".settings", "w");
    for (int i = 0; i <= num - 1; i++)
    {
        fprintf(settings_file, "%d %s %s %d %s %s\n",
                (MEAS + i)->ENABLED,
                (MEAS + i)->NAME,
                (MEAS + i)->COMMAND,
                (MEAS + i)->MEASUREMENT,
                (MEAS + i)->INTERVAL,
                (MEAS + i)->START);
    }
    fclose(settings_file);
}
