/*
 * ReverseBeebBeeb.h
 * Header-fil for STK500 ReverseBeebBeeb lyd driver
 * Created: 15-12-2012 15:55:51
 * Author: David
 */ 

#pragma once;

void initTimer0();
void initTimer1();
void startTone( char tone);
void stopTone();
void startMelodi( char *mPtr);