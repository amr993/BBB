/*
 * ftos.h
 *
 *  Created on: Jul 3, 2017
 *      Author: amr
 */

#ifndef FTOS_H_
#define FTOS_H_

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<math.h>
#include"string.h"
#include<termios.h> // using the termios.h library

void reverse(char *str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char *res, int afterpoint);

#endif /* FTOS_H_ */
