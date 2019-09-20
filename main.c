

#include "UART.h"
#include "accessMemory.c"
#include "usbCard.h"
	

int main(void)
{
	DDRB = 0xFF;
	USART_Init ( MYUBRR );
	fdevopen(USART_Transmit, USART_Receive);
	extern FILE* uart ;
	printf("0");

	
	//initialisation for SRM TEST !!!!
	MCUCR |= 1 << SRE; // enable external memory
	SFIOR |= 1 << XMM2; // disable flashing pins (we only use 12 pins for addressing)

	//acccess ADC

	//initialisation of buttons
	int buttonLEFT=0;
	int buttonRIGHT=0;

	//enable pins of port B (put 11 in PB1 and PB0 for the 2 buttons
	PORTB|= ~((1<<PB0)|(1<<PB1));

	

	while(1)
	{
				
		//_Bool btn1 = PINB & (1 << PB0); 
		//_Bool btn2 = PINB & (1 << PB1);
		//printf("Button left: %d, button right: %d \n\r", btn2, btn1);		
		readButtons();
		readJoystick();
		readSliders();

		_delay_ms(1000);
	}


/*
	//Adressing SRAM test
	while (1) SRAM_test();


	//int a=0;
    while(1)
    {
		PORTB = 0xFF;
		_delay_ms(1000);
		PORTB = 0x00;
        //USART_Transmit(USART_Receive(stream),stream);
      

		//USART_Receive();
		_delay_ms(1000);
		printf("3");
        //TODO:: Please write your application code 
    }

*/
    return 0;
}
