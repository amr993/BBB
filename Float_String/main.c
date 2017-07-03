/*
 * ftos.c
 *
 *  Created on: Jun 30, 2017
 *      Author: amr
 */
#include"ftos.h"
// integer is 4 bytes
// driver program to test above funtion
int main()
{
	char i = 0;
    char res[20];
    float n[3] ={20.33,30.55,60.78};

for(i=0;i<3;i++)
{
    ftoa(n[i], res, 6);
    printf("\n\"%s\"\n", res);
}
    return 0;
}

