/***********************************************************************

CODE10: Program for RC5 Remote controlled robot


Author: Roshni Uppala

IR TX PortB0		used for transmitter 
IR Rx PortB1  		used for receiver

*********************************************************************************/
#include<avr/io.h>
#include "delay.h"
#include "lcd.h"

int main(void)
{
unsigned char i,a[14],temp=0;
 lcd_init();
 lcd_string("  RC 5"); 
 lcd_cmd(0XC0);
 lcd_string("decoder");
 delayms(1000);
 lcd_clear();
 delayms(100);
 DDRB=0X00;
 DDRD=0XFF;
 PORTD=0X00;

 
 while(1)
  {
   if((PINB&0x02)==0x02)
   {
    delayus(100);
    for(i=0;i<14;i++)
	 {
	  if((PINB&0x02)==0x02)
	    {a[i]=1;}
	  else{a[i]=0;}	
	  delayus(1777);
	 }
	  lcd_gotoxy(0,0);			//  to use it as a IR remote controller receiver 
	  lcd_char((a[0])+0x30);	//instread 0f displaying its received data in LCD 
	  lcd_char((a[1])+0x30);	//separate the data and address bit check the 
	  lcd_char((a[2])+0x30);	//address and on the respective matching command 
	  lcd_char((a[3])+0x30);	//or data do the necessary action
	  lcd_char((a[4])+0x30);
	  lcd_char((a[5])+0x30);
	  lcd_char((a[6])+0x30);	  
	  lcd_char((a[7])+0x30);
	  lcd_gotoxy(1,0);
	  lcd_char((a[8])+0x30);
	  lcd_char((a[9])+0x30);
	  lcd_char((a[10])+0x30);
	  lcd_char((a[11])+0x30);
	  lcd_char((a[12])+0x30);
	  lcd_char((a[13])+0x30);
	  
	 temp=0x00;
		for(i=8;i<=13;i++)
		{
			if((a[i]&0x01)==0x01)
			{
				temp=temp|0x01;
			}
				temp<<=1;
				
		}		
		lcd_gotoxy(1,9);
		temp>>=1;					// To avoide the 1 bit extra shift
					
		
		lcd_showvalue(temp);
		
		switch(temp)
		{
			case 30: PORTD=0X50;
						break;
			case 28: PORTD=0XA0;
						break;
			case 18: PORTD=0x40;
						break;
			case 20: PORTD=0X10;
						break;
			case 38: PORTD=0X00;
						break;
		}
		
		

  }
 }}
