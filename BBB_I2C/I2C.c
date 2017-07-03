/*
 * I2C.c
 *
 *  Created on: Mar 9, 2017
 *      Author: Amr Taha
 */
/** Simple I2C code
 * This code was built on a code from derek Molly's Book but it has been changed for my needs
 * and thanks a lot for this man :D  :D  */

#include "I2C.h"

#define I2C_path                "/dev/i2c-1"
#define BUFFER_SIZE             10
#define slave_address           0x22

 int main(){
	 /*Declaration*/
	 	int file ;
	 	char readBuffer[BUFFER_SIZE];
	 	char writeBuffer[1] = {0x05};
	 	/*Starting code*/
	 	printf("Starting the I2C Communication as a Master\n");
	 	/* Acquiring bus access*/
	 	   if((file=open(I2C_path, O_RDWR)) < 0){
	 	      perror("failed to open the bus\n");
	 	      return 1;
	 	   }
	 	   if(ioctl(file, I2C_SLAVE, slave_address) < 0){
	 	         perror("Failed to connect to the Slave\n");
	 	         return 1;
	 	      }
	 	  if(write(file, writeBuffer, 1)!=1){
	 	  		         perror("Failed to reset the read address\n");
	 	  		         return 1;
	 	  		      }


	 	   if(read(file, readBuffer, BUFFER_SIZE)!=BUFFER_SIZE){
	 	        perror("Failed to read in the buffer\n");
	 	        return 1;
	 	     }
	 	  printf("The Output is is: %x\n", readBuffer);
	 	   close(file);
	 	return (0);
	 	}
