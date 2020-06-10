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

struct measurement *MEAS;
char *port;

//Variables to store time-related information.
time_t previous;
time_t current;
struct tm *info;
