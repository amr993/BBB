/*
 * spi_uart.c
 *
 *  Created on: Jun 30, 2017
 *      Author: amr
 */
#include"spi_uart.h"

/*************************************SPI*********************************************/

int transfer(int fd, unsigned char send[], unsigned char receive[], int length){
   struct spi_ioc_transfer transfer;           //the transfer structure
   transfer.tx_buf = (unsigned long) send;     //the buffer for sending data
   transfer.rx_buf = (unsigned long) receive;  //the buffer for receiving data
   transfer.len = length;                      //the length of buffer
   transfer.speed_hz = 1000000;                //the speed in Hz
   transfer.bits_per_word = 8;                 //bits per word
   transfer.delay_usecs = 0;                   //delay in us

   // send the SPI message (all of the above fields, inc. buffers)
   int status = ioctl(fd, SPI_IOC_MESSAGE(1), &transfer);
   if (status < 0) {
      perror("SPI: SPI_IOC_MESSAGE Failed");
      return -1;
   }

   return status;
}

int SPI_Receive(float out[]){
   int fd;                             //file handle
   int i=0;                            //loop counter
   int k=0;
   int length=1;                       //number of bites sent or received
   unsigned char rx[4];
   unsigned char tx[4] ={ 0x00, 0xFF, 0x00, 0xFF};
   unsigned char x[4];
   uint8_t bits = 8;                   //8 bits per word
   uint8_t mode = 0;                   //SPI mode 0
   uint32_t speed = 4000000;           //Speed is 4 MHz

   // The following calls set up the SPI bus properties
   if ((fd = open(SPI_PATH, O_RDWR))<0){
      perror("SPI Error: Can't open device.");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_WR_MODE, &mode)==-1){
      perror("SPI: Can't set SPI mode.");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_RD_MODE, &mode)==-1){
      perror("SPI: Can't get SPI mode.");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits)==-1){
      perror("SPI: Can't set bits per word.");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits)==-1){
      perror("SPI: Can't get bits per word.");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed)==-1){
      perror("SPI: Can't set max speed HZ");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed)==-1){
      perror("SPI: Can't get max speed HZ.");
      return -1;
   }

   // Check that the properties have been set
   printf("SPI Mode is: %d\n", mode);
   printf("SPI Bits is: %d\n", bits);
   printf("SPI Speed is: %d\n", speed);

printf("New Raw data :D\n");
for (k=0; k<14; k++)
{
 for (i=0; i<4; i++)

{
     // send and receive function
      if (transfer(fd, (unsigned char*) &tx[i], (unsigned char*) &rx[i], length)==-1){
         perror("Failed to send or receive");
         return -1;
      }
      //printf("tx:%x\t",tx[i]);
      //printf("rx:%x\n",rx[i]);

      x[i]=rx[i];

      fflush(stdout);       //need to flush the output, no \n
}
	out[k] = *(float*)&x;

}
   close(fd);               //close the file
   return -1;
}

/*************************************UART****************************************/

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


void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}



// Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0'; //convert to string
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}


// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
	//char neg[]={"-"};
    // Extract integer part
    int ipart = (int)n;
    if(ipart>0){
    // Extract floating part
    float fpart = n - (float)ipart;


    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
    }
    else{}
}
