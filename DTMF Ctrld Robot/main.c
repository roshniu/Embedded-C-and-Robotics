/***********************************************************************

CODE6.1: Program for Controlling Bot by DTMF module


Author:Roshni Uppala

***********************************************************************/

#include<avr/io.h>

int main(void)
{
  DDRA=0X00;					// Initialization of PORTA as input
  PORTA=0XFF;
  
  DDRD=0XF0;					// Initailization of PORTD as output
  PORTD=0X00;
  
  while(1)
  {
	switch(PINA&0x0F)			// Checking the status of PA0- PA3 
	{
	 case 0x02:					// For Key 2
	 PORTD=0X50;				// Move forward
	 break;
	 
	 case 0x04:					// For key 4
	 PORTD=0X10;				// Turn left
	 break;
	 
	 case 0x06:					// For key 6
	 PORTD=0X40;				// Turn Right
	 break;
	 
	 case 0x05:					// For key 5
	 PORTD=0X00;				// Stop
	 break;
	 
	 case 0x08:					// For key 8
	 PORTD=0XA0;				// Turn Right
	 break;
	}
  }
 }