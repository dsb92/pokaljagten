/*
 * Main.c
 * 8/01-2013 - Pseduo code 
 * Created: 03-12-2012 19:02:14
 * Author: David Buhauer
 * 201270749
 * Version 1 - 8/01-2013: Psedo kode til main.c
 */ 

// inkluderer  Motor.h
// ----||----  Bluetooth.h
//-----||----  Reflektion.h
//-----||----- Lyddriver.h
//-----||----- Lysdriver.h

/*
#include <avr/io.h>
#include "Lyd.h"
#include "Motor.h"
#include "Bluetooth.h"
#include "Reflektion.h"
#include "Lyddriver.h"
#include "Lysdriver.h"
#define F_CPU 3686400UL
*/

int main( void )
{
	
	while(1)
	{
		
		if ( hvis der modtages et signal fra bluetooth )	// kald StartSignal() = signal.
		{
			T�nd alle lys
			Start t�ller
	
			do 
			{
				Spil Super-Mario melodien	// Kalder superMario main theme
		
				if ( hvis der er detekteret en refleksbrik )	// StartReflection() == true.
				{
					Spil coin lyden								// DetekCoin()
				}
		
				else if( hvis bilens fart reduceres )	// Speed( char speedValue < x )
				{
					Kald bremsefunktion
					T�nd bremselygte
				}
						
			
			} while ( s� l�nge bilen k�rer);		// kald Forward() = middelsp�nding>0.
	
	
			if( hvis bilen bakker )	// Kald Reverse()
			{
				Spil lyd fra en lastbil der bakker	// ReverseBeebBeeb
				T�nd bremselygter	// Dutycycle 95 % ?
			}
		
			Stop bilen
			Spil level complete lyden
			Sluk alle lys.
			Reset t�ller
			
		}			
	}
	
	return 0;	
}

ISR( TIMER1_COMPB_vect )
{
	counter++;	// initialiseres i main til counter = 0;

}
