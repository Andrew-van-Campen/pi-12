#include <stdio.h>

FILE *settings_file;

//General commands
void reset();
void load();
void view();
//Measurement settings
void setMeas(char *label, char *setting, char *value);
//Data settings
void setSite(char *string);
void setPath(char *string);
//Serial port settings
void setPort(char *string);
void setBaud(char *string);
void setFormat(char *string);
void setPrepend(char *string);
void setAppend(char *string);
void setSkip(char *string);
