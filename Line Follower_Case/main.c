/***********************************************************************

CODE5.6: Program for Line Follower using Switch case


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
	switch(PINA&0x03)			// Checking the status of PA0 and PA1 
	{
	 case 0x01:					// Right Sensor sensing the Black line
	 PORTD=0X40;				// Turn right
	 break;
	 
	 case 0x02:					// Left Sensor sensing the Black line
	 PORTD=0X10;				// Turn left
	 break;
	 
	 case 0x00:					// Both sensors are sensing white surface
	 PORTD=0X50;				// Move forward
	 break;
	}
  }
 }