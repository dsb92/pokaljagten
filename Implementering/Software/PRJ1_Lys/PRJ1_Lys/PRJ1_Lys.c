/*
 * PRJ1_Lys.c
 *
 * Created: 04/12/2012 12:09:52
 *  Author: RaZak
 */ 
#define F_CPU 3686400UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)		//Test af Forlys og Baglys
{
    initBackLEDPort();
	initFrontLEDPort();
	
	_delay_ms(2000);
	
	allLightsOn();		//Test alle lys tændt
	
	_delay_ms(3000);
	
	brakeLightOn();		//bremselys test tænd
	
	_delay_ms(3000);
	
	brakeLightOff();	//bremselys test sluk
	
	_delay_ms(3000);
	
	allLightsOff();		//Test alle lys sluk
	
	_delay_ms(3000);
	
	brakeLightNormal();
	
	while(1);
	
	return 0;
}