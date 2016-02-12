/*
 * Class: Sound
 * Implementering af lyddriver
 * Created: 03-12-2012 19:02:14
 * Author: David Buhauer
 * 201270749
 * Version: 4 - coin "interrupt" imens main melodien spiller. 
 */ 

// PORTD.5

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Lyddriver.h"
#define F_CPU 3686400UL
#define PAUSE 2700
#define ANTAL_OVERFLOWS_reverse 450


// TONELÆNGDER FOR SUPERMARIO:

#define L 45	//100 ms
#define M 36	// 80 ms
#define N 23	// 50 ms
#define O 68	// 150 ms
#define P 90	// 200 ms
#define R 27	// 60 ms


// GLOBALE VARIABLER:

char ANTAL_OVERFLOWS_lvlcom;
char ANTAL_OVERFLOWS_coin;

unsigned int overflow_cnt = 0;


// POINTERS TIL DELAYS

int *levelcompleteDelayPtr;
int *coinDelayPtr;


// POINTERS TIL TONER 

char *levelcomplete_melodiPtr;
char *coin_melodiPtr;
char *reverse_melodiPtr;


//ARRAYS:

char LevelComplete[] = "abcdef-g-hijklm-n-opqrstt-t-t-t-uuuu";

char Coin[] = "aaaaabbbbbbbbbb";

char ReverseBeeb[] = "aaaaaa------------";


// ANTAL OVERFLOWS/DELAYS: 

int toneDelay_levelComplete[] = {90, 90, 90, 90, 90, 90, PAUSE, 90, PAUSE, 90, 90, 90, 90, 90, 90, PAUSE, 90, PAUSE, 90};

int toneDelay_coin[] = {36, 360};	 	

	
// TIMERS:

// UNDERFUNKTIONER:


void startTone_levelComplete(char tone_lvlcom, int delay_lvlcom)
{
	ANTAL_OVERFLOWS_lvlcom = delay_lvlcom;
	switch(tone_lvlcom)
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
	}
	stopTone_lvlcom(-1);
	if (tone_lvlcom != '-')
		TCCR1A |= 0b01000000;	// Toggle OCR1A on compare match
	
	// Enable Timer0 overflow interrupt
	TIMSK |= 0b00000001;
}

void startTone_coin(char tone_coin, int delay_coin)
{
	ANTAL_OVERFLOWS_coin = delay_coin;
	
	if ( tone_coin == 'a')
		OCR1A = 1842;	//a = 1000 Hz
	
	else if ( tone_coin == 'b')
		OCR1A = 1382;	//b = 1333 Hz
	
	stopTone_coin(-1);
	
	if (tone_coin != '-')
		TCCR1A |= 0b01000000;	// Toggle OCR1A on compare match
	
	// Enable Timer0 overflow interrupt
	TIMSK |= 0b00000001;
}

void startTone_reverse(char tone_reverse)
{
	if ( tone_reverse == 'a')
		OCR1A = 2792;	//a = 660 Hz
	
	stopTone_reverse();
	
	if ( tone_reverse != '-')
		TCCR1A |= 0b01000000;	// Toggle OCR1A on compare match
	
	// Enable Timer0 overflow interrupt
	TIMSK |= 0b00000001;
}


void stopTone_lvlcom(int delay_lvlcom)
{
	TCCR1A &= 0b10111111;
	ANTAL_OVERFLOWS_lvlcom = delay_lvlcom;
}

void stopTone_coin(int delay_coin)
{
	TCCR1A &= 0b10111111;
	ANTAL_OVERFLOWS_coin = delay_coin;
}

void stopTone_reverse()
{
	TCCR1A &= 0b10111111;
}


void startMelodi_levelComplete(char *levelCompletePtr, int *lvlCompleteDelayPtr)
{
	if (*levelCompletePtr )
	{
		levelcomplete_melodiPtr = levelCompletePtr;
		levelcompleteDelayPtr = lvlCompleteDelayPtr;
		startTone_levelComplete(*levelCompletePtr, *lvlCompleteDelayPtr);
		levelcomplete_melodiPtr++;
		levelcompleteDelayPtr++;
	}
}

void startMelodi_coin(char *coinPtr, int *cDelayPtr)
{
	if ( *coinPtr )
	{
		coin_melodiPtr = coinPtr;
		coinDelayPtr = cDelayPtr;
		startTone_coin(*coinPtr, *cDelayPtr);
		coin_melodiPtr++;
		coinDelayPtr++;
	}
}

void startMelodi_reverse(char *BeebPtr)	// Pointers der peger på arrayet ReverseBeebBeeb. BEMÆRK KUN 1 PARAMETER, DA ANTAL OVERFLOWS ER KONSTANT for ReverseBeeb! 
{
	if (*BeebPtr)
	{
		startTone_reverse(*BeebPtr);
		reverse_melodiPtr = BeebPtr;
		reverse_melodiPtr++;
	}
}

//FUNKTIONER

void StopLevelComplete( void )
{
	startMelodi_levelComplete(LevelComplete, toneDelay_levelComplete);
}

void DetekCoin( void )
{
	startMelodi_coin(Coin, toneDelay_coin);
}

void ReverseBeebBeeb( void )
{
	startMelodi_reverse(ReverseBeeb);
}


// INTERRUPT:

ISR(TIMER0_OVF_vect)
{
	overflow_cnt++;
	 	 
	if (overflow_cnt == ANTAL_OVERFLOWS_lvlcom )
	{
		if (*levelcomplete_melodiPtr == '-')
		{
			stopTone_lvlcom(*levelcompleteDelayPtr);
			levelcomplete_melodiPtr++;
			levelcompleteDelayPtr++;
		}
			 	 
		else if (*levelcomplete_melodiPtr == 0)
		{
			stopTone_lvlcom(0);
			// Disable Timer0 overflow interrupt
			TIMSK &= 0b11111110;
		}
			 
		else
		{
			startTone_levelComplete(*levelcomplete_melodiPtr, *levelcompleteDelayPtr);
			levelcomplete_melodiPtr++;
			levelcompleteDelayPtr++;
		}
		
		overflow_cnt = 0;
	}
		 
	else if (overflow_cnt == ANTAL_OVERFLOWS_coin)
	{
		if (*coin_melodiPtr == '-')
		{
			stopTone_coin(*coinDelayPtr);
			coin_melodiPtr++;
			coinDelayPtr++;
		}
			 	 
		else if (*coin_melodiPtr == 0)
		{
			stopTone_coin(0);
			// Disable Timer0 overflow interrupt
			TIMSK &= 0b11111110;
		}
			 
		else
		{
			startTone_coin(*coin_melodiPtr, *coinDelayPtr);
			coin_melodiPtr++;
			coinDelayPtr++;
		}
		
		overflow_cnt = 0;
	}
		
	else if ( overflow_cnt == ANTAL_OVERFLOWS_reverse)
	{
		if (*reverse_melodiPtr == '-')
		{
			stopTone_reverse();
			reverse_melodiPtr++;
		}
		
		else if (*reverse_melodiPtr == 0)
		{
			reverse_melodiPtr = ReverseBeeb;					// Sæt pointeren til at pege på første plads i ReverseBeeb arrayet og start melodien forfra.
			startTone_reverse(*reverse_melodiPtr);
			reverse_melodiPtr++;								// Inkrementere det som pointeren peger på.	
		}
		
		else
		{
			startTone_reverse(*reverse_melodiPtr);
			reverse_melodiPtr++;
		}
		overflow_cnt = 0;
	}
}