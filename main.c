//This code handles most general datalogger functionality.

#include "global.h"

#include "command.h"
#include "settings.h"
#include "serial.h"
#include "data.h"

//Main program.
void run()
{
    //Get current time.
    time(&current_time);
    time_info = localtime(&current_time);
    //Create data file if it doesn't already exist, and handle errors.
    if (createFile() == -1)
    {
        return;
    }
    //Execute loop endlessly.
    time_t previous_time;
    int write;
    while (1)
    {
        previous_time = current_time;
        write = 0;
        //Wait until time changes.
        while (current_time == previous_time)
        {
            time(&current_time);
        }
        time_info = localtime(&current_time);
        //Create data file if it doesn't already exist, and handle errors.
        if (createFile() == -1)
        {
            return;
        }
        //For each sensor that's enabled, check whether it's time to take a measurement.
        for (int i = 0; i <= num - 1; i++)
        {
            if ((MEAS + i)->ENABLED &&
                    (current_time - (MEAS + i)->start) % (MEAS + i)->interval == 0)
            {
                //TODO:
                //Send measurement command.
                //Wait number of milliseconds.
                //Send aD0! command.
                //If too few measurements, send aD1!, etc.
                //Parse measurement.
                (MEAS + i)->value = "12.0512";
                //Request write to file.
                write = 1;
            }
        }
        //Write to file if any measurements were taken.
        if (write)
        {
            //Save measurements to data file.
            writeToFile();
            //Reset measurement values.
            for (int i = 0; i <= num - 1; i++)
            {
                (MEAS + i)->value = "";
            }
        }
    }
}

int main(int argc, char **argv)
{
    //Load settings.
    load();
    //Interpret command from user and call the appropriate function.
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
            reset();
            break;
        case 4:
            setMeas(*(argv + 2), *(argv + 3), *(argv + 4));
            break;
        case 5:
            setSite(*(argv + 3));
            break;
        case 6:
            setPath(*(argv + 3));
            break;
        case 7:
            setPort(*(argv + 3));
            break;
        case 8:
            setBaud(*(argv + 3));
            break;
        case 9:
            setFormat(*(argv + 3));
            break;
        case 10:
            sendCommand(*(argv + 2));
            break;
    }
    //Return.
    return 0;
}
