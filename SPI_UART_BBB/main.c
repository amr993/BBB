/*
 * main.c
 *
 *  Created on: Jun 30, 2017
 *      Author: amr
 */
#include"spi_uart.h"


int main(){
	int i=0 ;
    //int j=0 ;                 /*Application team*/
	//int size = 10;			/*Test*/
	float raw_data[14];
	//char filtered_data[10];   /*Test*/
	float filtered_data[10]={3.5,60.5,70.5};    /*Application team or Processing*/
	float processing[3]; 		/*Processing*/
	unsigned char processing_SOF[]={"Orientation:,"};
	unsigned char processing_MOF[]={","};
	unsigned char processing_EOF[]={"\n"};
	char res[20];
	FILE *fp;
		//while(1)
		//{
	/*SPI receive raw data*/
	SPI_Receive((float*) &raw_data);

	for (i=0;i<14;i++){
	printf("Raw Data:%f\n", raw_data[i]);
	}

	fp = fopen( "raw_data.txt" , "w" );
	   fwrite(raw_data , 1 , sizeof(raw_data) , fp );
	   fclose(fp);

	/*UKF Filter*/
	usleep(1000);


	/*UART send filtered data*/

	//UART_Send_Bytes((char*) &filtered_data,size); //test


	/*Application team*/
	/*
	for(j=0 ; j<10 ;j++)
	{
	UART_Send_Float ((float*) &filtered_data[j]);
	}
    */

	/*Processing*/
		for(i=0; i<3; i++)
		{
			processing[i]=filtered_data[i];
		}


		UART_Send_Bytes((char*) &processing_SOF,14);

	    ftoa(processing[0],res, 5);

	    UART_Send_Bytes((char*) &res,7);

	    UART_Send_Bytes((char*) &processing_MOF,1);

	    ftoa(processing[1],res, 5);

	    UART_Send_Bytes((char*) &res,7);

	    UART_Send_Bytes((char*) &processing_MOF,1);

	    ftoa(processing[2],res, 5);

	    UART_Send_Bytes((char*) &res,7);

	    UART_Send_Bytes((char*) &processing_EOF,1);

		//}
	return 0;
}

