/*
 * Implementerings fil for LevelComplete.c
 * Created: 03-12-2012 19:02:14
 * Author: David Buhauer
 * 201270749
 */ 																																								
																																											
#include <avr/io.h>	
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#define F_CPU 3686400UL
#define PAUSE 2700


unsigned char ANTAL_OVERFLOWS = 5;	// Standard overflow - har ingen betydning, men skal initialiseres. 

//Toner for LevelComplete-lyd				
char LevelComplete[] = "abcdef-g-hijklm-n-opqrstt-t-t-t-uuuu";														
																														
																							
																																																			
//Antal overflows for hver tone
unsigned int toneDelay[] = {90, 90, 90, 90, 90, 90, PAUSE, 90, PAUSE, 90, 90, 90, 90, 90, 90, PAUSE, 90, PAUSE, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90};
								
								
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
		OCR1A = 3685; //a = 200 Hz 
		break;
    case 'b': 
        OCR1A -= 100; //b = 210 Hz
		break;
    case 'c': 
		OCR1A -= 200; //c = 770 Hz
		break;        
    case 'd':  
        OCR1A -= 300; //d = 380 Hz
		break;        
    case 'e':
        OCR1A -= 400; //e = 320 Hz
		break; 
	case 'f':
		OCR1A -= 400+200; //f = 440 Hz
		break;
	case 'g':
		OCR1A += 400; //g = 480 Hz
		break;
	case 'h':
		OCR1A = 3685; //h = 450 Hz
		break;
	case 'i':
		OCR1A -= 150; //i = 430 Hz
		break;
	case 'j':
		OCR1A -= 200; //j = 760 Hz
		break;
	case 'k':
		OCR1A -= 300; //k = 860 Hz
		break;
	case 'l':
		OCR1A -= 450; //l = 700 Hz
		break;
	case 'm':
		OCR1A -= 450+225; //m = 520 Hz
		break;
	case 'n':
		OCR1A += 225; //n = 580 Hz
		break;
	case 'o':
		OCR1A = 3685; //o = 500 Hz
		break;
	case 'p':
		OCR1A -= 200; //p = 720 Hz
		break;
	case 'q':
		OCR1A -= 225; //q = 680 Hz
		break;
	case 'r':
		OCR1A -= 325; //r = 620 Hz
		break;
	case 's':
		OCR1A -= 400; //s = 650 Hz
		break;
	case 't':
		OCR1A = 2000; //t = 570 Hz
		break;
	case 'u':
		OCR1A = 1700; //u = 1020 Hz
		break;
	case 'w':
		OCR1A = 3185; //w = 585 Hz
		break;
	case 'x':
		OCR1A = 3350; //x = 550 Hz
		break;
	case 'y':
		OCR1A = 2118; //y = 870 Hz
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

void startMelodi(char *mPtr, int *mDelayPtr)	// Pointers der peger på arrayene startMarioTheme og toneDelay
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
    startMelodi(LevelComplete, toneDelay);
  }
  
  return 0;
}
