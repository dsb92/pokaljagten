/******************************************
* "LED.H":                                *
* Header file for STK500 LED driver.      *
* The LEDs are connected to PC pins.      *
* Henning Hargaard, 26/3 2012             *
*******************************************/ 

//K�rer over portC

void initLEDport();
void writeAllLEDs(unsigned char pattern);
void turnOnLED(unsigned char led_nr);
void turnOffLED(unsigned char led_nr);
void toggleLED(unsigned char led_nr);
/******************************************/
