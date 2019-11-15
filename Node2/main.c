#include "timer.h"
#include "UART.h"
#include "CAN.h"
#include "ADC_driver.h"
#include "IR_driver.h"
#include <stdio.h>
#include "TWI_Master.h"
#include "motor.h"
#include "pid.h"
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
//try to set up the ¤th timer: TCNT4
	TCCR4B |= (1<<CS42);
    TCCR4B &= ~(1<<CS41);
    TCCR4B |= (1<<CS40);


	DDRB = 0xFF; // all pins in the port B act as outputs
	PORTB |= (1<<PB6); //init solenoïde
	USART_Init ( MYUBRR );
	extern FILE* uart ;
	fdevopen(USART_Transmit, USART_Receive);
	printf("START");


	can_init(MODE_NORMAL);
	PWM_init();
	ADC_init();
	motor_init();
	motor_calibrate();
	volatile struct PID_DATA motor_PID;
	pid_Init((int16_t)4,(int16_t)2,(int16_t)0,&motor_PID);
	can_message received_message;
	
	int16_t previous_time = TCNT4;
	int16_t new_time = TCNT4;
	while(1)
	{
		new_time = TCNT4;
		printf("new_time %u\t",new_time - previous_time);
		int16_t temp;
		can_data_receive(&received_message);
		//print_message(&received_message);
		//printf("PID pointer address %p", motor_PID);
		//printf("address pointer id msg %p", &received_message);
		switch (received_message.id) //this switch allow to manage the data how we want without waiting for them
		{
		case ID_QUIT:
			printf("TIME TO GO TO WORK FOR THE EXAMS");
			return 0;
			break;
		case ID_JOYSTICK_X:
			set_servo(received_message.data);
			break;
		case ID_RIGHT_SLIDER:
			temp = (uint8_t)received_message.data*40;
			printf("slider : %d\t",temp);
			break;
		case ID_BTNS:
			printf("toggling solenoid\t");
			PORTB &= ~(1<<PB6);
			_delay_ms(100);
			PORTB |= (1<<PB6);
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
		if(new_time-previous_time>16*100)
		{
			previous_time = new_time;
			motor_set_speed(pid_Controller(temp,-motor_readEncorder(),&motor_PID));
		}
	}


	
    return 0;
}