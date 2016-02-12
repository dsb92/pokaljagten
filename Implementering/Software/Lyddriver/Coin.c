/*
 * Implementerings fil for Coin.c
 * 15/12-2012
 * Created: 03-12-2012 19:02:14
 * Author: David Buhauer
 * 201270749
 */ 																																								
																																											
#include <avr/io.h>	
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#define F_CPU 3686400UL


unsigned char ANTAL_OVERFLOWS = 5;	// Standard overflow - har ingen betydning, men skal initialiseres.

//Toner for coin-lyden			
char Coin[] = "abbb";														
																														
																							
																																																			
//Antal overflows for hver tone
unsigned int toneDelay[] = {36, 360};
								
								
int *melodiDelayPtr;
char *melodiPtr;
int playing = 0;
//int sharp_flag = 0;
unsigned char overflow_cnt = 0;
    
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
void startTone(char tone, int delay)
{
ANTAL_OVERFLOWS = delay;
  switch(tone)
  {
    case 'a':
		OCR1A = 1842; //a = 1000 Hz 
		break;
    case 'b': 
        OCR1A = 1382; //b = 1333 Hz
		break;
    
  }
  stopTone(0);
  if (tone != '-') 
    TCCR1A |= 0b01000000;	// Toggle OCR1A on compare match
  // Enable Timer0 overflow interrupt
  TIMSK |= 0b00000001;  
}

void stopTone(int delay)
{
  TCCR1A &= 0b10111111;
  ANTAL_OVERFLOWS = delay;
}

void startMelodi(char *mPtr, int *mDelayPtr)	// Pointers der peger på arrayene Coin og toneDelay
{
  if (*mPtr)
  {
    while (playing)
    {}
    melodiPtr = mPtr;
    melodiDelayPtr = mDelayPtr;
	startTone(*mPtr, *mDelayPtr);
	melodiPtr++;
	melodiDelayPtr++;	  
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
		   stopTone(*melodiDelayPtr);
		   melodiPtr++;
		   melodiDelayPtr++;
	   }
	   
    
    else if (*melodiPtr == 0)
    {
      stopTone(0);
      // Disable Timer0 overflow interrupt
      TIMSK &= 0b11111110;
      playing = 0;
    }
  
    else
    {
      startTone(*melodiPtr, *melodiDelayPtr);
	  melodiPtr++;
	  melodiDelayPtr++;      
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
    startMelodi(Coin, toneDelay);
  }
  
  return 0;
}
