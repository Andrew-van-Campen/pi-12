//This code handles communication with SDI-12 sensors.

#include "global.h"
#include "sdi12.h"

void test()
{
    int port = open(port_name, O_RDWR);
    if (port < 0)
    {
        printf("ERROR: Could not open port %s.\n", port_name);
    }


    struct termios tty;

    memset(&tty, 0, sizeof(tty));

    if (tcgetattr(port, &tty) != 0)
    {
        printf("ERROR: %d\n", errno);
        return;
    }

    //Control modes
    tty.c_cflag &= ~PARENB;        //Clear parity bit, disabling parity.
    tty.c_cflag &= ~CSTOPB;        //Clear stop field, only one stop bit used in communication.
    tty.c_cflag |= CS8;            //8 bits per byte.
    tty.c_cflag &= ~CRTSCTS;       //Disable RTS/CTS hardware flow control.
    tty.c_cflag |= CREAD | CLOCAL; //Turn on READ and ignore ctrl lines.
    //Local modes
    tty.c_lflag &= ~ICANON; //Disable canonical mode.
    tty.c_lflag &= ~ECHO;   //Disable echo.
    tty.c_lflag &= ~ECHOE;  //Disable erasue.
    tty.c_lflag &= ~ECHONL; //Disable new-line echo.
    tty.c_lflag &= ~ISIG;   //Disable interpretation of INTR, QUIT and SUSP.
    //Input modes
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); //Turn off s/w flow ctrl.
    tty.ciflag &= ~(IGNBRK|



    close(port);
}
