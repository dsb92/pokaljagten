/*
 * Motorstyring.c
 *
 * Created: 16-01-2013 12:22:04
 *  Author: Martin
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "Motor klasse.h"

void DriveForward1( void )
{
	/*
	DDRD = 0xFF;
	PORTD = 0b10000000;
	OCR2 = 128; // 50 %
	*/
	
	DDRD |= 0b11000000;
	PORTD |= 0b10000000;
	OCR2 = 128;
}

void DriveForward2()
{
	/*
	DDRD = 0xFF;
	PORTD = 0b10000000;
	OCR2 = 179; // 30 %
	*/
	
	DDRD |= 0b11000000;
	PORTD |= 0b10000000;
	
	OCR2 = 179;
}

void Brake( void )			
{
	/*
	DDRD = 0xFF;
	OCR2 = 255; // ((255-255)/255)*100 = 
	*/
	
	DDRD |= 0b11000000;
	OCR2 = 255;
}	

void Reverse( void )
{	
	/*
	DDRD = 0xFF;
	PORTD = 0xFF;

	OCR2 = 30; //((255-178)/255)*100 = 30,196
	*/
	DDRD |= 0b11000000;
	PORTD |= 0b11000000;
	
	OCR2 = 30;
}

int main(void)
{
	initTimer2();
	
    while(1)
    {
       DriveForward1(); 
	   _delay_us(10000000);
	   DriveForward2();
	   _delay_us(10000000);
	   Brake();
	   _delay_us(10000000);
	   Reverse();
	   _delay_us(10000000);
	   Brake();
	   _delay_us(10000000);
	   
    }
}

void initTimer2( void )
{
	// PWM Phase correct.
	// Set OC2 on compare match when up-counting. Clear OC2 downcounting.
	// Prescaling 64.
	// Inverted mode
	TCCR2 = 0b01110100;
}