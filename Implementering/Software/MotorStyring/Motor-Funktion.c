#include "Motor klasse.h"
#include "Refleks.h"
#include <avr/io.h>
#include <util/delay.h>

void DriveForward1( void )
{
	
	DDRD = 0xFF;
	PORTD = 0b10000000;
	OCR2 = 128; // 50 %
	
	/*
	DDRD |= 0b11000000;
	PORTD |= 0b10000000;
	OCR2 = 128;
	*/
}


void Brake( void )			
{
	
	DDRD = 0xFF;
	OCR2 = 255; // ((255-255)/255)*100 = 
	
	
	/*
	DDRD |= 0b11000000;
	OCR2 = 255;
	*/
}

void Reverse( void )
{	
	
	DDRD = 0xFF;
	PORTD = 0xFF;

	OCR2 = 179; //((255-178)/255)*100 = 30,196
	
	/*
	DDRD |= 0b11000000;
	PORTD |= 0b11000000;
	
	OCR2 = 179;
	*/
}
