/*
 * GccApplication1.c
 *
 * Created: 30.08.2019 14:15:11
 *  Author: inakij
 */ 

#include "UART.h"



void USART_Init( unsigned int ubrr )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

int USART_Transmit( unsigned char data, FILE *file)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

int USART_Receive( FILE *file )
{// Wait for data to be received 
if ( !(UCSR0A & (1<<RXC0)) ) return UDR0;
// Get and return received data from buffer 
return UDR0;
}
