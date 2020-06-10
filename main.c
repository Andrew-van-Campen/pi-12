//This code handles most general datalogger functionality.

#include "global.h"

#include "command.h"
#include "settings.h"
#include "sdi-12.h"
#include "data.h"

//Main program.
void run()
{
    //Create data file if it doesn't already exist.
    createFile();
    //Get current time.
    time(&current);
    info = localtime(&current);
    //Execute loop endlessly.
    time_t previous;
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
                //Save measurements to data file.
                writeToFile();
            }
        }
    }
}

int main(int argc, char **argv)
{
    //Load settings.
    load();
    //Test serial port.
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
