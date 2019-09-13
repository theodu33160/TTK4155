

#include "UART.h"
#include "accessMemory.c"
#include "usbCard.c"

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
	while(1)
	{
		printf("Y : %d \t",readADC(DIR_Y));
		printf("X : %d \n",readADC(DIR_X));
//		printf("slider L : %d \n",readADC(LEFT_SLIDER));
//		printf("slider R : %d \n",readADC(RIGHT_SLIDER));
		_delay_ms(100);
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
