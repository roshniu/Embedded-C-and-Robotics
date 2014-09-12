/*	UART.h


	this header file provides time delay in the form of mili second and micro second
	without affecting any interrupts.

	delayms()  this function provides delay in the form of mili second
	delayus()  this function provides delay in the form of micro second
	
*/
#ifndef _UART_H_
#define _UART_H_

void uartinit()
{
	UCSRA=0x00;
	UCSRB=0x18;
	UCSRC=0x86;
	UBRRH=0x00;
	UBRRL=0x67;
	delayms(100);
}

void printchar(unsigned char uchar)
{
  UDR=uchar;
  while((UCSRA&0x40)==0x00);
  delayuart(1000);
}
 
void printstring(const unsigned char *ustring)
{
   while ( *ustring )
    {
	 UDR=*ustring++;
     while((UCSRA&0x40)==0x00);
    delayuart(1000);
	
}	}

 
void printnum(unsigned char num)
{
    unsigned char H=0,T=0,O=0;
	H=num/100;
	T=(num - (H*100))/10;
	O=(num - (H*100) - (T*10));
	
	printchar(H+48);
	
	printchar(T+48);
	
	printchar(O+48);
	
}
 
 
unsigned char dispdata()
{
  while((UCSRA&0x80)==0x00);
  return UDR;
}
 
void delayuart(unsigned int delaytime)
{
unsigned int dc;
	 for(dc=0;dc<=delaytime;dc++)
	 {
		 
		  asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
		  asm("nop");asm("nop");asm("nop");asm("nop");
	 }
}


#endif 
