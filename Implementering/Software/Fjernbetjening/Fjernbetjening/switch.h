/**********************************************************
* "SWITCH.H":                                             *
* Header file for STK500 SWITCH panel driver (8 switches).*
* The SWITCH panel is connected to the PA pins.           *
* Kim Lykke Johansen, 27/9 2012                           *
***********************************************************/
void initSwitchPort();
unsigned char switchStatus();
unsigned char switchOn(unsigned char switch_nr);
/**********************************************************/