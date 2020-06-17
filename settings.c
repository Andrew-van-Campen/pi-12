//This code handles settings.

#include "global.h"
#include "settings.h"

//Create a new settings settings_file with default settings.
void reset()
{
    settings_file = fopen(".settings", "w");
    fprintf(settings_file, ".|/dev/ttyACM0\n");
    for (int i = 0; i <= num - 1; i++)
    {
        fprintf(settings_file, "0|MEAS%d|0M!|1|01:00:00|00:00:00\n", i);
    }
    fclose(settings_file);
}

//Load settings from file.
void load()
{
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
    //DATA
    data_path = (char *) calloc(51, sizeof(char));
    while (c != '|')
    {
        *(data_path + pos) = c;
        pos++;
        c = fgetc(settings_file);
    }
    *(data_path + pos) = '\0';
    pos = 0;
    c = fgetc(settings_file);
    //PORT
    port_name = (char *) calloc(13, sizeof(char));
    while (c != '\n')
    {
        *(port_name + pos) = c;
        pos++;
        c = fgetc(settings_file);
    }
    *(port_name + pos) = '\0';
    pos = 0;
    c = fgetc(settings_file);
    //Measurement settings
    MEAS = (struct measurement *) calloc(num, sizeof(struct measurement));
    for (int i = 0; i <= num - 1; i++)
    {
        //ENABLED
        (MEAS + i)->ENABLED = c - 48;
        c = fgetc(settings_file);
        c = fgetc(settings_file);
        //NAME
        (MEAS + i)->NAME = (char *) calloc(9, sizeof(char));
        while (c != '|')
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
        while (c != '|')
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
        while (c != '|')
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
        //value
        (MEAS + i)->value = "";
    }
    fclose(settings_file);
}

//Save settings in file.
void save()
{
    settings_file = fopen(".settings", "w");
    fprintf(settings_file, "%s|%s\n", data_path, port_name);
    for (int i = 0; i <= num - 1; i++)
    {
        fprintf(settings_file, "%d|%s|%s|%d|%s|%s\n",
                (MEAS + i)->ENABLED,
                (MEAS + i)->NAME,
                (MEAS + i)->COMMAND,
                (MEAS + i)->MEASUREMENT,
                (MEAS + i)->INTERVAL,
                (MEAS + i)->START);
    }
    fclose(settings_file);
}

//Print settings to the screen.
void view()
{
    printf("---------------");
    for (int i = 0; i <= num - 1; i++)
    {
        printf("--------");
        if (i < num - 1)
        {
            printf("----");
        }
    }
    printf("\n");
    //Data save path
    printf("DATA           %s\n", data_path);
    //Port name
    printf("PORT           %s\n", port_name);
    printf("---------------");
    for (int i = 0; i <= num - 1; i++)
    {
        printf("--------");
        if (i < num - 1)
        {
            printf("----");
        }
    }
    printf("\n");
    //Measurement labels
    printf("               ");
    for (int i = 0; i <= num - 1; i++)
    {
        printf("MEAS%d       ", i);
    }
    printf("\n");
    //ENABLED
    printf("ENABLED        ");
    for (int i = 0; i <= num - 1; i++)
    {
        printf("%d           ", (MEAS + i)->ENABLED);
    }
    printf("\n");
    //NAME
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
    //COMMAND
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
    //MEASUREMENT
    printf("MEASUREMENT    ");
    for (int i = 0; i <= num - 1; i++)
    {
        printf("%d           ", (MEAS + i)->MEASUREMENT);
    }
    printf("\n");
    //INTERVAL
    printf("INTERVAL       ");
    for (int i = 0; i <= num - 1; i++)
    {
        printf("%s    ", (MEAS + i)->INTERVAL);
    }
    printf("\n");
    //START
    printf("START          ");
    for (int i = 0; i <= num - 1; i++)
    {
        printf("%s    ", (MEAS + i)->START);
    }
    printf("\n");
    printf("---------------");
    for (int i = 0; i <= num - 1; i++)
    {
        printf("--------");
        if (i < num - 1)
        {
            printf("----");
        }
    }
    printf("\n");
}

//Change a measurement setting.
void setMeas(char *label, char *setting, char *value)
{
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
    save();
}

//Set data path.
void setData(char *string)
{
    data_path = string;
    save();
}

//Set port name.
void setPort(char *string)
{
    port_name = string;
    save();
}
