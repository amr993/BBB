/*
 * main.c
 *
 *  Created on: Jul 1, 2017
 *      Author: amr
 */
#include "GPIO.h"

int main(){

	gpio_export_direction(49, OUT);
	gpio_value(49, HIGH);
	usleep(1000);
	gpio_value(49, LOW);
return 0;
}

