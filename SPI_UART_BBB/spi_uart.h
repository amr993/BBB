/*
 * spi_uart.h
 *
 *  Created on: Jun 30, 2017
 *      Author: amr
 */

#ifndef SPI_UART_H_
#define SPI_UART_H_
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<math.h>
#include<termios.h> // using the termios.h library
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<stdint.h>
#include<linux/spi/spidev.h>


/*preprocessors*/
#define SPI_PATH "/dev/spidev1.0"
#define UART_PATH "/dev/ttyO4"
/*SPI Functions Prototypes*/
int transfer(int fd, unsigned char send[], unsigned char receive[], int length);
int SPI_Receive(float raw_data[]);

/*UART Functions Prototypes*/
int UART_Send_Bytes(char in[],int size);
int UART_Send_Float (float in[]);
void reverse(char *str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char *res, int afterpoint);

#endif /* SPI_UART_H_ */
