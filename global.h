//This file includes variables that need to be accessed by all project files.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Maximum number of measurements.
#define num 10

struct measurement
{
    int ENABLED;     //Boolean indicating whether sensor is enabled or not
    char *NAME;      //Name of measurement
    char *COMMAND;   //Measurement command to send
    int MEASUREMENT; //Which measurement to use if multiple measurements are returned
    char *INTERVAL;  //Time interval to take measurements at
    time_t interval; //Same as above, but in seconds
    char *START;     //Start time which interval is measured from
    time_t start;    //Same as above, but in seconds
    char *value;    //Most recent measured value
};

//Array to store measurement settings.
struct measurement *MEAS;
//Path to save data files to.
char *data_path;
//Name of serial port.
char *port_name;
//Variables to store current time.
time_t current;
struct tm *info;
