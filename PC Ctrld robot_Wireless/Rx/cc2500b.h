/***************************************************************************************************************************************************
HEADER:cc2500b.h (SPI master to interface CC2500 with atmega 8535 )
****************************************************************************************************************************************************

*AUTHOR: rOSHNI uPPALA


*H fuse=0xC8																	
*L fuse=0xFF	
	
DESCRIPTION: 

    This header files gives an interface between cc2500 RF communication 
	module and motherboard for	serial rf bidirectional communicating
	purpose. Include this header file in your C code. Call the rf_init() 
	function before calling any other functions of cc2500.
	
****************************************************************************************************************************************************

MOTHER BOARD CONFIGURATION / PORTS USED

LCD (on PORTC)----------------------------------------------

RS PORTC.0
RW PORTC.1 
E  PORTC.2
D4 PORTC.4
D5 PORTC.5
D6 PORTC.6
D7 PORTC.7

Switches----------------------------------------------------

S1  PortA4
S2  PortA5
S3  PortA6
S4  PortA7

RST Reset

LED (Active high)-------------------------------------------

LED1-PortC4
LED2-PortC5
LED3-PortC6
LED4-PortC7
power-Power on indicator main power
DS-power on indicator driving supply

BUZZER (Active high mode)-----------------------------------
	
PortB4
1-Buzzer enables

MOTOR DRIVERS-----------------------------------------------

0-PortB0
1-PortB1
2-PortB2
3-PortB3
4-PortD4
5-PortD5
6-PortD6
7-PortD7


CC2500……………….(RF trans receiver module)----------------------		
							
PB5-MOSI																
PB6-MISO																
PB7-SCK																	
PB4-SS'																	
PB2-GD0																	
PB3-GD2	

***************************************************************************************************************************************************/

#include<avr/interrupt.h>

#ifndef _CC2500b_H_
#define _CC2500b_H_

#define csn1 (PORTB|=0x10)
#define csn0 (PORTB&=0xEF)
#define miso (PINB & 0x40)
#define gd0 (PINB & 0x04)

//******************************************************************************************//0
void rf_init();				      		//for initialization of rf device                  	//1
void spi_master_init(void);																   	//2
void cc_reset(void);																		//3
void cc_config(void);																		//4
void cc_strobe(char data);																	//5
void Wait(char timeout);																	//6

/****normal mode communication****/
void cc_writereg(char add,char data);														//7
void rf_transmit(unsigned char CCdata);														//8
void cc_readreg(char add);																	//9
void rf_receive();																			//10

/****burst mode communication****/
void cc_writereg_B(char add,char data1,char data2,char data3);								//11
void rf_transmit_B(unsigned char CCdata1, unsigned char CCdata2, unsigned char CCdata3);	//12
void cc_readreg_B(char add);																//13
void rf_receive_B();																		//14

/**************************************************************************************************************************************************/
unsigned char retval,retval1,retval2,retval3,flag,cc_data,cc_data1,cc_data2,cc_data3;

ISR (INT2_vect) //****************************************************************************0
{ 
	if(flag==0)
	{
		//rf_receive();  	//Comment or Uncomment for normal mode communication
		rf_receive_B();   	//Comment or Uncomment for burst mode communication
    }
	else
	{
		flag=0;
	}
}

void rf_init() //*****************************************************************************1
{
	spi_master_init();
	cc_reset();
	cc_config();
	Wait(100);   
	cc_strobe(0x34); 		//receive mode
	//MCUCR=0x02;			//for interrupt 0
	//GICR=0x40;	
 
	MCUCSR=0x00;			//Falling Edge
	GICR=0x20;				//interrupt 2 enabled
 
	sei();	 
	Wait(100);
	Wait(100);
	Wait(100);
	Wait(100);
	retval=retval1=retval2=retval3=flag=cc_data=cc_data1=cc_data2=cc_data3=0;
}

void spi_master_init(void) //*****************************************************************2
{
	DDRB|=0x02;			//spi slave select pin configure as output
	DDRB|=0xB0;			//spi pins (mosi, sck, ss) configure as output important ss must shod be configured  even if it is not in use
	SPCR =0x50;			//spe=1(spi enable),DDRD=1(MSB first),mstr=1(master)
}

void cc_reset(void) //************************************************************************3
{
	csn1; 
    Wait(1); 
    csn0; 
    Wait(1); 
    csn1; 
    Wait(41);
	csn0;
    while (miso);//((PINB&0x08)); 
    SPDR = 0x30; 
    while((SPSR&0x80)==0);			 //SPI_WAIT(); 
	while (miso);//((PINB&0x08)); 
    csn1; 
}

void cc_config(void) //***********************************************************************4
{
	cc_writereg(0X0B,0x07);
	cc_writereg(0x0c,0x00);
	cc_writereg(0x0D,0x5D);
	cc_writereg(0x0E,0x93);
	cc_writereg(0x0F,0xB1);		//93
 
	cc_writereg(0x10,0x2D);
	cc_writereg(0x11,0x3B);
	cc_writereg(0x12,0x73);
	cc_writereg(0x13,0x22);
	cc_writereg(0x14,0xF8);
 
	cc_writereg(0x0A,0x00);
 
	cc_writereg(0x15,0x00);		//
 
	cc_writereg(0x21,0xB6);
	cc_writereg(0x22,0x10);
 
	cc_writereg(0x18,0x18);
	cc_writereg(0x19,0x1D);
 
	cc_writereg(0x1A,0x1C);
	cc_writereg(0x1B,0xC7);
	cc_writereg(0x1C,0x00);
	cc_writereg(0x1D,0xB2);		//f8
 
	cc_writereg(0x23,0xEA);
	cc_writereg(0x24,0x0A);
	cc_writereg(0x25,0x00);
	cc_writereg(0x26,0x11);
	cc_writereg(0x29,0x59);
 
	cc_writereg(0x2C,0x88);
	cc_writereg(0x2D,0x31);
	cc_writereg(0x2E,0x0B);
 
	cc_writereg(0x00,0x06);  	//iocfg2
 
	cc_writereg(0x02,0x06); 	//iocfg0
 
	cc_writereg(0x07,0x04);
	cc_writereg(0x08,0x05);  	//pktctrl 0 
	cc_writereg(0x09,0x00);		//device address
	cc_writereg(0x06,0xFF);
 
	//sync bits
	cc_writereg(0x04,0x12);
	cc_writereg(0x05,0x34);
}

cc_strobe(char data) //***********************************************************************5
{
	csn0;						//pull the ss line to down to activate slave 
	while(miso);
	SPDR=data;					//place data on spi resistor
	while((SPSR&0x80)==0);		//wait foe the spi transmittion complit
	csn1;						//pull the ss line to up to deactivate the slave
	retval = SPDR;
}

Wait(char timeout) //*************************************************************************6
{
// This sequence uses exactly 8 clock cycle for each round
 do {
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
		asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
		asm("nop");
        asm("nop");
	} 
	while (--timeout);
}

/*********************************SINGLE MODE COMMUNICATION***********************************/
/********Check that in ISR rf_recieve(); is uncommented & rf_receive_B(); is commented********/

void cc_writereg(char add,char data)//********************************************************7
{
	csn0;
	while(miso);
	SPDR=add;
	while((SPSR&0x80)==0);		//pull the ss line to down to activate slave 
	SPDR=data;					//place data on spi resistor
	while((SPSR&0x80)==0);		//wait foe the spi transmittion complit
	csn1;
	Wait(1);
}

void rf_transmit(unsigned char CCdata)//*******************************************************8
{
	cli();
	flag=1;
	cc_writereg(0x3f,CCdata);
	cc_strobe(0x35);
	while(!gd0);
	//lcd_string("2");
	while(gd0);
	cc_strobe(0x3A);  			//flux rxfifo
	cc_strobe(0x3B); 			//flux txfifo
	Wait(1);
	cc_strobe(0x36); 			//ideale mode 
	cc_strobe(0x34); 			//receiver mode
	Wait(1); 
	sei();
}

void cc_readreg(char add)//*******************************************************************9
{
	csn0;
	while(miso);
	SPDR=(add|0x80);
	Wait(1);	
	while((SPSR&0x80)==0);		//pull the ss line to down to activate slave 
	SPDR=0;						//place data on spi resistor
	while((SPSR&0x80)==0);		//wait foe the spi transmittion complit
	csn1;						//pull the ss line to up to deactivate the slave
	retval = SPDR;
}

void rf_receive() //**************************************************************************10
{
	cc_readreg(0x3F);
	cc_data=retval;
	Wait(5);
	cc_strobe(0x3A);  			//flux rxfifo
	Wait(1);
	cc_strobe(0x36); 			//ideale mode 
	Wait(1);
	cc_strobe(0x34);			//receive mode
	Wait(1);	
}


/*******************************BURST (MULTI) MODE COMMUNICATION********************************/
/********Check that in ISR rf_recieve_B(); is uncommented & rf_receive(); is commented**********/

void cc_writereg_B(char add,char data1,char data2,char data3)//********************************11
{
	csn0;
	while(miso);
	SPDR=add;
	while((SPSR&0x80)==0);		//pull the ss line to down to activate slave 
	SPDR=data1;					//place data on spi resistor
	while((SPSR&0x80)==0);		//pull the ss line to down to activate slave 
	SPDR=data2;					//place data on spi resistor
	while((SPSR&0x80)==0);		//pull the ss line to down to activate slave 
	SPDR=data3;					//place data on spi resistor
	while((SPSR&0x80)==0);		//wait foe the spi transmittion complit
	csn1;
	Wait(1);
}

void rf_transmit_B(unsigned char CCdata1, unsigned char CCdata2, unsigned char CCdata3)//*******12
{
	cli();
	flag=1;
	cc_writereg_B(0x7f,CCdata1,CCdata2,CCdata3);
	cc_strobe(0x35);			//transmitter mode
	while(!gd0);
	while(gd0);
	cc_strobe(0x3A);    		//flux rxfifo
	cc_strobe(0x3B);  			//flux txfifo
	Wait(1);
	cc_strobe(0x36);   			//ideale mode 
	cc_strobe(0x34);    		//receiver mode
	Wait(1); 
	sei();
}

void cc_readreg_B(char add)//********************************************************************13
{
	csn0;
	while(miso);
	SPDR=(add|0x80);
	Wait(1);	
	while((SPSR&0x80)==0);		//pull the ss line to down to activate slave 
  
	SPDR=0;						//place data on spi resistor
	while((SPSR&0x80)==0);		//pull the ss line to down to activate slave 
	retval1 = SPDR;
  
	SPDR=0;						//place data on spi resistor
	while((SPSR&0x80)==0);		//pull the ss line to down to activate slave 
	retval2 = SPDR;
  
	SPDR=0;						//place data on spi resistor
	while((SPSR&0x80)==0);		//wait foe the spi transmittion complit
	retval3 = SPDR;
  
	csn1;						//pull the ss line to up to deactivate the slave
}

void rf_receive_B() //***************************************************************************14
{
	cc_readreg_B(0x7F);
	cc_data1=retval1;
	cc_data2=retval2;
	cc_data3=retval3;
	//LCD_gotoXY(1,4);
	//LCD_writeString_F ("Rx1 Rx2 Rx3 ");
	//LCD_gotoXY(1,5);
	//LCD_showvalue(retval1);
	//LCD_gotoXY(29,5);
	//LCD_showvalue(retval2);
	//LCD_gotoXY(57,5);
	//LCD_showvalue(retval3);
	Wait(5);
	cc_strobe(0x3A);  			//flux rxfifo
	Wait(1);
	cc_strobe(0x36);  			//ideale mode 
	Wait(1);
	cc_strobe(0x34);			//receive mode
	Wait(1);	
}

#endif

/**************************************************************************************************************************************************/