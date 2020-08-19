# Pi-12
Read the user manual first.

The code is structured as follows:

main.c
    the main() function, which interprets commands from the user (i.e. arguments)
    run(), which is the main loop the program executes when acting as a data logger

global.h
    variables that need to be accessed by multiple files
    #include statements for libraries used in multiple files

command.c, command.h
    command(), which parses user input

settings.c, settings.h
    functions to handle changing and saving settings for the data logger
    view()
    reset()
    set...()

serial.c, serial.h
    functions to handle communication with SDI-12 to USB adapter over serial port
    sendCommand()

data.c, data.h
    functions to handle writing data to CSV files
    writeToFile()
