//This code handles most general datalogger functionality.

#include "data.h"
#include "global.h"
#include "serial.h"
#include "command.h"
#include "settings.h"

//Create data file for the current month, if it doesn't already exist.
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
                //TODO: Save measurements to data file.
            }
        }
    }
}

int main(int argc, char **argv)
{
    //Load settings.
    load();
    send("Hello");
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
