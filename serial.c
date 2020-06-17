//This code handles communication over serial port.

#include "global.h"
#include "serial.h"

//Variables to be accessed by all functions in this file.
int port;
struct termios tty;

void test()
{

}

//Open and set up serial port.
void openPort()
{
    //Open serial port.
    port = open(port_name, O_RDWR);
    //Handle errors.
    if (port < 0)
    {
        printf("ERROR: Could not open port %s\n", port_name);
        return;
    }
    //Create termios structure.
    memset(&tty, 0, sizeof(tty));
    //Read in existing settings, and handle errors.
    if (tcgetattr(port, &tty) != 0)
    {
        printf("ERROR: %s\n", strerror(errno));
        return;
    }
    //Set control modes.
    tty.c_cflag &= ~PARENB;      //Disable parity.
    tty.c_cflag &= ~CSTOPB;      //Only one stop bit used in communication.
    tty.c_cflag |= CS8;          //8 bits per byte.
    tty.c_cflag &= ~CRTSCTS;     //Disable RTS/CTS hardware flow control.
    tty.c_cflag |= CREAD|CLOCAL; //Turn on READ & ignore ctrl lines.
    //Set local modes.
    tty.c_lflag &= ~ICANON; //Disable canonical mode.
    tty.c_lflag &= ~ECHO;   //Disable echo.
    tty.c_lflag &= ~ECHOE;  //Disable erasure.
    tty.c_lflag &= ~ECHONL; //Disable new-line echo.
    tty.c_lflag &= ~ISIG;   //Disable interpretation of INTR, QUIT, and SUSP.
    //Set input modes.
    tty.c_iflag &= ~(IXON|IXOFF|IXANY);                              //Turn off software flow control.
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); //Disable any special handling of received bytes.
    //Set output modes.
    tty.c_oflag &= ~OPOST; //Prevent special interpretation of output bytes (e.g. newline chars).
    tty.c_oflag &= ~ONLCR; //Prevent conversion of newline to carriage return/line feed.
    //Set VMIN and VTIME.
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 0;
    //Set baud rate.
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);
    //Save settings, and handle errors.
    if (tcsetattr(port, TCSANOW, &tty) != 0)
    {
        printf("ERROR: %s.\n", strerror(errno));
        return;
    }
}

//Send a string over the serial port.
void send(char *string)
{
    write(port, string, sizeof(string));
}

//Read a string from the serial port.
char *receive(int bytes)
{
    char *string = (char *) calloc(bytes, sizeof(char));
    int n = read(port, &string, bytes);
    return string;
}

//Close serial port.
void closePort()
{
    close(port);
}
