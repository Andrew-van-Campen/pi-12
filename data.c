//This code handles writing data to the file.

#include "global.h"
#include "data.h"

//Create data file for the current month, if it doesn't already exist.
int createFile()
{
    //Assign file name based on current month.
    free(filepath);
    filepath = (char *) calloc(70, sizeof(char));
    if (time_info->tm_mon < 9)
    {
        sprintf(filepath, "%s/%s-%d-0%d.csv", data_path, site_name, time_info->tm_year + 1900, time_info->tm_mon + 1);
    }
    else
    {
        sprintf(filepath, "%s/%s-%d-%d.csv", data_path, site_name, time_info->tm_year + 1900, time_info->tm_mon + 1);
    }
    //Attempt to open a file with that name.
    data_file = fopen(filepath, "r");
    //If the file doesn't exist, create one.
    if (data_file == NULL)
    {
        data_file = fopen(filepath, "w");
        if (data_file == NULL)
        {
            printf("ERROR: Could not access %s\n", data_path);
            return -1;
        }
        //Create a column for date & time.
        fprintf(data_file, "Date & Time,");
        //Create a column for each measurement.
        for (int i = 0; i <= num - 1; i++)
        {
            if ((MEAS + i)->ENABLED)
            {
                fprintf(data_file, "%s,", (MEAS + i)->NAME);
            }
        }
        fprintf(data_file, "\n");
    }
    //Close the file.
    fclose(data_file);
    return 0;
}

//Write most recent measurements to file.
void writeToFile()
{
    //Open file.
    data_file = fopen(filepath, "a");
    //Write date and time.
    fprintf(data_file, "%d-", time_info->tm_year + 1900);
    if (time_info->tm_mon < 9)
    {
        fprintf(data_file, "0");
    }
    fprintf(data_file, "%d-", time_info->tm_mon + 1);
    if (time_info->tm_mday < 10)
    {
        fprintf(data_file, "0");
    }
    fprintf(data_file, "%d ", time_info->tm_mday);
    if (time_info->tm_hour < 10)
    {
        fprintf(data_file, "0");
    }
    fprintf(data_file, "%d:", time_info->tm_hour);
    if (time_info->tm_min < 10)
    {
        fprintf(data_file, "0");
    }
    fprintf(data_file, "%d:", time_info->tm_min);
    if (time_info->tm_sec < 10)
    {
        fprintf(data_file, "0");
    }
    fprintf(data_file, "%d,", time_info->tm_sec);
    //Write measurements.
    for (int i = 0; i <= num - 1; i++)
    {
        if ((MEAS + i)->ENABLED)
        {
            fprintf(data_file, "%s,", (MEAS + i)->value);
        }
    }
    fprintf(data_file, "\n");
    //Close the file.
    fclose(data_file);
}
