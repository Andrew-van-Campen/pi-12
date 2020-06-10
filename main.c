//This code handles most general datalogger functionality.

#include "command.h"
#include "settings.h"

void run()
{
    //Create variables to store time-related information.
    time_t previous;
    time_t current;
    struct tm *info;
    //Create data file for the current month, if it doesn't already exist.
    time(&current);
    info = localtime(&current);
    char *filename = (char *) calloc(8, sizeof(char));
    if (info->tm_mon > 9)
    {
        sprintf(filename, "%d-%d.csv", info->tm_year + 1900, info->tm_mon + 1);
    }
    else
    {
        sprintf(filename, "%d-0%d.csv", info->tm_year + 1900, info->tm_mon + 1);
    }
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        file = fopen(filename, "w");
        //Create a column for each sensor in the data file.
    }
    fclose(file);
    //Create string to store measurements.
    char *measurements;
    //Execute loop endlessly.
    /*
    while (1)
    {
        previous = current;
        //Wait until time changes to check again.
        while (current == previous)
        {
            time(&current);
        }
        //For each sensor that's enabled, check whether it's time to take a measurement.
        for (int i = 0; i <= num - 1; i++)
        {
            if ((MEAS + i)->ENABLED &&
                    (current - (MEAS + i)->start) % (MEAS + i)->interval == 0)
            {
                //Send an SDI-12 command.
                //Parse and save measurements in data file.
                measurements = "0+3.14+2.718+1.414";
            }
        }
    }
    */
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
