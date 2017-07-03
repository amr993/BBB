/*
 * UART.c
 *
 *  Created on: Jul 3, 2017
 *      Author: amr
 */
/*************************************UART****************************************/
#include"UART.h"

/*UART Functions*/

int UART_Send_Bytes(char in[],int size){
			int file;
			int count;

	if ((file = open(UART_PATH, O_RDWR | O_NOCTTY | O_NDELAY))<0){
		perror("UART: Failed to open the file.\n");
		return -1;
	}

	struct termios options; // the termios structure is vital
	tcgetattr(file, &options); // sets the parameters associated with file

	// Set up the communications options:
	// 9600 baud, 8-bit, enable receiver, no modem control lines
	options.c_cflag = B9600 | CS8 | CREAD | CLOCAL;
	options.c_iflag = IGNPAR | ICRNL; // ignore partity errors, CR -> newline

	tcflush(file, TCIFLUSH); // discard file information not transmitted
	tcsetattr(file, TCSANOW, &options); // changes occur immmediately


	if ((count = write(file, in, size))<0){ // send the string
	    perror("Failed to write to the output\n");
	    return -1;
	    }

close(file);
return 0;
}

int UART_Send_Float (float in[])
{
	int file;
	int count;
	char m;
	if ((file = open(UART_PATH, O_RDWR | O_NOCTTY | O_NDELAY))<0){
			perror("UART: Failed to open the file.\n");
			return -1;
		}

		struct termios options; // the termios structure is vital
		tcgetattr(file, &options); // sets the parameters associated with file

		// Set up the communications options:
		// 9600 baud, 8-bit, enable receiver, no modem control lines
		options.c_cflag = B9600 | CS8 | CREAD | CLOCAL;
		options.c_iflag = IGNPAR | ICRNL; // ignore partity errors, CR -> newline

		tcflush(file, TCIFLUSH); // discard file information not transmitted
		tcsetattr(file, TCSANOW, &options); // changes occur immmediately

		unsigned char *xptr = (unsigned char *)&in;

			for(m=0 ; m<sizeof(float) ; m++)
			{
				if ((count = write(file, (xptr+m),1))<0){ // send the string
						perror("Failed to write to the output\n");
						return -1;
					}
			}
return -1;
		}


