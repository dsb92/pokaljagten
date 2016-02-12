/*
 * Main2.c
 *
 * Created: 15-01-2013 13:03:26
 *  Author: David
 */ 


#include <avr/io.h>
//#include "Lyddriver.h"
//#include "Lys_functions.h"
#include "Refleks.h"
#include "Motor klasse.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#define F_CPU 3686400UL
#define XTAL 3686400

StartSignal();
unsigned int counter = 0;

void initPORT()
{
	DDRD = 0b11110001;	// PD5(lyd), PD4(T1Delay), PD6(Motor), PD7(Motor) - alle udgang.
	PORTD = 0b00000001 | PIND;
	DDRA = 0b00100000;	// PA5(Lys) - udgang, PA2(Refleks) - indgang.
	DDRB = 0b00001000;	// PB3(Lys) - udgang
}

int main(void)
{
	T1Delay();	// Timer1 - Lyd
	initTimer2(); // Timer2 - Motor
	initBackLEDPort();	// Timer0 sat her.
	initFrontLEDPort();
	initPORT();
	sei();
	
	allLightsOn();	// Tænd alle lys
	
	counter = ReflectionCount();

	while( counter >= 0 && counter < 9 )
	{
		DriveForward1();
		brakeLightOff();
		
		if( StartReflection() == 1 )
		{
			DetekCoin();
		}	
		
		if( counter == 3 )
		{
			Brake();
			brakeLightOn();
		}
		
		if( counter == 6 )	// Refleksbrik 6
		{
			Brake();
			brakeLightOn();
			Reverse();
		}
		
		if( counter == 7 )	// Refleksbrik 5
		{
		}
	}
	
	Brake();
	allLightsOff();
	StopLevelComplete();

	return 0;
}

ISR( TIMER1_COMPB_vect )
{
	counter++;	// initialiseres i main til counter = 0;
}
