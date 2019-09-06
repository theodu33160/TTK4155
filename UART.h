#ifndef F_CPU
#define F_CPU 4962000UL // 16 MHz clock speed
#endif


#define FOSC 4962000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


#include <avr/io.h>
#include <stdio.h>
#include "util/delay.h"

void USART_Init( unsigned int ubrr );

void USART_Transmit( unsigned char data );