/*
 * Main2.c
 *
 * Created: 15-01-2013 13:03:26
 *  Author: David
 */ 

//*********HEADER-FILER*********
#include <avr/io.h>
#include "Lyddriver.h"
#include "Lys_functions.h"
#include "Motor klasse.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#define F_CPU 3686400UL
#define XTAL 3686400
//******************************


//********PROTOTYPER************
void initTimer0( void );
void initTimer1( void );
void initTimer2( void );
void ReflectionCount( void );
//******************************


//*****GLOBALE VARIABLER********
int antalRefleksbrik = -1;
//******************************


int main(void)
{
	initTimer0();		// Timer0 - Lys/Lyd
	initTimer1();		// Timer1 - Lyd(OCR1A) og Delays
	initTimer2();		// Timer2 - Motorstyring
	initBackLEDPort();	
	initFrontLEDPort();
	
	sei();
	
	allLightsOn();	// T�nd alle lys
	
	

	while(1)
	{
		do 
		{
			ReflectionCount();
			DriveForward1();
			brakeLightOff();
			
			if( antalRefleksbrik == 3 )	// Brems ved bakken.
			{
				Brake();
				brakeLightOn();
			}
			
			if( antalRefleksbrik == 6 )	// Bremse og bak.
			{
				Brake();
				_delay_us(5000000);
				brakeLightOn();
				Reverse();
			}
			
			if( antalRefleksbrik == 8 )	// N�r den holder ved refleksbrik nr 5.
			{
				Brake();
				_delay_us(5000000);
			}
		} while ( antalRefleksbrik >=0 && antalRefleksbrik <=11 );
		
		Brake();
		brakeLightNormal();
		StopLevelComplete();
	}
	
	return 0;
}

//******TIMERS********
void initTimer0( void )
{
	// Timer0: PWM Mode, Clock = 3,6864 MHz/1024 = 3600 Hz
	// => Overflow frekvens = 3600 Hz / 8 = 450 Hz
	// Prescaler 1
	TCCR0 = 0b01100001;
	//Timer0 ikke-fast PWM mode, compare match set when up counting
}


void initTimer1( void )
{
	// CTC mode (mode 4), OC1A:"Normal port operation"
	TCCR1A = 0b00000000;
	// Prescaler = 1 (timer 1 clock = 3,6864 MHz)
	TCCR1B = 0b00001001;
	// Ben OC1A (= PORTD bit 5) s�ttes til udgang
	
	DDRD |= 0b00110000;
}

void initTimer2( void )
{
	// PWM Phase correct.
	// Set OC2 on compare match when up-counting. Clear OC2 downcounting.
	// Prescaling 256.
	TCCR2 = 0b01110100;
}
//**********************


void ReflectionCount( void )
{
	DDRC = 0xFF;	// Fri udgang
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

/*
void T1Delay( void )
{
	// Benfrekvens 100 Hz ?
	OCR1B = 18432;	// Delay p� 0,005*100 = 0,5 sekunder, hvis overflowfrekvensen er 100 - laves i en while-l�kke.
	
	TIMSK |= 0b00001000;	// Enabler interrupt
	// ( TIMSK = 0b00101000; hvis TICIE1 enabled? )
}



//******TIMER1-COMPAREB INTERRUPT******
ISR( TIMER1_COMPB_vect )	// Compare-interrupt for PD4.
{
	
	counter++;
	
}
//************************************
*/