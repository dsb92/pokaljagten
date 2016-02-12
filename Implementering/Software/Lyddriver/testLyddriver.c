/*
 * testLyddriver.c
 *
 * Created: 08-01-2013 20:09:01
 *  Author: David
 */ 


/*
 * test_lyddriver.c
 *
 * Created: 15-12-2012 18:08:47
 *  Author: David
 * OBS: Testet med switches fra de gamle LAB øvelser. 
 */ 


#include <avr/io.h>
#include "avr/interrupt.h"
#include "Lyddriver.h"
#include "switch.h"
#include <util/delay.h>

int main( void )
{
	initSwitchPort();
	
	// Klargør timer 0
	initTimer0();
	// Klargør timer 1
	initTimer1();
	// Enable global interrupt
	sei();
	
	while(1)
	{	
		
		if( switchOn(0) )
		{
			StopLevelComplete();
		}
		else if( switchOn(1) )
		{
			DetekCoin();
		}
		
		else if( switchOn(2) )
		{
			StartMario();
		}
		
		else if( switchOn(3) )
		{
			ReverseBeebBeeb();
		}				
	}		
	
	// Interrupt lyden coin afbryder den nuværende melodi, dvs. main theme og spiller coin til den er slut og fortsætter dernæst main theme. 
	// Hvis bilen bakker, spilles reversebeebbeeb og main theme melodien afbrydes. Kaldes DetekCoin funktionen, stopper baklyden og main theme fortsætter.
	
	return 0;
}
