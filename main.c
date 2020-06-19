//This code handles most general datalogger functionality.

#include "global.h"

#include "command.h"
#include "settings.h"
#include "serial.h"
#include "data.h"

//Return the process ID saved in file.
int getProcess()
{
    FILE *process = fopen(".process", "r");
    //Create file if it doesn't exist.
    if (process == NULL)
    {
        process = fopen(".process", "w");
        fprintf(process, "0");
        fclose(process);
        //Re-open for reading.
        process = fopen(".process", "r");
    }
    //Read process ID from file.
    char *s = (char *) calloc(7, sizeof(char));
    char c = fgetc(process);
    int pos = 0;
    while (c != EOF)
    {
        *(s + pos) = c;
        pos++;
        c = fgetc(process);
    }
    *(s + pos) = '\0';
    fclose(process);
    //Convert to integer and return.
    int pid = atoi(s);
    free(s);
    return pid;
}

//Save the current process ID in file.
void saveProcess()
{
    FILE *process = fopen(".process", "w");
    fprintf(process, "%d", getpid());
    fclose(process);
}

//Stop program running in the background.
void stop()
{
    //Kill background process if currently running.
    int pid = getProcess();
    if (pid == 0)
    {
        printf("ERROR: Program is not currently running.\n");
    }
    else
    {
        char *command = (char *) calloc(12, sizeof(char));
        sprintf(command, "kill %d", pid);
        system(command);
        printf("Program stopped.\n");
    }
    //Clear process ID in file.
    FILE *process = fopen(".process", "w");
    fprintf(process, "0");
    fclose(process);
}

//Print program status.
void status()
{
    if(getProcess() == 0)
    {
        printf("STOPPED\n");
    }
    else
    {
        printf("RUNNING\n");
    }
}

//Main program; call in background.
void runNew()
{
    //Check if program is already running.
    if (getProcess() != 0)
    {
        printf("ERROR: Program is already running.\n");
        return;
    }
    //Save process ID in file.
    saveProcess();
    //Get current time.
    time(&current);
    info = localtime(&current);
    //Create data file if it doesn't already exist, and handle errors.
    if (createFile() == -1)
    {
        return;
    }
    //Execute loop endlessly.
    time_t previous;
    int write;
    while (1)
    {
        previous = current;
        write = 0;
        //Wait until time changes.
        while (current == previous)
        {
            time(&current);
        }
        info = localtime(&current);
        //Create data file if it doesn't already exist, and handle errors.
        if (createFile() == -1)
        {
            return;
        }
        //For each sensor that's enabled, check whether it's time to take a measurement.
        for (int i = 0; i <= num - 1; i++)
        {
            if ((MEAS + i)->ENABLED &&
                    (current - (MEAS + i)->start) % (MEAS + i)->interval == 0)
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

//Clone current process and call main program from there.
void run()
{
    int p = fork();
    if (p == 0)
    {
        runNew();
    }
}

int main(int argc, char **argv)
{
    //Load settings.
    load();
    //Test serial port.
    test();
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
        case 11:
            stop();
            break;
        case 12:
            status();
            break;
    }
    //Return.
    return 0;
}
