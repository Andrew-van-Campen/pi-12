//This code handles communication over serial port.

#include "global.h"
#include "serial.h"

//Variables to be accessed by all functions in this file.
int port;
struct termios *tty;

//Open and set up serial port.
int openPort()
{
    //Open port, and handle any errors.
    port = open(port_name, O_RDWR);
    if (port == -1)
    {
        printf("ERROR: Could not open port %s. %s.\n", port_name, strerror(errno));
        return -1;
    }
    //Check that the device is a tty.
    if (!isatty(port))
    {
        printf("ERROR: Incompatible device.\n");
        close(port);
        return -1;
    }
    //Allocate memory for termios structure.
    tty = (struct termios *) malloc(sizeof(struct termios));
    //Get current serial configuration.
    if (tcgetattr(port, tty) == -1)
    {
        printf("ERROR: %s.\n", strerror(errno));
        close(port);
        return -1;
    }
    //Clear current configuration.
    tty->c_iflag = 0;
    tty->c_oflag = 0;
    tty->c_cflag = 0;
    tty->c_lflag = 0;
    //Get serial format settings.
    int data_bits = *serial_format - 48;
    char parity = *(serial_format + 1);
    int stop_bits = *(serial_format + 2) - 48;
    //Set baud rate.
    switch (baud_rate)
    {
        case 0:
            cfsetispeed(tty, B0);
            cfsetospeed(tty, B0);
            break;
        case 50:
            cfsetispeed(tty, B50);
            cfsetospeed(tty, B50);
            break;
        case 75:
            cfsetispeed(tty, B75);
            cfsetospeed(tty, B75);
            break;
        case 110:
            cfsetispeed(tty, B110);
            cfsetospeed(tty, B110);
            break;
        case 134:
            cfsetispeed(tty, B134);
            cfsetospeed(tty, B134);
            break;
        case 150:
            cfsetispeed(tty, B150);
            cfsetospeed(tty, B150);
            break;
        case 200:
            cfsetispeed(tty, B200);
            cfsetospeed(tty, B200);
            break;
        case 300:
            cfsetispeed(tty, B300);
            cfsetospeed(tty, B300);
            break;
        case 600:
            cfsetispeed(tty, B600);
            cfsetospeed(tty, B600);
            break;
        case 1200:
            cfsetispeed(tty, B1200);
            cfsetospeed(tty, B1200);
            break;
        case 1800:
            cfsetispeed(tty, B1800);
            cfsetospeed(tty, B1800);
            break;
        case 2400:
            cfsetispeed(tty, B2400);
            cfsetospeed(tty, B2400);
            break;
        case 9600:
            cfsetispeed(tty, B9600);
            cfsetospeed(tty, B9600);
            break;
        case 19200:
            cfsetispeed(tty, B19200);
            cfsetospeed(tty, B19200);
            break;
        case 38400:
            cfsetispeed(tty, B38400);
            cfsetospeed(tty, B38400);
            break;
        case 57600:
            cfsetispeed(tty, B57600);
            cfsetospeed(tty, B57600);
            break;
        case 115200:
            cfsetispeed(tty, B115200);
            cfsetospeed(tty, B115200);
            break;
        case 230400:
            cfsetispeed(tty, B230400);
            cfsetospeed(tty, B230400);
            break;
    }
    //Set number of data bits.
    switch (data_bits)
    {
        case 5:
            tty->c_cflag |= CS5; //5 data bits
            break;
        case 6:
            tty->c_cflag |= CS6; //6 data bits
            break;
        case 7:
            tty->c_cflag |= CS7; //7 data bits
            break;
        case 8:
            tty->c_cflag |= CS8; //8 data bits
            break;
    }
    //Set parity bit.
    switch (parity)
    {
        case 'N':
            //Do nothing.
            break;
        case 'E':
            tty->c_cflag |= PARENB;  //Enable parity.
            break;
        case 'O':
            tty->c_cflag |= (PARENB | PARODD); //Enable parity and odd parity.
            break;
    }
    //Set number of stop bits.
    switch (stop_bits)
    {
        case 1:
            //Do nothing.
            break;
        case 2:
            tty->c_cflag |= CSTOPB; //Set 2 stop bits.
            break;
    }
    //Set other control modes.
    tty->c_cflag |= (CREAD | CLOCAL);
    //Set special characters:
    tty->c_cc[VMIN] = 0;   //No minimum number of characters to wait for.
    tty->c_cc[VTIME] = 10;  //1s (10 ds) timer.
    //Save modified settings, and handle any errors.
    if (tcsetattr(port, TCSAFLUSH, tty) == -1)
    {
        printf("ERROR: %s.\n", strerror(errno));
        close(port);
        return -1;
    }
    //Return 0 if successful.
    return 0;
}

//Send an SDI-12 command and return the response.
char *getResponse(char *command)
{
    //Create string to store response.
    char *response = (char *) calloc(256, sizeof(char));
    //Attept to open serial port, and return if there are any errors.
    if (openPort() == -1)
    {
        *response = '\0';
        return response;
    }
    //Copy command into a new string, with prepended and appended characters.
    int length = strlen(prepend) + strlen(command) + strlen(append);
    char *string = (char *) calloc(length + 1, sizeof(char));
    int pos = 0;
    for (int i = 0; *(prepend + i) != '\0'; i++)
    {
        *(string + pos) = *(prepend + i);
        pos++;
    }
    for (int i = 0; *(command + i) != '\0'; i++)
    {
        *(string + pos) = *(command + i);
        pos++;
    }
    for (int i = 0; *(append + i) != '\0'; i++)
    {
        *(string + pos) = *(append + i);
        pos++;
    }
    *(string + pos) = '\0';
    //Write command to serial port.
    for (int i = 0; *(string + i) != '\0'; i++)
    {
        write(port, (string + i), 1);
    }
    //Skip input characters as set by user.
    char c;
    for (int i = 1; i <= skip; i++)
    {
        read(port, &c, 1);
    }
    //Save response in string.
    pos = 0;
    while (read(port, &c, 1) && c != 13 && pos <= 200)
    {
        *(response + pos) = c;
        pos++;
    }
    *(response + pos) = '\0';
    //Free command string.
    free(string);
    //Close serial port.
    close(port);
    //Return the string.
    return response;
}

//Print the response to an SDI-12 command.
void printResponse(char *command)
{
    char *response = getResponse(command);
    if (strlen(response) < 1)
    {
        printf("No response.\n");
    }
    else
    {
        printf("%s\n", response);
    }
}
