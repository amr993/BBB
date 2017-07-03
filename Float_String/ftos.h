/*
 * ftos.h
 *
 *  Created on: Jun 30, 2017
 *      Author: amr
 */

#ifndef FTOS_H_
#define FTOS_H_
#include<stdio.h>
#include<math.h>

void reverse(char *str, int len);
int intToStr1(int x, char str[], int d);
int intToStr2(int x, char str[], int d);
void ftoa(float n, char *res, int afterpoint);

#endif /* FTOS_H_ */
