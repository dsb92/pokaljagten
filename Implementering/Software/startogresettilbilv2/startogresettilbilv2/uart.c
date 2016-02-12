/*
 * uart.c
 *
 * Created: 22-11-2012 13:36:53
 *  Author: WeX
 */ 
#include <avr/io.h>
#include "uart.h"
#include <stdlib.h>


void InitUART(unsigned long BaudRate, unsigned char DataBit)
{
	if( (110<=BaudRate) && (BaudRate<=115200) && (5<=DataBit) && (DataBit<=8) )
	{
		UBRRH = (3686400/(16*BaudRate)-1) >>8;
		UBRRL = 3686400/(16*BaudRate)-1;
		
		UCSRB = 0b00011000;
		//UCSRC = 0b10000??0//Bit 7 skal være 1, bit 6 0=asynkron mode, bit 4 og 5 = valg af paritet, bit 3 = valg af stop bits 0 = 1 stop bit 1 = 2 stop bits, bit 2 og 1 = antal databits 
		if( DataBit == 5 )
		{
			UCSRC = 0b10000000;
		}
				if( DataBit == 5 )
		{
			UCSRC = 0b10000000;
		}
		if( DataBit == 6 )
		{
			UCSRC = 0b10000010;
		}
		if( DataBit == 7 )
		{
			UCSRC = 0b10000100;
		}
		if( DataBit == 8 )
		{
			UCSRC = 0b10000110;
		}
	}	
}


unsigned char CharReady( tegn )
{
	return ( (tegn != 0) ? 1 : 0 );
}


char ReadChar()
{
	while( (UCSRA & 0b10000000) == 0 )
	{
	}
	
	// x = UDR læser
	// UDR = x skriver
	return ( UDR );
}


void SendChar(char Tegn)
{
	while( ( UCSRA & 0b00100000 ) == 0 )
	{
	}
	
	UDR = Tegn;	
}


void SendString(char* Streng)
{
	// Repeat untill zero-termination
	while (*Streng != 0)
	{
		// Send the character pointed to by "Streng"
		SendChar(*Streng);
		// Advance the pointer one step
		Streng++;
	}
}

void SendInteger(int Tal)
{
	char array[7];
	// Convert the integer til an ASCII string (array), radix = 10
	itoa(Tal, array, 10);
	// - then send the string
	SendString(array);
}