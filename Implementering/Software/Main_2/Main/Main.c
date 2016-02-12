/*
 * Main.c
 *
 * Created: 14-01-2013 13:01:19
 *  Author: David
 */ 

/*
#include <avr/io.h>
#include "Lyddriver.h"
#include "Lys_functions.h"
#include "Refleks.h"
#include "Motor klasse.h"
#include <stdlib.h>
#define F_CPU 3686400UL
#define XTAL 3686400


void StartSignal();
unsigned char counter = 0;


int main(void)
{
	
	T1Delay();
	initTimer2();
	initBackLEDPort();
	initFrontLEDPort();
	
    while(1)
    {
       StartSignal();
        
	        allLightsOn();
	        Start tæller
			
			DriveForward();
			StopBackwards();
			
	       while ( StartReflection() == false || ReflectionCount() >= 0 )
		   {
			   if( StartReflection() == true)
			   {
				   DetekCoin();
			   }
			   
			   if( ReflectionCount() == 6 )
			   {
				   brakeLightOn();
				   T1Delay();
				   while( counter < 100);
				   brakeLightOff();
				   ReverseBeebBeeb();
			   }
	
	        if( hvis bilen bakker )	// Kald Reverse()
	        {
		        Spil lyd fra en lastbil der bakker	// ReverseBeebBeeb
		        Tænd bremselygter	// Dutycycle 95 % ?
	        }
	        
	        Stop bilen
	        Spil level complete lyden
	        Sluk alle lys.
	        Reset tæller
	        
        }
    }
}

void StartSignal()
{
	// "Normal" clock, no multiprocesser mode (= default)
	UCSRA = 0b00100000;
	// No interrupts enabled
	// Receiver enabled
	// Transmitter enabled
	// No 9 bit operation
	UCSRB = 0b00011000;
	// Asynchronous operation, 1 stop bit, no parity
	// Bit7 always has to be 1
	// Bit 2 and bit 1 controlles the number of databits
	UCSRC = 0b10000000 | (DataBit-5)<<1;
	// Set Baud Rate according to the parameter BaudRate:
	// Select Baud Rate (first store "UBRRH--UBRRL" in local 16-bit variable,
	//                   then write the two 8-bit registers seperately):
	TempUBRR = XTAL/(16*19200) - 1;
	// Write upper part of UBRR
	UBRRH = TempUBRR >> 8;
	// Write lower part of UBRR
	UBRRL = TempUBRR;
	
}

ISR( TIMER1_COMPB_vect )
{
	counter++;	// initialiseres i main til counter = 0;	
}
*/