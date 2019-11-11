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
	fdevopen(USART_Transmit, USART_Receive);
	extern FILE* uart ;
	printf("START");


	can_init(MODE_NORMAL);
	PWM_init();
	ADC_init();
	TWI_Master_Initialise();
	sei(); // enable interrupt for TWI communication
	motor_init();
	set_speed(200);// speed out of 255

	can_message received_message;


	while(1)
	{	printf("\n\r0");
		can_data_receive(&received_message);
		if(received_message.id == ID_JOYSTICK_X)
		{
			set_servo(received_message.data);
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
		_delay_ms(6);
	}


	
    return 0;
}