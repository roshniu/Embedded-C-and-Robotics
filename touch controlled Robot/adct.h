
/***********************************************************************

Headerfile for make ADC convertion

***********************************************************************

*/

#ifndef _ADC_H_
#define _ADC_H_						//This is the header for AVR Microcontroller.
#include<avr/io.h>
#include<technophilia/delay.h>		//header file for genarating time delay
#include<technophilia/lcd.h>		//headerfile for interfacing LCD
#include<avr/interrupt.h>			//header file for using interrupt service routins
unsigned int adcdata,adcdata1;

 void adc_init()
 {
  ADCSRA=0X85;	//					//ADC enable, ADC interrupt enable, set prescaller to 64
  ADMUX=0X60;		
 }
 unsigned char getdata(unsigned char chno)	
  {
    ADMUX=0X60;						//right align the ADC result
    ADMUX|=chno;					//select the ADC channel
    ADCSRA|=0X40;					//start ADC convertion
    while(ADSC==1);					//wait for the convertion complit
	return ADCH;
  }

#endif 