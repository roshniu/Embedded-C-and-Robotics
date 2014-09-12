/***********************************************************************

CODE3.9: Program for UART Reception on LCD with header


Author:Roshni Uppala

***********************************************************************/

#include<avr/io.h>
#include"uart.h"
#include"lcd.h"
#include"delay.h"

int main(void)
{
 	uart_init();
	lcd_init();
	delayms(100);
	
	while(1)
	{
		lcd_char(uart_read());
	}
}