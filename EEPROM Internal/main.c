/***********************************************************************

CODE6.2: Program for Internal EEPROM R/W

Author: Roshni Uppala
***********************************************************************/

#include<avr/io.h>
#include "delay.h"
#include "lcd.h"

char read_eeprom(unsigned int eadd)
{
 while((EECR & 0x02)==0x02);
 EEAR=eadd;
 EECR|=0x01;
 return EEDR;
}

void write_eeprom(unsigned int eadd,unsigned char edata)
{
 while((EECR & 0x02)==0x02);
 EEAR=eadd;
 EEDR=edata;
 EECR|=0x04;
 EECR|=0x02; 
delayms(10);
}


int main(void)
{

unsigned char a,b,c;
lcd_init();
write_eeprom(0,1);
write_eeprom(1,2);
write_eeprom(2,3);
write_eeprom(7,1);
write_eeprom(10,2);
write_eeprom(8,3);

PORTA=0x10;
 b=0;
 while(1)
 {
 
 if((PINA&0x10)==0x10)  
  {
  while((PINA&0x10)==0x10);
   a=read_eeprom(b);
   lcd_gotoxy(0,0);
   lcd_showvalue(b);
   lcd_string("-");
   lcd_showvalue(a);
   b++;
  }}
 
}