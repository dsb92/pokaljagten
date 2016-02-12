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
	DDRA |= 0b01000000;		//PINA, 6 sat til udgang
	
	unsigned char patternA = 0b10111111;
	PORTA = PINA & patternA;			//Det sikres at PINA 6 er sat til 0
}

void initBackLEDPort()
{
	DDRB |= 0b00001000; //PINB, 3 sat til udgang
	
	unsigned char patternB = 0b11110111;
	PORTB = PINB & patternB;			//Det sikres at PINA 3 er sat til 0
	
	TCCR0 = 0b01100001;		//Timer0 ikke-fast PWM mode, compare match set when up counting
	
}

void allLightsOn()
{
	unsigned char patternA = 0b01000000;		//BIT 6, active high
	PORTA = PINA ^ patternA;
		
	OCR0 = 26;		//10% duty cycle
}

void allLightsOff()
{
	unsigned char patternB = 0b11110111;
	PORTB = PINB & patternB;				//Bit 3 sættes til 0
	
	OCR0 = 0;		//0% duty cycle, sluk
}

void brakeLightOn()
{
	OCR0 = 255;		//100%  dutycycle
}

void brakeLightOff()
{
	OCR0 =26;		//10% duty cycle;
}

void brakeLightNormal()
{
	TCCR0 = 0b00000010;
	unsigned char patternB = 0b00001000;		//BIT 3, active high
	PORTB = PINB | patternB;
}