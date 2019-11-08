#include "timer.h"
#include "UART.h"
#include "CAN.h"
#include "ADC_driver.h"
#include "IR_driver.h"
#include <stdio.h>

uint8_t score=250;				//Starting score
_Bool ball_lost = 0;

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

	can_message received_message;
		
	while(1)
	{
		printf("\n\rread message\t");
		can_data_receive(&received_message);
		if(received_message.id == ID_JOYSTICK_X)
		{
			set_servo(received_message.data);
		}

		printf("adc %d",ADC_read());
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
		_delay_ms(100);
	}


	
    return 0;
}