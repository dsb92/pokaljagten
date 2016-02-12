/*
 * SuperMario.h
 * Header-fil for STK500 Super-Mario lyd driver
 * Created: 15-12-2012 15:36:57
 * Author: David Buhauer
 */ 

#pragma once;

void initTimer0();
void initTimer1();
void startTone( char tone, int delay);
void stopTone( int delay );
void startMelodi( char *mPtr, int *mDelayPtr );