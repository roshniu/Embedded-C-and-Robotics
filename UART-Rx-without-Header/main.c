/***********************************************************************

CODE3.8: Program for UART Reception without header


Author:Roshni Uppala

***********************************************************************/

#include<avr/io.h>
#include"delay.h"
#include"lcd.h"

int main(void)
{
 	UCSRA=0x00;
	UCSRB=0x10;  	//rx enable
	UCSRC=0x06;		//charactoor size 8bit  86
	UBRRH=0x00;
	UBRRL=0x67;		//103
	lcd_init();
	delayms(100);
 
	while(1)
	{
		while((UCSRA&0x80)==0x00);
		lcd_char(UDR);
	}
}