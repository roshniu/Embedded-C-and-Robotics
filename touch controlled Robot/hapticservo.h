/*	SERVO.h


	this header file will help you to controlle four servo moter at a single time.

	
*/
#ifndef _SERVO_H_
#define _SERVO_H_

int i,j,k;   
unsigned char m0h,m0l,m1h,m1l,m2h,m2l,m3h,m3l,x,y;
unsigned char temp;
void servo_init()
{

TCCR1A=0x03;
TCCR1B=0x1A;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x27;
OCR1AL=0x0F;
OCR1BH=0x1D;
OCR1BL=0x4B;
TIMSK=0x18;  

sei(); 

}

ISR (TIMER1_COMPA_vect) //void timer1_compa_isr(void)
{
PORTB=0X00;
TCNT1H=0x00;
TCNT1L=0x00;
}

ISR (TIMER1_COMPB_vect) // void timer1_compb_isr(void)
{
switch(i)
{
case 0:
 OCR1BH=m0h;     
 OCR1BL=m0l;     
 PORTB=0X01;
 i=1;
 break ;  
 
case 1:
 OCR1BH=m1h;       
 OCR1BL=m1l;      
 PORTB=0X02;
 i=2;
 break ; 
 
case 2:
 OCR1BH=m2h;              
 OCR1BL=m2l;                
 PORTB=0X04;
 i=3;
 break ;
 
case 3:
 OCR1BH=m3h;   
 OCR1BL=m3l;      
 PORTB=0X08;
 i=0;
 break ; 
 } 
}

void deg(float value,int m)
{
        unsigned int va;
        va=5080+value*15;
        if(m==2)              
        {
                m1l=va;
                temp=va>>8;
                m1h=temp;
        }
        if(m==3)            
        {
                m2l=va;
                temp=va>>8;
                m2h=temp;
        }
        if(m==0)       
        {
                m3l=va;
                temp=va>>8;
                m3h=temp;
        }
        if(m==1)     
        {
                m0l=va;
                temp=va>>8;
                m0h=temp;
        }
}


#endif 
