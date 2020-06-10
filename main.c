//This code handles most general datalogger functionality.

#include "command.h"
#include "settings.h"

//Variables to store time-related information.
time_t previous;
time_t current;
struct tm *info;
//Pointer and name for file.
FILE *file;
char *filename;

//Create data file for the current month, if it doesn't already exist.
void createFile()
{
    free(filename);
    filename = (char *) calloc(8, sizeof(char));
    if (info->tm_mon < 9)
    {
        sprintf(filename, "%d-0%d.csv", info->tm_year + 1900, info->tm_mon + 1);
    }
    else
    {
        sprintf(filename, "%d-%d.csv", info->tm_year + 1900, info->tm_mon + 1);
    }
    file = fopen(filename, "r");
    if (file == NULL)
    {
        file = fopen(filename, "w");
        //Create a column in the data file for each measurement.
        fprintf(file, ",,");
        for (int i = 0; i <= num - 1; i++)
        {
            if ((MEAS + i)->ENABLED)
            {
                fprintf(file, "%s,", (MEAS + i)->NAME);
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void run()
{
    time(&current);
    info = localtime(&current);
    createFile();
    //Create string to store measurements.
    char *measurements;
    //Execute loop endlessly.
    while (1)
    {
        previous = current;
        //Wait until time changes to check again.
        while (current == previous)
        {
            time(&current);
        }
        info = localtime(&current);
        //If it's a new month, create a new data file.
        if (info->tm_mday == 1 && info->tm_hour == 0 && info->tm_min == 0)
        {
            createFile();
        }
        //For each sensor that's enabled, check whether it's time to take a measurement.
        for (int i = 0; i <= num - 1; i++)
        {
            if ((MEAS + i)->ENABLED &&
                    (current - (MEAS + i)->start) % (MEAS + i)->interval == 0)
            {
                //Send an SDI-12 command.
                //Parse measurements.
                measurements = "0+3.14+2.718+1.414";
                //Write date and time.
                file = fopen(filename, "a");
                fprintf(file, "%d-", info->tm_year + 1900);
                if (info->tm_mon < 9)
                {
                    fprintf(file, "0");
                }
                fprintf(file, "%d-", info->tm_mon + 1);
                if (info->tm_mday < 10)
                {
                    fprintf(file, "0");
                }
                fprintf(file, "%d,", info->tm_mday);
                if (info->tm_hour < 10)
                {
                    fprintf(file, "0");
                }
                fprintf(file, "%d:", info->tm_hour);
                if (info->tm_min < 10)
                {
                    fprintf(file, "0");
                }
                fprintf(file, "%d:", info->tm_min);
                if (info->tm_sec < 10)
                {
                    fprintf(file, "0");
                }
                fprintf(file, "%d,", info->tm_sec);
                //TODO: Save measurements to data file.
                fprintf(file, "\n");
                fclose(file);
            }
        }
    }
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
