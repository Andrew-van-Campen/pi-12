#include <stdio.h>

FILE *settings_file;

void reset();
void load();
void view();
void set(char *label, char *setting, char *value);
