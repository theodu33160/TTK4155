

#include "UART.h"
#include "accessMemory.c"


#define DIR_Y 0x7
#define DIR_X 0x6
#define LEFT_SLIDER 0x5
#define RIGHT_SLIDER 0x4

uint8_t getJoystick(uint8_t direction)
{
	volatile char *ext_adc = (char *) 0x1400;
	
	ext_adc[0] = direction;
	_delay_ms(20) ;
	uint8_t result = ext_adc[0];
	return result;
//	printf("%d\n", result);
}


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
	volatile char *ext_adc = (char *) 0x1400;
	while(1)
	{
		printf("Y : %d \t",getJoystick(DIR_Y));
		printf("X : %d \n",getJoystick(DIR_X));
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
