/*
 * startogresettilbilv2.c
 *
 * Created: 17-01-2013 08:18:13
 *  Author: WeX
 */ 



#include <avr/io.h>
#include "uart.h"
#include <util/delay.h>

#define XTAL 3686400

	InitUART( 9800, 8);
	DDRA |= 0b00010000;
	
	PORTA |= 0b00010000; //sætter PA4 høj for at tælleren kan køre
	
	while( 'S' != ReadChar() )
	{
		
		if( 'R' == ReadChar() )
		{
			PORTA &= ~( 1 << 4 );	// sætter PA4 lav og dermed trigger reset på tæller = tælleren resat
			_delay_ms( 500 );		// delay sikre at det lave signal registreres af tællerkredsløbet
			PORTA |= 0b00010000;	//sætter PA4 høj for at tælleren kan køre igen
		}
	}

// Her forsætter programmet til bilens kørsel