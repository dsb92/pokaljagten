/*
 * Lys_functions.c
 *
 * Created: 06/12/2012 13:44:40
 *  Author: RaZak
 */ 
#define F_CPU 3686400UL
#include "Lys_functions.h"
#include <avr/io.h>

#define MAX_LED 7

void initFrontLEDPort()
{
	//DDRA |= 0b00100000;		//PINA, 5 sat til udgang
	
	unsigned char patternA = 0b00100000;
	PORTA = PINA ^ patternA;
}

void initBackLEDPort()
{
	//DDRB |= 0b00001000; //PINB, 3 sat til udgang
	
	unsigned char patternB = 0b00001000;
	PORTB = PINB ^ patternB;
	
	TCCR0 = 0b01100010;		//Timer0 ikke-fast PWM mode, compare match set when up counting
	
}

void allLightsOn()
{
	unsigned char patternA = 0b0010000;		//BIT 6, now: active low!
	PORTA = PINA ^ patternA;
		
	OCR0 = 204;		//50% duty cycle
}

void allLightsOff()
{
	unsigned char patternA = 0b01000000;
	PORTA = PINA ^ patternA;
	
	OCR0 = 255;		//0% duty cycle, sluk
}

void brakeLightOn()
{
	OCR0 = 13;		//95%  dutycycle
}

void brakeLightOff()
{
	OCR0 = 204;		//50% duty cycle;
}