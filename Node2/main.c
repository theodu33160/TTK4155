#include "UART.h"
#include "CAN.h"
#include "CAN_ID.h"
#include "timer.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRB = 0xFF; // all pins in the port B act as outputs
	USART_Init( MYUBRR );
	fdevopen(USART_Transmit, USART_Receive);
	extern FILE* uart ;
	printf("START\n\r");


	can_init(MODE_NORMAL);

	// 	mcp2515_writecan_data_receive
	// _delay_ms(10);can_data_receive
	// uint8_t data = mcp2515_read(MCP_CANCTRL);
	// PORTB &= (1 << CAN_CS);
	// printf("data: %x \n\r", data);
	// _delay_ms(3000);

	/*
	can_message message;
	message.id= 3;
	message.length= 1;
	message.data[0] = (uint8_t)'U';
	can_message_send(&message);
	while(!can_transmit_complete);
	can_message msg;
	can_data_receive(&msg); 
	*/

	can_message received_message;
	
	while(1)  
	{
		can_data_receive(&received_message);
		print_message(&received_message);
	}

	PWM_init();
	sei(); 
	set_PWM(80); //in 10µs (claires)
	
	while(1)
	{
		//printf("In while\n\r");
		//can_data_receive(&received_message);
		_delay_ms(2000);
		set_PWM(200);
		_delay_ms(2000);
		set_PWM(70);
		 
	}
    return 0;
}