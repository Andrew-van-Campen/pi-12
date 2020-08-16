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
    char *value;     //Most recent measured value
};

//Array to store measurement settings
struct measurement *MEAS;
//Data settings
char *site_name;     //20 characters
char *data_path;     //30 characters
//Serial port settings
char *port_name;     //12 characters
int baud_rate;
char *serial_format; //3 characters
//Variables to store current time
time_t current_time;
struct tm *time_info;
//Paths to store program files.
char *settings_filepath;
