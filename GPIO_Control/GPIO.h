/*
 * GPIO_49.h
 *
 *  Created on: Jul 1, 2017
 *      Author: amr
 */

#ifndef GPIO_H_
#define GPIO_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>


#define GPIO_PATH "/sys/class/gpio"
#define MAX_GPIO_dir 64

enum direction{ IN=0, OUT=1};
enum value{LOW=0, HIGH=1};


int gpio_export_direction(unsigned int gpio, unsigned int direction);
int gpio_unexport(unsigned int gpio);
int gpio_value(unsigned int gpio, unsigned int value);
#endif /* GPIO_H_ */
