/**************************************
* "uart.h":                           *
* Header file for Mega32 UART driver. *
* Kim Lykke Johansen, 22/11 2012      *
***************************************/ 
void InitUART(unsigned long BaudRate, unsigned char DataBit);
unsigned char CharReady();
char ReadChar();
void SendChar(char Tegn);
void SendString(char* Streng);
void SendInteger(int Tal);
/**************************************/
