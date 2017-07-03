/*
 * spi.h
 *
 *  Created on: Jun 29, 2017
 *      Author: amr
 */

#ifndef SPI_H_
#define SPI_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<stdint.h>
#include<linux/spi/spidev.h>

/*preprocessors*/
#define SPI_PATH "/dev/spidev1.0"
/*functions prototypes*/
//int transfer(int fd, unsigned char send[], unsigned char receive[], int length);

#endif /* SPI_H_ */
