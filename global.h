//This file includes variables that need to be accessed by all project files.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define num 10 //Number of possible measurements.

struct measurement
{
    int ENABLED;
    char *NAME;
    char *COMMAND;
    int MEASUREMENT;
    char *INTERVAL;
    time_t interval;
    char *START;
    time_t start;
};

//Array to store measurement settings.
struct measurement *MEAS;
//Name of serial port.
char *port_name;
//Variables to store current time.
time_t current;
struct tm *info;
