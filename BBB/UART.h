/*
 * UART.h
 *
 *  Created on: Jul 3, 2017
 *      Author: amr
 */

#ifndef UART_H_
#define UART_H_

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<math.h>
#include"string.h"
#include<termios.h> // using the termios.h library

#define UART_PATH "/dev/ttyO4"

/*UART Functions Prototypes*/
int UART_Send_Bytes(char in[],int size);
int UART_Send_Float (float in[]);
#endif /* UART_H_ */
