/*
 * UART.h
 *
 *  Created on: Jun 23, 2017
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

int send_float (float in);
void reverse(char *str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char *res, int afterpoint);

#endif /* UART_H_ */
