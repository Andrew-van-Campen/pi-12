#include <stdio.h>

FILE *settings_file;

void reset();
void load();
void view();
void setMeas(char *label, char *setting, char *value);
void setData(char *string);
void setPort(char *string);
