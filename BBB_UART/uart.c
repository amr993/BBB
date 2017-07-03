/*
 * uart.c
 *
 *  Created on: Jun 30, 2017
 *      Author: amr
 */
#include"UART.h"

int send_float (float in)
{
	char m ;
	int count;
	int file;
			unsigned char *xptr = (unsigned char *)&in;
			for(m=0 ; m<sizeof(float) ; m++)
			{
				if ((count = write(file, (xptr+m),1))<0){ // send the string
						perror("Failed to write to the output\n");
						return -1;
					}
			}
			usleep(10000);
return -1;
		}

void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}


// Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0'; //convert to string
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}


// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
	char neg[]={"-"};
    // Extract integer part
    int ipart = (int)n;
    if(ipart>0){
    // Extract floating part
    float fpart = n - (float)ipart;


    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
    }
    else{
    	float fpart = n - (float)ipart;
    	// convert integer part to string
    	    int i = intToStr(ipart, res, 0);
    	    i = strcat(neg,i);
    	    // check for display option after point
    	    if (afterpoint != 0)
    	    {
    	        res[i] = '.';  // add dot

    	        // Get the value of fraction part upto given no.
    	        // of points after dot. The third parameter is needed
    	        // to handle cases like 233.007
    	        fpart = fpart * pow(10, afterpoint);
    	        intToStr((int)fpart, res + i + 1, afterpoint);

    	    }
    }
}

