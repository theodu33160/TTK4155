

#include "UART.h"


int main(void)
{
	DDRB = 0xFF;
	USART_Init ( MYUBRR );
	//printf("3");
	//int a=0;
    while(1)
    {
		/*PORTB = 0xFF;
		_delay_ms(1000);
		PORTB = 0x00;*/
		USART_Transmit('B');
		//USART_Receive();
		_delay_ms(1000);
		//printf("3");
        //TODO:: Please write your application code 
    }
    return 0;
}