/***********************************************************************
interfacing 4 wire resistive touch screen with avr
CODE5.9: Program to control a robot using Touch screen

***********************************************************************

Author:Roshni Uppala



connection details

YM-PA0
XM-PA1
YP-PA2
XP-PA3


 4  3   2  1    //pin numbar
 X+,Y+, X-,Y-
 3  2   1  0

 1  ad  0  x		reading x axis 
 ad 0   x  1		reading y axis

 1  0  r  0		touch detect  DDRA=0x05;  PORTA=0x08;

***********************************************************************/
#include <avr/io.h>
#include "adc.h"
#include "lcd.h"
#include "delay.h"


unsigned char xcod,ycod,pxcod,pycod,dx,dy;

void xaxis()                      	//for reading X cordinate
 {
  DDRA=0x0A;						
  PORTA=0x08;
  delayus(100);
  xcod=getdata(2);
  delayus(100);
 }
 
void yaxis() 						//for reading Y coordinate
 {
  DDRA=0x05;
  PORTA=0x01;
  delayus(100);
  ycod=getdata(3);
  delayus(100);
 }
 
   
int main(void)
 {
 
  
 adc_init();
 lcd_init();   
 DDRD=0xF0;									//set the direction for motor pins
 
  while(1)
   {
   
    DDRA=0x05;
    PORTA=0x08;
    delayus(100);
    while((PINA & 0x02)==0x02){PORTD=0x00;};//touch detect
	
    xaxis();
	yaxis();
	
	lcd_gotoxy(0,0);
	lcd_showvalue(xcod);
	lcd_gotoxy(1,0);
	lcd_showvalue(ycod);
	
	if((xcod<60)&(ycod>80)&(ycod<150))
	 {PORTD=0x50;}							//forward
	 
	if((xcod>80)&(ycod>80)&(ycod<150)) 
	 {PORTD=0xA0;}							//backword
	 
	if((ycod<60)&(xcod>50)&(xcod<180))
	 {PORTD=0x10;}							//left turn
	 
	if((ycod>180)&(xcod>50)&(xcod<180))
	 {PORTD=0x40;}							//right turn
	 
	if((xcod==0)|(ycod==0))
	 {PORTD=0x00;}							//stop
    
   }
 }