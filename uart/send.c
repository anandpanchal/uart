#include "serial.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
/*
 * Test program for RS232 control
 */
int main(int argc, char* argv[])
{
//		struct serial_rs232 rs232conf;
		char buffer[188]="Hi here am receving approximately 64 bytes of data for testing application .... \n", buffer2[21];
		int i, rv, opt;
		struct termios my_termios, new_termios;


		char dev[20]="/dev/ttyUSB2";

		int fd = open(dev, O_RDWR | O_NDELAY | O_NOCTTY);
		printf("fd=%d\n",fd);

		tcgetattr(fd, &my_termios);
		my_termios.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON);
		my_termios.c_oflag &= ~(OCRNL | ONLCR | ONLRET | ONOCR | OFILL | OLCUC | OPOST);
		my_termios.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG | ECHOK | ECHOCTL | ECHOPRT);
		my_termios.c_cflag &= ~(CSIZE | PARENB);
		my_termios.c_cflag &= ~CRTSCTS;
		my_termios.c_cflag |= CS8 | CLOCAL;
		my_termios.c_cflag &= ~CBAUD;
		my_termios.c_cflag |= B115200; // B19200; // 
//		my_termios.c_cflag |= atoi(argv[1]); // B19200; // 
		my_termios.c_cc[VMIN] = 1;
		my_termios.c_cc[VTIME] = 0;
		rv = tcsetattr(fd, TCSANOW, &my_termios);
		tcgetattr(fd, &new_termios);

		opt=strlen(buffer);

//		for (i = 0; i < 30; i++) {
		while(1){
//				printf("Writing [%d]\n" , i);
			 printf("Writing %d \n", opt);
			 write(fd, buffer, opt);
			 sleep(1);
		}
		close(fd);
}
