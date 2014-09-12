/***********************************************************************

CODE7.5: Program for Rx of PC controlled bot

Author: rOSHNI uPPALA

***********************************************************************/

#include <avr/io.h >
#include "cc2500b.h"
#include "delay.h"
int main()
{
rf_init();
DDRD=0xF0;
PORTD=0X00;
while(1)
 {
 PORTD=cc_data3;
 delayms(10);
 }
}