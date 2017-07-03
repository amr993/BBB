/*
 * main.c
 *
 *  Created on: Jun 23, 2017
 *      Author: amr
 */
#include"UART.h"

 	 	char l ;
		int file;
		int count;

int main(){

	//float processing[]={0.5,10.5,15.25};
	while(1)
		{

	if ((file = open("/dev/ttyO4", O_RDWR | O_NOCTTY | O_NDELAY))<0){
		perror("UART: Failed to open the file.\n");
		return -1;
	}

	struct termios options; // the termios structure is vital
	tcgetattr(file, &options); // sets the parameters associated with file

	// Set up the communications options:
	// 9600 baud, 8-bit, enable receiver, no modem control lines
	options.c_cflag = B9600 | CS8 | CREAD | CLOCAL;
	options.c_iflag = IGNPAR | ICRNL; // ignore partity errors, CR -> newline

	tcflush(file, TCIFLUSH); // discard file information not transmitted
	tcsetattr(file, TCSANOW, &options); // changes occur immmediately

	//float processing[]={0.5,10.5,15.25};
	//char loop =0;
	//for (loop =0 ;loop<200 ; loop++)
/*
		processing[0]+=10;
		processing[1]+=10;
		processing[2]+=10;
    unsigned char transmit1[] = {"Orientation:,"};
    unsigned char transmit2[] = {","};
    unsigned char transmit3[] = {"\n"};
    char res[20];

    if ((count = write(file, &transmit1,14))<0){ // send the string

    perror("Failed to write to the output\n");

    return -1;

    }

    ftoa(processing[0],res, 5);


    if ((count = write(file, &res,7))<0){ // send the string

           perror("Failed to write to the output\n");

           return -1;

           }
    if ((count = write(file, &transmit2,1))<0){ // send the string

       perror("Failed to write to the output\n");

       return -1;

       }
    ftoa(processing[1],res, 5);


        if ((count = write(file, &res,7))<0){ // send the string

               perror("Failed to write to the output\n");

               return -1;

               }
    if ((count = write(file, &transmit2,1))<0){ // send the string

          perror("Failed to write to the output\n");

          return -1;

          }
    ftoa(processing[2],res, 5);


        if ((count = write(file, &res,7))<0){ // send the string

               perror("Failed to write to the output\n");

               return -1;

               }
    if ((count = write(file, &transmit3,1))<0){ // send the string

          perror("Failed to write to the output\n");

          return -1;

          }
   // usleep(1000);

    		//"nu,nu,nu\n"}

	*//*
	//test
	char loop ;
	float in[10]={30.5,20,20.5,12.5,6.5,7.5,8.5,7.77,88.8,10.1};
	for (loop = 0 ; loop<10 ; loop++ )
		{
			send_float (in[loop]);
		}
*/
	 //Application team
	char i ;
	char j ;
	//unsigned char transmit[40];
	float in[10]={30.5,20,20.5,12.5,6.5,7.5,8.5,7.77,88.8,10.1};

	for(i=0 ; i<10 ; i++)
	{
		unsigned char *xptr = (unsigned char *)&in[i];
		for(j=0 ; j<sizeof(float) ; j++)
		{
			if ((count = write(file, (xptr+j),1))<0){ // send the string
					perror("Failed to write to the output\n");
					return -1;
				}
		}
		usleep(10000);

	}



//usleep(100000);

close(file);
		}
return 0;

}


