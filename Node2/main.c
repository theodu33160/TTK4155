#include "UART.h"
#include "CAN.h"
#include <stdio.h>



int main(void)
{
	DDRB = 0xFF; // all pins in the port B act as outputs
	USART_Init ( MYUBRR );
	fdevopen(USART_Transmit, USART_Receive);
	extern FILE* uart ;
	printf("START");

	//can_init(MODE_LOOPBACK);
	//printf("Before While");


	/*can_message received_message;
	can_message message;
	message.id= 3;
	message.length= 1;
	message.data[0] = (uint8_t)'U';
	can_message_send(&message);
	_delay_ms(100);
	can_data_receive(&received_message);
	_delay_ms(1000);*/
 



	
	can_init(MODE_NORMAL);

	// 	mcp2515_write(MCP_CANCTRL, 0xab);
	// _delay_ms(10);
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
	
	 
	can_message message1;
	message1.id= 5;
	message1.length= 1;
	message1.data[0] = (uint8_t)'F';
	can_message_send(&message1);
	while(!can_transmit_complete);
	can_message msg1;
	can_data_receive(&msg1);  
	
	*/
	can_message received_message;


	while(1)
	{
		printf("In while\n\r");
		can_data_receive(&received_message);
		_delay_ms(1000);
		 
	}
    return 0;
}
