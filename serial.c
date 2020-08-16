//This code handles communication over serial port.

#include "global.h"
#include "serial.h"

//Variables to be accessed by all functions in this file.
int port;
struct termios tty;

//Open and set up serial port.
int openPort()
{
    //Open port in read/write mode, and handle any errors.
    port = open(port_name, O_RDWR);
    if (port < 0)
    {
        printf("ERROR: Could not open port %s. %s.\n", port_name, strerror(errno));
        return -1;
    }
    //Allocate memory for termios structure.
    memset(&tty, 0, sizeof(tty));
    //Read in existing settings, and handle any errors.
    if (tcgetattr(port, &tty) != 0)
    {
        printf("ERROR: %s.\n", strerror(errno));
        close(port);
        return -1;
    }
    //Set output baud rate.
    switch (baud_rate)
    {
        case 0:
            cfsetospeed(&tty, B0);
            break;
        case 50:
            cfsetospeed(&tty, B50);
            break;
        case 75:
            cfsetospeed(&tty, B75);
            break;
        case 110:
            cfsetospeed(&tty, B110);
            break;
        case 134:
            cfsetospeed(&tty, B134);
            break;
        case 150:
            cfsetospeed(&tty, B150);
            break;
        case 200:
            cfsetospeed(&tty, B200);
            break;
        case 300:
            cfsetospeed(&tty, B300);
            break;
        case 600:
            cfsetospeed(&tty, B600);
            break;
        case 1200:
            cfsetospeed(&tty, B1200);
            break;
        case 1800:
            cfsetospeed(&tty, B1800);
            break;
        case 2400:
            cfsetospeed(&tty, B2400);
            break;
        case 9600:
            cfsetospeed(&tty, B9600);
            break;
        case 19200:
            cfsetospeed(&tty, B19200);
            break;
        case 38400:
            cfsetospeed(&tty, B38400);
            break;
        case 57600:
            cfsetospeed(&tty, B57600);
            break;
        case 115200:
            cfsetospeed(&tty, B115200);
            break;
        case 230400:
            cfsetospeed(&tty, B230400);
            break;
    }
    //Set input baud rate to be equal to output baud rate.
    cfsetispeed(&tty, 0);
    //Get serial format settings.
    int data_bits = *serial_format - 48;
    char parity = *(serial_format + 1);
    int stop_bits = *(serial_format + 2) - 48;
    //Set control modes:
    if (data_bits == 5)
    {
        tty.c_cflag |= CS5; //5 data bits
    }
    else if (data_bits == 6)
    {
        tty.c_cflag |= CS6; //6 data bits
    }
    else if (data_bits == 7)
    {
        tty.c_cflag |= CS7; //7 data bits
    }
    else if (data_bits == 8)
    {
        tty.c_cflag |= CS8; //8 data bits
    }
    if (parity == 'N')
    {
        tty.c_cflag &= ~PARENB; //Disable parity.
    }
    else if (parity == 'E')
    {
        tty.c_cflag |= PARENB;  //Enable parity.
        tty.c_cflag &= ~PARODD; //Disable odd parity (i.e. use even parity).
    }
    else if (parity == 'O')
    {
        tty.c_cflag |= PARENB; //Enable parity.
        tty.c_cflag |= PARODD; //Enable odd parity.
    }
    if (stop_bits == 1)
    {
        tty.c_cflag &= ~CSTOPB; //Disable use of 2 stop bits (i.e. set 1 stop bit).
    }
    else if (stop_bits == 2)
    {
        tty.c_cflag |= CSTOPB; //Set 2 stop bits.
    }
    tty.c_cflag |= CREAD;    //Enable receiver.
    tty.c_cflag |= CLOCAL;   //Ignore modem control lines.
    tty.c_cflag &= ~CRTSCTS; //Disable RTS/CTS (hardware) flow control.
    //Set local modes:
    tty.c_lflag &= ~ISIG;   //Disable interpretation of INTR, QUIT, SUSP, and DSUSP.
    tty.c_lflag &= ~ICANON; //Disable canonical mode.
    //Set input modes:
    //Disable any special handling of received bytes.
    tty.c_iflag &= ~IGNBRK;
    tty.c_iflag &= ~BRKINT;
    tty.c_iflag &= ~PARMRK;
    tty.c_iflag &= ~ISTRIP;
    tty.c_iflag &= ~INLCR;
    tty.c_iflag &= ~IGNCR;
    tty.c_iflag &= ~ICRNL;
    //Disable XON/XOFF flow control.
    tty.c_iflag &= ~IXON;
    tty.c_iflag &= ~IXANY;
    tty.c_iflag &= ~IXOFF;
    //Set output modes:
    tty.c_oflag &= ~OPOST; //Disable special interpretation of output bytes.
    tty.c_oflag &= ~ONLCR; //Disable conversion of NL to CR-NL on output.
    //Set special characters:
    tty.c_cc[VMIN] = 0;   //Minimum number of characters for read().
    tty.c_cc[VTIME] = 10; //Read data for this many deciseconds before timing out.
    //Save modified settings, and handle any errors.
    if (tcsetattr(port, TCSANOW, &tty) != 0)
    {
        printf("ERROR: %s.\n", strerror(errno));
        close(port);
        return -1;
    }
    //Return 0 if successful.
    return 0;
}

//Send an SDI-12 command and print the response.
void sendCommand(char *command)
{
    //Attept to open serial port, and return if there are any errors.
    if (openPort() != 0)
    {
        return;
    }
    //Write command to serial port.
    write(port, command, sizeof(command));
    //Allocate memory for read buffer.
    char response [256];
    memset(&response, '\0', sizeof(response));
    //Read data and store in buffer.
    read(port, &response, sizeof(response));
    //Print response.
    printf("%s", response);
    //Close serial port.
    close(port);
}
