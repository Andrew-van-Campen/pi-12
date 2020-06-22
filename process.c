//This code keeps track of the program when it is running.

#include "global.h"
#include "process.h"

//Return the process ID saved in file.
int getProcess()
{
    FILE *process = fopen(process_filepath, "r");
    //Create file if it doesn't exist.
    if (process == NULL)
    {
        process = fopen(process_filepath, "w");
        fprintf(process, "0");
        fclose(process);
        //Re-open for reading.
        process = fopen(process_filepath, "r");
    }
    //Read process ID from file.
    char *s = (char *) calloc(7, sizeof(char));
    char c = fgetc(process);
    int pos = 0;
    while (c != EOF)
    {
        *(s + pos) = c;
        pos++;
        c = fgetc(process);
    }
    *(s + pos) = '\0';
    fclose(process);
    //Convert to integer and return.
    int pid = atoi(s);
    free(s);
    return pid;
}

//Save the current process ID in file.
void saveProcess()
{
    FILE *process = fopen(process_filepath, "w");
    fprintf(process, "%d", getpid());
    fclose(process);
}

//Stop program running in the background.
void stop()
{
    //Kill background process if currently running.
    int pid = getProcess();
    if (pid == 0)
    {
        printf("ERROR: Program is not currently running.\n");
    }
    else
    {
        char *command = (char *) calloc(20, sizeof(char));
        sprintf(command, "kill %d", pid);
        system(command);
        free(command);
    }
    //Clear process ID in file.
    FILE *process = fopen(process_filepath, "w");
    fprintf(process, "0");
    fclose(process);
}

//Display program status.
void status()
{
    if (getProcess() == 0)
    {
        printf("STOPPED\n");
    }
    else
    {
        printf("RUNNING\n");
    }
}
