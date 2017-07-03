/*=====================================================================================
 * main.c
 *
 *  Created on: Jun 20, 2017
 *      Author: amr
 *      Description:
 ======================================================================================*/
#include"spi.h"

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
      //printf("tx:%x\t",tx[i]);
     // printf("rx:%x\n",rx[i]);
   return status;
}
int main(){
   int fd;                             //file handle
   int i=0;                            //loop counter
   int k=0;
   int length=1;                       //number of bites sent or received
   unsigned char rx[4];
   unsigned char tx[4] ={ 0x00, 0xFF, 0x00, 0xFF};             //sending only a single char
   uint8_t bits = 8;                   //8 bits per word
   uint8_t mode = 0;                   //SPI mode 0
   uint32_t speed = 4000000;           //Speed is 4 MHz
   float out;
   unsigned char x[4];
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

//while(1)
//{
printf("Hello :D\n");
for (k=0; k<14; k++)
{
 for (i=0; i<4; i++)

{
     // send and receive function
      if (transfer(fd, (unsigned char*) &tx[i], (unsigned char*) &rx[i], length)==-1){
         perror("Failed to send or receive");
         return -1;
      }
      //printf("%4d\r", i);   //print i
      printf("tx:%x\t",tx[i]);
      printf("rx:%x\n",rx[i]);
	x[i]=rx[i];

      fflush(stdout);       //need to flush the output, no \n
}
	out = *(float*)&x;
	printf("z:%f\n",out);
//    usleep(10000);       //sleep for 100ms each loop */
  // }
}
   close(fd);               //close the file
   return 0;
}


