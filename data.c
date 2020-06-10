//This code handles writing data to the file.

#include "data.h"
#include "global.h"
#include "settings.h"

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
    data_file = fopen(filename, "r");
    if (data_file == NULL)
    {
        data_file = fopen(filename, "w");
        //Create a column in the data file for each measurement.
        fprintf(data_file, "Date,Time,");
        for (int i = 0; i <= num - 1; i++)
        {
            if ((MEAS + i)->ENABLED)
            {
                fprintf(data_file, "%s,", (MEAS + i)->NAME);
            }
        }
        fprintf(data_file, "\n");
    }
    fclose(data_file);
}

void writeToFile()
{
    //Write date and time.
    data_file = fopen(filename, "a");
    fprintf(data_file, "%d-", info->tm_year + 1900);
    if (info->tm_mon < 9)
    {
        fprintf(data_file, "0");
    }
    fprintf(data_file, "%d-", info->tm_mon + 1);
    if (info->tm_mday < 10)
    {
        fprintf(data_file, "0");
    }
    fprintf(data_file, "%d,", info->tm_mday);
    if (info->tm_hour < 10)
    {
        fprintf(data_file, "0");
    }
    fprintf(data_file, "%d:", info->tm_hour);
    if (info->tm_min < 10)
    {
        fprintf(data_file, "0");
    }
    fprintf(data_file, "%d:", info->tm_min);
    if (info->tm_sec < 10)
    {
        fprintf(data_file, "0");
    }
    fprintf(data_file, "%d,", info->tm_sec);
    fprintf(data_file, "\n");
    fclose(data_file);
}
