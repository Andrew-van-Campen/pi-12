//This code handles settings.

#include "global.h"
#include "settings.h"

//Create a new settings settings_file with default settings.
void reset()
{
    settings_file = fopen(settings_filepath, "w");
    fprintf(settings_file, "Test|%s/data\n", getenv("HOME"));
    fprintf(settings_file, "/dev/ttyACM0|9600|8N1\n");
    for (int i = 0; i <= num - 1; i++)
    {
        fprintf(settings_file, "0|MEAS%d|0M!|1|00:30:00|00:00:00\n", i);
    }
    fclose(settings_file);
}

//Load settings from file.
void load()
{
    //Set program file paths.
    char *home = getenv("HOME");
    settings_filepath = (char *) calloc(30, sizeof(char));
    sprintf(settings_filepath, "%s/.pi-12_settings", home);
    process_filepath = (char *) calloc(30, sizeof(char));
    sprintf(process_filepath, "%s/.pi-12_process", home);
    //Create a settings file if one doesn't exist.
    settings_file = fopen(settings_filepath, "r");
    if (settings_file == NULL)
    {
        reset();
        settings_file = fopen(settings_filepath, "r");
    }
    //Read settings from file.
    char c = fgetc(settings_file);
    int pos = 0;
    //Data settings:
    //SITE
    site_name = (char *) calloc(21, sizeof(char));
    while (c != '|')
    {
        *(site_name + pos) = c;
        pos++;
        c = fgetc(settings_file);
    }
    *(site_name + pos) = '\0';
    pos = 0;
    c = fgetc(settings_file);
    //PATH
    data_path = (char *) calloc(31, sizeof(char));
    while (c != '\n')
    {
        *(data_path + pos) = c;
        pos++;
        c = fgetc(settings_file);
    }
    *(data_path + pos) = '\0';
    pos = 0;
    c = fgetc(settings_file);
    //Serial port settings:
    //PORT
    port_name = (char *) calloc(13, sizeof(char));
    while (c != '|')
    {
        *(port_name + pos) = c;
        pos++;
        c = fgetc(settings_file);
    }
    *(port_name + pos) = '\0';
    pos = 0;
    c = fgetc(settings_file);
    //BAUD
    baud_rate = (char *) calloc(7, sizeof(char));
    while (c != '|')
    {
        *(baud_rate + pos) = c;
        pos++;
        c = fgetc(settings_file);
    }
    *(baud_rate + pos) = '\0';
    pos = 0;
    c = fgetc(settings_file);
    //FORMAT
    serial_format = (char *) calloc(4, sizeof(char));
    while (c != '\n')
    {
        *(serial_format + pos) = c;
        pos++;
        c = fgetc(settings_file);
    }
    *(serial_format + pos) = '\0';
    pos = 0;
    c = fgetc(settings_file);
    //Measurement settings:
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

//Save settings to file.
void save()
{
    settings_file = fopen(settings_filepath, "w");
    fprintf(settings_file, "%s|%s\n", site_name, data_path);
    fprintf(settings_file, "%s|%s|%s\n", port_name, baud_rate, serial_format);
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

//Set site name.
void setSite(char *string)
{
    site_name = string;
    save();
}

//Set data path.
void setPath(char *string)
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

//Set baud rate
void setBaud(char *string)
{
    baud_rate = string;
    save();
}

//Set serial format.
void setFormat(char *string)
{
    serial_format = string;
    save();
}

//Helper function for view()
void printLine()
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
}

//Print settings to the screen.
void view()
{
    printLine();
    //Data settings
    printf("Data Settings:\n");
    printf("\n");
    printf("SITE           %s\n", site_name);
    printf("PATH           %s\n", data_path);
    printLine();
    //Serial port settings
    printf("Serial Port Settings:\n");
    printf("\n");
    printf("PORT           %s\n", port_name);
    printf("BAUD           %s\n", baud_rate);
    printf("FORMAT         %s\n", serial_format);
    printLine();
    //Measurement settings
    printf("Measurement Settings:\n");
    printf("\n");
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
    printLine();
}
