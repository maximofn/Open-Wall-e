//============================================================================
// Name        : UART.cpp
// Author      : Maximo Fernandez Nuñez
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//#include <iostream>
//using namespace std;
//
//int main() {
//	cout << "UART" << endl; // prints UART
//	return 0;
//}


//#include <stdlib.h>
//#include <stdio.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <termios.h>
//#include <string.h> // needed for memset
//
//int main(int argc,char** argv)
//{
//        struct termios tio;
//        struct termios stdio;
//        int tty_fd;
//        fd_set rdset;
//
//        unsigned char c='D';
//
//        printf("Please start with /dev/ttyS1 (for example)\n");
//        memset(&stdio,0,sizeof(stdio));
//        stdio.c_iflag=0;
//        stdio.c_oflag=0;
//        stdio.c_cflag=0;
//        stdio.c_lflag=0;
//        stdio.c_cc[VMIN]=1;
//        stdio.c_cc[VTIME]=0;
//        tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
//        tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
//        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking
//
//
//
//        printf("1\n");
//        memset(&tio,0,sizeof(tio));
//        tio.c_iflag=0;
//        tio.c_oflag=0;
//        tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
//        tio.c_lflag=0;
//        tio.c_cc[VMIN]=1;
//        tio.c_cc[VTIME]=5;
//
//        printf("2\n");
//        tty_fd=open("/dev/ttyUSB0", O_RDWR | O_NONBLOCK);
//        cfsetospeed(&tio,B115200);            // 115200 baud
//        cfsetispeed(&tio,B115200);            // 115200 baud
//
//        printf("3\n");
//        tcsetattr(tty_fd,TCSANOW,&tio);
//        while (c!='q')
//        {
//                if (read(tty_fd,&c,1)>0){
//                	write(STDOUT_FILENO,&c,1);              // if new data is available on the serial port, print it out
//                	printf("4\n");
//                }if (read(STDIN_FILENO,&c,1)>0){
//                	write(tty_fd,&c,1);                     // if new data is available on the console, send it to the serial port
//                	printf("5\n");
//                }
//        }
//        printf("4\n");
//
//        close(tty_fd);
//}


#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART


int main ()
{
	char pLog[150];
	struct termios options;
	int count;
	int rx_length;

	char tx_buffer[20];
	char *p_tx_buffer;
	char *rx_buffer[256];

	//-------------------------
	//----- SETUP USART 0 -----
	//-------------------------
	//At bootup, pins 8 and 10 are already set to UART0_TXD, UART0_RXD (ie the alt0 function) respectively
	int uart0_filestream = -1;

	//OPEN THE UART
	//The flags (defined in fcntl.h):
	//	Access modes (use 1 of these):
	//		O_RDONLY - Open for reading only.
	//		O_RDWR - Open for reading and writing.
	//		O_WRONLY - Open for writing only.
	//
	//	O_NDELAY / O_NONBLOCK (same function) - Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
	//											if there is no input immediately available (instead of blocking). Likewise, write requests can also return
	//											immediately with a failure status if the output can't be written immediately.
	//
	//	O_NOCTTY - When set and path identifies a terminal device, open() shall not cause the terminal device to become the controlling terminal for the process.
	//	uart0_filestream = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode
	uart0_filestream = open("/dev/ttyUSB2", O_RDWR | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode
	if (uart0_filestream == -1)
	{
		//ERROR - CAN'T OPEN SERIAL PORT
		perror("Error - Unable to open UART.  Ensure it is not in use by another application\n");
	}

	//CONFIGURE THE UART
	//The flags (defined in /usr/include/termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html):
	//	Baud rate:- B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
	//	CSIZE:- CS5, CS6, CS7, CS8
	//	CLOCAL - Ignore modem status lines
	//	CREAD - Enable receiver
	//	IGNPAR = Ignore characters with parity errors
	//	ICRNL - Map CR to NL on input (Use for ASCII comms where you want to auto correct end of line characters - don't use for bianry comms!)
	//	PARENB - Parity enable
	//	PARODD - Odd parity (else even)
	tcgetattr(uart0_filestream, &options);
	options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(uart0_filestream, TCIFLUSH);
	tcsetattr(uart0_filestream, TCSANOW, &options);


	//----- TX BYTES -----
	p_tx_buffer = &tx_buffer[0];
	*p_tx_buffer++ = 'H';
	*p_tx_buffer++ = 'e';
	*p_tx_buffer++ = 'l';
	*p_tx_buffer++ = 'l';
	*p_tx_buffer++ = 'o';

	printf("Escribir en puerto serie\n\r");
	if (uart0_filestream != -1)
	{
		count = write(uart0_filestream, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));		//Filestream, bytes to write, number of bytes to write
		if (count < 0)
		{
			perror("UART TX error\n");
		} else
		{
			sprintf(pLog, "Escritos %i bytes\n\r", count);
			printf (pLog);
			printf (tx_buffer);
			printf ("\n\r");
		}
	}


//	int i;
//	for (i=0; i<30000000; i++){
	//----- CHECK FOR ANY RX BYTES -----
	if (uart0_filestream != -1)
	{
		// Read up to 255 characters from the port if they are there
		rx_length = read(uart0_filestream, (void*)rx_buffer, 255);		//Filestream, buffer to store in, number of bytes to read (max)
		if (rx_length < 0)
		{
//			sprintf(pLog, "An error %i occured (will occur if there are no bytes)\n\r", rx_length);
			//perror(pLog);
//			printf(pLog);
//			printf (rx_buffer);
//			printf ("\n\r");
		}
		else if (rx_length == 0)
		{
			//perror("No data waiting\n\r");
			printf("No data waiting\n\r");
		}
		else
		{
			//Bytes received
			rx_buffer[rx_length] = '\0';
			printf("%i bytes read : %s\n", rx_length, rx_buffer);
		}
	}
//	}

	int loop;
	loop = 1;
	do{
		if (uart0_filestream != -1)
		{
			// Read up to 255 characters from the port if they are there
			rx_length = read(uart0_filestream, *rx_buffer, 255);		//Filestream, buffer to store in, number of bytes to read (max)
			if (rx_length < 0)
			{
	//			sprintf(pLog, "An error %i occured (will occur if there are no bytes)\n\r", rx_length);
				//perror(pLog);
	//			printf(pLog);
	//			printf (rx_buffer);
	//			printf ("\n\r");
			}
			else if (rx_length == 0)
			{
				//perror("No data waiting\n\r");
				printf("No data waiting\n\r");
			}
			else
			{
				//Bytes received
				rx_buffer[rx_length] = '\0';
				int i;
//				for (i=0; i<=255; i++){
//					printf("b[%i] : %c\n\r", i, rx_buffer[i]);
//				}
				printf("%i bytes read : %s\n\r", rx_length, &rx_buffer);
				sprintf(pLog, "%i \n\r", rx_buffer);
				printf(pLog);
			}
		}
//		gets (rx_buffer);
//		if (rx_buffer[0] == 'c' || rx_buffer[0] == 'C')
//		{
////			eleccion = -1;
//			loop = 0;
//		}else{
////			eleccion = atoi(inLog);
//		}


	} while (loop);


	//----- CLOSE THE UART -----
	close(uart0_filestream);

	return 0;
}

