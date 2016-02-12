/*
 * Refleksstyring.c
 *
 * Created: 16-01-2013 13:37:59
 *  Author: David
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Lyddriver.h"

int antal = -1;

void ReflectionCount( void )
{
	DDRC = 0xFF;
	PORTC = 0xFF;
	
	DDRA &= 0b11110011;	// PA2 og PA3 sættes til indgang
	
	while( PINA & 0b00000100 || PINA & 0b00001000 )
	{
		DetekCoin();
		//Tæl antal én op
		antal++;
		_delay_us(2000000);	
	}
}

void DriveForward1( void )
{
	
	DDRD = 0xFF;
	PORTD = 0b10000000;
	OCR2 = 128; // 50 %
	
	/*
	DDRD |= 0b11000000;
	PORTD |= 0b10000000;
	OCR2 = 128;
	*/
}

void DriveForward2()
{
	/*
	DDRD = 0xFF;
	PORTD = 0b10000000;
	OCR2 = 179; // 30 %
	*/
	
	DDRD |= 0b11000000;
	PORTD |= 0b10000000; 
	
	OCR2 = 179;
}

void Brake( void )			
{
	
	DDRD = 0xFF;
	OCR2 = 255; // ((255-255)/255)*100 = 
	
	
	/*
	DDRD |= 0b11000000;
	OCR2 = 255;
	*/
}	

void Reverse( void )
{	
	
	DDRD = 0xFF;
	PORTD = 0xFF;

	OCR2 = 30; //((255-178)/255)*100 = 30,196
	
	/*
	DDRD |= 0b11000000;
	PORTD |= 0b11000000;
	
	OCR2 = 179;
	*/
}

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
	// Ben OC1A (= PORTD bit 5) sættes til udgang
	
	DDRD |= 0b00110000;
}

void initTimer2( void )
{
	// PWM Phase correct.
	// Set OC2 on compare match when up-counting. Clear OC2 downcounting.
	// Prescaling 256.
	TCCR2 = 0b01110100;
}


int main(void)
{
	initTimer0();
	initTimer1();
	initTimer2();
	initSwitchPort();
	sei();
	
	//int antalRefleksbrik;
	
    while(1)
    {
			do
			{
				ReflectionCount();
				DriveForward1();

				/*if( StartReflection() == 1 )	// True = 1.
				{
					DetekCoin();
				}
				*/

				if( antal == 3 )	// Brems ved bakken.
				{
					Brake();
				}
	        
				if( antal == 6 )	// Bremse og bak.
				{
					Brake();
					_delay_us(5000000);
					Reverse();
				}
	        
				if( antal == 8 )	// Når den holder ved refleksbrik nr 5.
				{
					Brake();
					_delay_us(5000000);
				}
			
			} while ( antal >=0 && antal <=11 );
		
			Brake();		
    }
	
	return 0;
}