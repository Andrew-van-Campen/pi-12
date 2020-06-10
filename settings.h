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

void reset();
void load();
void view();
void set(char *label, char *setting, char *value);
