/*
 * GPIO_49.c
 *
 *  Created on: Jul 1, 2017
 *      Author: amr
 */
#include "GPIO.h"

int gpio_export_direction(unsigned int gpio, unsigned int direction)
{
	int fh;
	int length;
	char GPIO_Buffer[MAX_GPIO_dir];
	if ((fh = open(GPIO_PATH "/export", O_WRONLY))< 0){
		perror("Unable to export the GPIO");
		return fh;
	}

	length = snprintf(GPIO_Buffer, sizeof(GPIO_Buffer), "%d", gpio);
	write(fh, GPIO_Buffer , length);
	close(fh);

	length = snprintf(GPIO_Buffer, sizeof(GPIO_Buffer), GPIO_PATH "/gpio%d/direction", gpio);

	if((fh = open(GPIO_Buffer, O_WRONLY))<0)
	{
		perror("GPIO direction not set");
	}

	if(direction==OUT)
	{
		write(fh, "out", 4);
	}else{
		write(fh, "in", 3);
	}
	close(fh);

	return 0;
	}

int gpio_unexport(unsigned int gpio)
{
	int fh;
	int length;
	char GPIO_Buffer[MAX_GPIO_dir];
	if ((fh = open(GPIO_PATH "/unexport", O_WRONLY))< 0){
		perror("Unable to unexport the GPIO");
		return fh;
	}

	length = snprintf(GPIO_Buffer, sizeof(GPIO_Buffer), "%d", gpio);
	write(fh, GPIO_Buffer , length);
	close(fh);

	return 0;
	}


int gpio_value(unsigned int gpio, unsigned int value)
{
	int fh;
	char GPIO_Buffer[MAX_GPIO_dir];

	snprintf(GPIO_Buffer, sizeof(GPIO_Buffer), GPIO_PATH "/gpio%d/value", gpio);

	if((fh = open(GPIO_Buffer, O_WRONLY))<0)
	{
		perror("GPIO value not set");
	}
	if(value==HIGH){
		write(fh, "1", 2);
	}else{
		write(fh, "0", 2);
	}
	close(fh);
	return 0;
	}

