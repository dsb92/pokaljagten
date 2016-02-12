/*
 * Andet_software.c
 *
 * Created: 13-01-2013 15:45:06
 *  Author: David
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include "Refleks.h"


int ReflectionCount()
{
	int antal = 0;
	unsigned char counter = 0;
	
	DDRA = 0x00;	// PA2 sættes til indgang
	
	while( antal <= 9)
	{
		if( PINA & 0b00000100 )	// Hvis PA2 bliver høj
		{
			antal++;
			//_delay_ms(500);
			T1Delay();
			while( counter < 100 );
			counter = 0;
		}
		return antal;
	}
}

int StartReflection()
{
	
	DDRA = 0x00;	// PA2 sættes til indgang
	
	while( 1 )
	{
		if( PINA & 0b00000100 )	// Hvis PA2 bliver høj
		{
			return 1;
		}
		return 0;
	}
}

void T1Delay()
{
	DDRD = 0b00010000;
	
	// CTC mode (mode 4), OC1A:"Normal port operation"
	TCCR1A = 0b00000000;
	// Prescaler = 1 (timer 1 clock = 3,6864 MHz)
	TCCR1B = 0b00001001;
	// Ben OC1A (= PORTD bit 5) sættes til udgang
	
	TIMSK = 0b00101000;	// Enabler interrupt
	sei();
	
	OCR1B = 18432;	
}
