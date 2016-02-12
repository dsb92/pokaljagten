/*
 * Implementerings fil for superMarioTheme.c
 * Created: 03-12-2012 19:02:14
 * Author: David Buhauer
 * 201270749
 */ 																																								
																																											
#include <avr/io.h>	
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#define F_CPU 3686400UL
#define L 45	//100 ms
#define M 36	// 80 ms
#define N 23	// 50 ms
#define O 68	// 150 ms
#define P 90	// 200 ms
#define R 27	// 60 ms
#define PAUSE 2700 // 2000 ms

unsigned char ANTAL_OVERFLOWS = 5;	// Standard overflow - har ingen betydning, men skal initialiseres. 

//Toner for superMarioTheme				
char superMarioTheme[] = "a-a-a-b-a-c-d----"	//--- = PAUSE 
						"b-d-e-f-g-h-i-d-a-j-k-l-j-a-m-n-g----"		// PAUSE
						"b-d-e-f-g-h-i-d-a-j-k-l-j-a-m-n-g----"		// PAUSE
						"o-"
						"j-p-q-r-"
						"s-d-i-"
						"o-i-o-t-"
						"o----" // PAUSE
						"j-p-q-r-"
						"s-"
						"u-u-u-"
						"d-o-"																												//a = 660 Hz
						"j-p-q-r-"																											//b = 510 Hz
						"s-d-i-"																										    //c = 770 Hz   											
						"o-i-o-t----" // PAUSE																								//d = 380 Hz    		
						"w-"																												//e = 320 Hz
						"x-"																												//f = 440 Hz
						"o-"																												//g = 480 Hz
						"d-o-o-o-"																											//h = 450 Hz
						"o-"																												//i = 430 Hz
						"j-p-q-r-"																											//j = 760 Hz	
						"s-d-i-"																											//k = 860 Hz		
						"o-i-o-t-"																											//l = 700 Hz	
						"o----" // PAUSE																									//m = 520 Hz
						"j-p-q-r-"																											//n = 580 Hz	
						"s-"																												//o = 500 Hz
						"u-u-u-"																											//p = 720 Hz
						"d-o-"																												//q = 680 Hz
						"j-p-q-r-"																											//r = 620 Hz
						"s-d-i-"																											//s = 650 Hz
						"o-i-o-t-"																											//t = 570 Hz
						"w-"																												//u = 1020 Hz
						"x-"																												//w = 585 Hz
						"o-"																												//x = 550 Hz
						"d-o-o-o-"																											//y = 870 Hz
						"o-o-o-o-n-a-o-i-d-"																								//= 115 toner
						"o-o-o-o-n-a-"																											
						"y-j----"	// PAUSE
						"o-o-o-o-n-a-o-i-d-"																												
						"a-a-a-b-a-c-d-";																												
																														
																							
																																																			
//Antal overflows for hver tone
unsigned int toneDelay[] = {L, 68, L, 135, L, 135, L, 45, L, 135, L, 248, L, 259, PAUSE, 
								L, 203, L, 180, L, 225, L, 135, M, 149, L, 68, L, 135, L, 90, M, 90, N, 68, L, 135, M, 68, N, 158, M, 135, M, 68, M, 68, M, 225, PAUSE,
								L, 203, L, 180, L, 225, L, 135, M, 149, L, 68, L, 135, L, 90, M, 90, N, 68, L, 135, M, 68, N, 158, M, 135, M, 68, M, 68, M, 225, PAUSE,
								L, 135,
								L, 45, L, 68, L, 68, O, 135,
								O, 135, L, 68, L, 68,
								L, 135, L, 68, L, 45, L, 99,
								L, 135, PAUSE,
								L, 45, L, 68, L, 68, O, 135,
								P, 135,
								M, 135, M, 68, M, 135,
								L, 135, L, 135,
								L, 45, L, 68, L, 68, O, 135,
								O, 135, L, 68, L, 68,
								L, 135, L, 68, L, 45, L, 189,
								L, 203, PAUSE,
								L, 189,
								L, 162,
								L, 135, L, 135, L, 68, L, 135,
								L, 135,
								L, 45, L, 68, L, 68, O, 135,
								O, 135, L, 68, L, 68,
								L, 135, L, 68, L, 45, L, 99,
								L, 135, PAUSE, 
								L, 45, L, 68, L, 68, O, 135,
								P, 135,
								M, 135, M, 68, M, 135,
								L, 135, L, 135,
								L, 45, L, 68, L, 68, O, 135,  	
								O, 135, L, 68, L, 68,
								L, 135, L, 68, L, 45, L, 99,
								L, 203,
								L, 189,
								L, 162,
								L, 135, L, 135, L, 68, L, 135,
								R, 68, M, 135, R, 158, M, 68, M, 158, M, 68, M, 135, M, 68, M, 270,
								R, 68, M, 135, R, 158, M, 68, M, 68, M, 248,
								M, 146, M, 270, PAUSE,
								R, 68, M, 135, R, 158, M, 68, M, 158, M, 68, M, 135, M, 68, M, 270,
								L, 68, L, 135, L, 135, L, 45, L, 135, L, 248, L, 259};
								
								
int *melodiDelayPtr;
char *melodiPtr;
int playing = 0;
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
        OCR1A = 2792; //a = 660 Hz 
		break;
    case 'b': 
        OCR1A = 3613; //b = 510 Hz
		break;
    case 'c': 
		OCR1A = 2393; //c = 770 Hz
		break;        
    case 'd':  
        OCR1A = 4850; //d = 380 Hz
		break;        
    case 'e':
        OCR1A = 5759; //e = 320 Hz
		break; 
	case 'f':
		OCR1A = 4188; //f = 440 Hz
		break;
	case 'g':
		OCR1A = 3839; //g = 480 Hz
		break;
	case 'h':
		OCR1A = 4095; //h = 450 Hz
		break;
	case 'i':
		OCR1A = 4286; //i = 430 Hz
		break;
	case 'j':
		OCR1A = 2424; //j = 760 Hz
		break;
	case 'k':
		OCR1A = 2142; //k = 860 Hz
		break;
	case 'l':
		OCR1A = 2632; //l = 700 Hz
		break;
	case 'm':
		OCR1A = 3544; //m = 520 Hz
		break;
	case 'n':
		OCR1A = 3177; //n = 580 Hz
		break;
	case 'o':
		OCR1A = 3685; //o = 500 Hz
		break;
	case 'p':
		OCR1A = 2559; //p = 720 Hz
		break;
	case 'q':
		OCR1A = 2710; //q = 680 Hz
		break;
	case 'r':
		OCR1A = 2972; //r = 620 Hz
		break;
	case 's':
		OCR1A = 2835; //s = 650 Hz
		break;
	case 't':
		OCR1A = 3233; //t = 570 Hz
		break;
	case 'u':
		OCR1A = 1806; //u = 1020 Hz
		break;
	case 'w':
		OCR1A = 3150; //w = 585 Hz
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
    startMelodi(superMarioTheme, toneDelay);
  }
  
  return 0;
}
