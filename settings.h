#define num 3 //Number of possible measurements.

struct measurement
{
    int ENABLED;
    char *NAME;
    char *COMMAND;
    int POSITION;
    char *START;
    char *INTERVAL;
};

struct measurement *MEAS;

void reset();
void load();
void view();
void set(char *label, char *setting, char *value);
