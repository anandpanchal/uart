#include "serial.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

/*
 * Test program for 232 control
 */
int main(int argc, char* argv[])
{
		char buffer2[81];
		int i, rv, opt;
		struct termios my_termios, new_termios, stdio;
		
//		char dev[20]="/dev/ttyO1";
		char dev[20]="/dev/ttyUSB3";

		int fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);

		if (fd == -1) {
	                printf(" \n Unable to Open %s \n\n ",dev);
	                return -1;
                }

		tcgetattr(fd, &my_termios);
		my_termios.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON);
		my_termios.c_oflag &= ~(OCRNL | ONLCR | ONLRET | ONOCR | OFILL | OLCUC | OPOST);
		my_termios.c_lflag &= ~(ECHO | ECHOE | ECHOKE | ECHONL | ICANON | IEXTEN | ISIG | ECHOK | ECHOCTL | ECHOPRT);
		my_termios.c_cflag &= ~(CSIZE | PARENB);
		my_termios.c_cflag &= ~CRTSCTS;
		my_termios.c_cflag |= CS8 | CLOCAL | CREAD;
		my_termios.c_cflag &= ~CBAUD;
		my_termios.c_cflag |= B115200; // B19200; // 
//		my_termios.c_cflag |= atoi(argv[1]); // B19200; // 
		my_termios.c_cc[VMIN] = 1;
		my_termios.c_cc[VTIME] = 5;
		rv = tcsetattr(fd, TCSANOW, &my_termios);
		tcgetattr(fd, &new_termios);

		fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

		printf("Reading (hit q, return to quit)...\n");
		while(1)
		{
				if(read(fd, buffer2, 1) > 0) {
	                    			 write(STDOUT_FILENO, buffer2, 1);
						 
					}
				
		}
		close(fd);
}
