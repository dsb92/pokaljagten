/********************************************************
* "SWITCH.C":                                           *
* Implementation file for the STK500 SWITCH PORT driver.*
* The SWITCHES are connected to the PA pins.            *
* Henning Hargaard, 27/9 2011                           *
*********************************************************/
#include <avr/io.h>

#define MAX_SWITCH_NR 7

// Klarg�r switch-porten
void initSwitchPort()
{
  // Switch-port = All inputs
  DDRA = PINA & 0b11011111;
}

// L�ser alle switches samtidigt
unsigned char switchStatus()
{
  return (~PINA);
}

// Returnerer TRUE, hvis switchen med nummeret
// "switch_nr" er aktiveret - ellers returneres FALSE
unsigned char switchOn(unsigned char switch_nr)
{
unsigned char mask;
  if (switch_nr <= MAX_SWITCH_NR)
  {
    mask = 0b00000001 << switch_nr;
    return (~PINA & mask);
  }
  else
    return 0;
} 