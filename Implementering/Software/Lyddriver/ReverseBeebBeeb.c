/*
 * Implementerings fil for ReverseBeebBeeb.c
 * 13/12 - Vers. 1
 * Created: 13-12-2012 15:09:14
 * Author: David Buhauer
 * 201270749
 */ 																																								
																																											
#include <avr/io.h>	
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#define F_CPU 3686400UL
#define ANTAL_OVERFLOWS 450
 
//Toner for ReverseBeebBeeb			
char ReverseBeebBeeb[] = "a-";	

//Bemærk: Der bruges ikke et 2. array, da der kun er en tone, dvs. laver antal overflows some define.
							
char *melodiPtr;
int playing = 0;
unsigned int overflow_cnt = 0;
    
void initTimer0()
{
  // Timer0: Normal mode, Clock = 3,6864 MHz/1024 = 3600 Hz
  // => Overflow frekvens = 3600 Hz / 8 = 450 Hz
  TCCR0 = 0b00000010;	// Prescaler 8 
}

void initTimer1()	
{
  // CTC mode (mode 4), OC1A:"Normal port operation"
  TCCR1A = 0b00000000;
  // Prescaler = 1 (timer 1 clock = 3,6864 MHz)
  TCCR1B = 0b00001001;
  // Ben OC1A (= PORTD bit 5) sættes til udgang
  DDRD = 0b00100000;
}

// Tone frekvens f = 3,6864 MHz / (2 * (1 + OCR1A)
// OCR1A = 3,6864 MHz/(2*f) - 1
void startTone(char tone)
{
   switch(tone)
   {
	   case 'a':
		OCR1A = 2792; //a = 660 Hz
		break;
   }		
   
   if ( tone != '-')
   {
	TCCR1A |= 0b01000000;	// Toggle OCR1A on compare match
   }		
  // Enable Timer0 overflow interrupt  
  TIMSK |= 0b00000001; 
}

void stopTone()
{
  TCCR1A &= 0b10111111;
}

void startMelodi(char *mPtr)	// Pointers der peger på arrayet ReverseBeebBeeb
{
  if (*mPtr)
  {
    while (playing)
    {}
	startTone(*mPtr);
	melodiPtr = mPtr;
	melodiPtr++;	  
    playing = 1;	   
  }  
}

ISR(TIMER0_OVF_vect)
{
	overflow_cnt++;
	if (overflow_cnt == ANTAL_OVERFLOWS)
	{
		if (*melodiPtr == '-')
		{
			stopTone();
			melodiPtr++;
		}
		else if (*melodiPtr == 0)
		{
			melodiPtr = 'a';
			startTone(*melodiPtr);
			*melodiPtr--;
		}
		else
		{
			startTone(*melodiPtr);
			melodiPtr++;
		}
		overflow_cnt = 0;
	}
}

int main(void)
{
  // Klargør timer 0
  initTimer0();
  // Klargør timer 1
  initTimer1();
  // Enable global interrupt
  sei();  
  while (1)
  {
	startMelodi(ReverseBeebBeeb);
  }
  
  return 0;
}
