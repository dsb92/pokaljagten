#include "Motor klasse.h"
#include "Refleks.h"
#include <avr/io.h>

// DDRD = 0b11000000;

void initTimer2()
{
	TCCR2 = 0b01110100;
}

void DriveForward1()
{
		//PORTD = 0b01000000 | PIND;
		OCR2 = (((255-250)/255)*100); //30.196 % Duty  178
		
}

void Brake()			
{
//	int counter = 0;
	OCR2 = ((255-255)/255)*100; //0 % Duty Cycle
//	T1Delay();
//	while( counter < 400 ); //2 sek
//	counter = 0;
}	

void Reverse()
{	
	unsigned char mask = 0b01000000;
	PORTD = PIND ^ mask;	//XOR
	
	OCR2 = ((255-178)/255)*100; //30.196 % Duty Cycle
	
}

