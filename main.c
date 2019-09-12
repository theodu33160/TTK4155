

#include "UART.h"
#include "accessMemory.c"


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

	//Test connection to ADC with the GAL
	volatile char *ext_ram = (char *) 0x1800;
	while(1)
	{
		ext_ram[0x1400] = 1;
		_delay_ms(1000);
		ext_ram[0x1400] = 0;
		_delay_ms(1000);
	}
	
	//Adressing SRAM test
	//while (1) SRAM_test();


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
    return 0;
}