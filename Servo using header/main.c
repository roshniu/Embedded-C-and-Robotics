//Controlling servo using servo.h
//motor0-PB1, motor1-PB2, motor2-PB3, motor3-PB3

#include <avr/io.h>
#include <avr/interrupt.h>
#include "delay.h"
#include "servo.h"

int main()
 {
 
 servo_init();
 
  while(1)
   {
    deg(0,0);      //degree motor number
	delayms(2000);
	deg(90,0);
	delayms(2000);
	deg(180,0);
	delayms(2000);
   }
 }