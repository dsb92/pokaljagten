/*
 * 
 *
 * Created: 13-01-2013 15:45:06
 *  Author: Mathias
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include "Refleks.h"

void ReflectionCount( void )
{
	DDRC = 0xFF;
	PORTC = 0xFF;
	
	DDRA &= 0b11110011;	// PA2 og PA3 s�ttes til indgang
	
	while( PINA & 0b00000100 || PINA & 0b00001000 )
	{
		DetekCoin();
		//T�l antal �n op
		antalRefleksbrik++;
		_delay_us(2000000);	
	}
}

