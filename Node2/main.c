#include "timer.h"
#include "UART.h"
#include "CAN.h"
#include "ADC_driver.h"
#include "IR_driver.h"
#include <stdio.h>
#include "TWI_Master.h"
#include "motor.h"
#include <avr/interrupt.h>

uint8_t score=250;				//Starting score
_Bool ball_lost = 0;

void blink()
{
	uint8_t save_port = PORTH;
	PORTH = 0xFF;
	while (1)
	{
	PINH = 0xFF;
	_delay_ms(1100);
	PINH = 0x00;
	_delay_ms(1100);
	}
	PORTH = save_port;
}

int main(void)
{
	DDRB = 0xFF; // all pins in the port B act as outputs
	USART_Init ( MYUBRR );
	extern FILE* uart ;
	fdevopen(USART_Transmit, USART_Receive);
	printf("START");


	can_init(MODE_NORMAL);
	PWM_init();
	ADC_init();
	motor_init();

	can_message received_message;
	
	while(1)
	{	
		printf("\n\r");
		can_data_receive(&received_message);
		switch (received_message.id) //this switch allow to manage the data how we want without waiting for them
		{
		case ID_JOYSTICK_X:
			set_servo(received_message.data);
			break;
		//case ID_RIGHT_SLIDER:
		case ID_JOYSTICK_Y:
			motor_set_speed(received_message.data);
			//printf("motor power: %d",received_message.data);
			break;
		default:
			printf("no reception or ID unused\n\r");
			break;
		}
		if (ADC_read()<500)
		{
			if (!ball_lost)
			{
				score--;
				ball_lost = 1;
			}
			printf("You loose Claire, you're score is %d", score);
		}
		else
		{
			ball_lost = 0;
		}
		printf("\tencoder: %d",motor_readEncorder());
		_delay_ms(6);
	}


	
    return 0;
}