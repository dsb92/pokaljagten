/*
 * Fjernbetjening.c
 *
 * Created: 13-01-2013 12:43:03
 * Kim Lykke Johansen
 */ 


#include <avr/io.h>
#include "uart.h"
#include "switch.h"

#define XTAL 3686400

int main(void)
{
	InitUART( 9800, 8);		//initierer uart, baudrate 9800, 8 databit
	switchOn( 0 );			//tænder for switch SW0 - Start knap
	switchOn( 7 );			//tænder for switch SW7 - Reset tæller knap
	
    while(1)
    {
		if( switchStatus() == 0b00000001 )
		{
			SendChar( 'S' );		//sender 'S' for start
		}
		 
		if( switchStatus() == 0b10000000 )
		{
			SendChar( 'R' );		//sender 'R' for reset
		}			 			 
    }
}