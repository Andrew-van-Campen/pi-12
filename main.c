//This code handles most general datalogger functionality.

#include "global.h"

#include "command.h"
#include "settings.h"
#include "serial.h"
#include "data.h"

//Main program.
void run()
{
    //Check if there is a currently running pi-12 program.
    system("ps -A | grep pi-12 > .pi-12-test");
    FILE *test = fopen(".pi-12-test", "r");
    if (test == NULL)
    {
        printf("ERROR: Could not check for currently running Pi-12 programs.\n");
        return;
    }
    char *test_string = (char *) calloc(100, sizeof(char));
    int pos_test = 0;
    char current_char = fgetc(test);
    while (current_char != EOF)
    {
        *(test_string + pos_test) = current_char;
        pos_test++;
        current_char = fgetc(test);
    }
    fclose(test);
    system("rm .pi-12-test");
    if (pos_test > 30)
    {
        char *pid = (char *) calloc(10, sizeof(char));
        for (int i = 0; *(test_string + i) != ' '; i++)
        {
            *(pid + i) = *(test_string + i);
        }
        int pid_num = atoi(pid);
        printf("\nERROR: There is a Pi-12 program already running (PID %d).\n", pid_num);
        return;
    }
    //Get current time.
    time(&current_time);
    time_info = localtime(&current_time);
    //Create data file if it doesn't already exist, and handle errors.
    if (createFile() == -1)
    {
        return;
    }
    //Initialize variables for keeping track of information.
    time_t previous_time;
    int write;
    char *data_command = (char *) calloc(5, sizeof(char));
    *(data_command + 1) = 'D';
    *(data_command + 2) = '0';
    *(data_command + 3) = '!';
    *(data_command + 4) = '\0';
    char *time_delay_str = (char *) calloc(4, sizeof(char));
    *(time_delay_str + 3) = '\0';
    int time_delay;
    int pos_resp;
    int pos_val;
    int count;
    //Execute loop endlessly.
    while (1)
    {
        //Reset write requests.
        write = 0;
        //Wait until time changes.
        previous_time = current_time;
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
                //Flag for measurement.
                (MEAS + i)->flag = 1;
            }
        }
        //For each sensor that's flagged, take measurements.
        for (int i = 0; i <= num - 1; i++)
        {
            if ((MEAS + i)->flag)
            {
                //Send measurement command.
                sendCommand((MEAS + i)->COMMAND);
                //Parse response.
                for (int j = 0; j <= 2; j++)
                {
                    *(time_delay_str + j) = *(response + j + 1);
                }
                time_delay = atoi(time_delay_str);
                //Wait number of seconds.
                for (int j = 1; j <= time_delay + 1; j++)
                {
                    previous_time = current_time;
                    while (current_time == previous_time)
                    {
                        time(&current_time);
                    }
                }
                //Send request data command.
                *(data_command + 0) = *((MEAS + i)->COMMAND + 0);
                sendCommand(data_command);
                //Check that the correct number of measurements are returned.
                count = 0;
                pos_resp = 0;
                while (*(response + pos_resp) != '\0')
                {
                    if (*(response + pos_resp) == '+' || *(response + pos_resp) == '-')
                    {
                        count++;
                    }
                    pos_resp++;
                }
                //If the correct number of measurements are returned, parse and save.
                if (count >= (MEAS + i)->MEASUREMENT)
                {
                    //Find measurement.
                    pos_resp = 0;
                    for (int j = 1; j <= (MEAS + i)->MEASUREMENT; j++)
                    {
                        while (*(response + pos_resp) != '+' && *(response + pos_resp) != '-')
                        {
                            pos_resp++;
                        }
                        if ((*(response + pos_resp) == '+' || *(response + pos_resp) == '-') &&
                                j < (MEAS + i)->MEASUREMENT)
                        {
                            pos_resp++;
                        }
                    }
                    //Save measurement.
                    pos_val = 0;
                    if (*(response + pos_resp) == '-')
                    {
                        *((MEAS + i)->value + pos_val) = *(response + pos_resp);
                        pos_val++;
                    }
                    pos_resp++;
                    while (*(response + pos_resp) != '+' && *(response + pos_resp) != '-' &&
                            *(response + pos_resp) != '\0')
                    {
                        *((MEAS + i)->value + pos_val) = *(response + pos_resp);
                        pos_resp++;
                        pos_val++;
                    }
                    //Request write to file.
                    write = 1;
                }
                //Reset flag.
                (MEAS + i)->flag = 0;
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
                for (int j = 0; j <= 20; j++)
                {
                    *((MEAS + i)->value + j) = '\0';
                }
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
            printf("%s\n", response);
            break;
        case 11:
            setPrepend(*(argv + 3));
            break;
        case 12:
            setAppend(*(argv + 3));
            break;
        case 13:
            setSkip(*(argv + 3));
            break;
    }
    //Return.
    return 0;
}
