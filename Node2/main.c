#include <avr/interrupt.h>
#include <stdio.h>
#include "timer.h"
#include "UART.h"
#include "CAN.h"
#include "ADC_driver.h"
#include "IR_driver.h"
#include "TWI_Master.h"
#include "motor.h"
#include "pid.h"


// Function to debug using LEDs
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
	// Initialization of the Timer. Set a prescaler of 1024
	TCCR4B |= (1<<CS42);
    TCCR4B &= ~(1<<CS41);
    TCCR4B |= (1<<CS40);

	DDRB = 0xFF; 			// Configuration of PORTB to all outputs
	PORTB |= (1<<PB6); 		// Initialization of the pin controlling the Solenoid (always HIGH unless we press the button)
	can_message received_message; // Creating a variable to receive CAN messages
	uint8_t score=250;				// Initial score of the game
	_Bool ball_lost = 0;			// Bool to detect if the ball is crossing the line
	int16_t previous_time = TCNT4;
	int16_t current_time = TCNT4;

	// Managing the UART communication
	USART_Init (MYUBRR);  // Initializing the communication between NODE 2 and PC
	extern FILE* uart ;
	fdevopen(USART_Transmit, USART_Receive);

	// Other initializations
	can_init(MODE_NORMAL);
	PWM_init();
	IR_init();
	motor_init();
	motor_calibrate();
	struct PID_DATA motor_PID;
	pid_Init((int16_t)4,(int16_t)2,(int16_t)0,&motor_PID);

	while(1)
	{
		current_time = TCNT4;
		printf("Current_time %u\t",current_time - previous_time);
		int16_t temp;
		can_data_receive(&received_message);
		switch (received_message.id) //	Switch configured to manage the data we receive via CAN, depending on the ID of the message
		{
		case ID_QUIT:
			printf("TIME TO GO TO WORK FOR THE EXAMS");
			return 0;
			break;
		case ID_JOYSTICK_X:		// Message that is containing the Joystick X position, used to control the servo
			set_servo(received_message.data);
			break;
		case ID_RIGHT_SLIDER:	// Message that is containing the position of the right slider, used to control the DC motor
			temp = (uint8_t) received_message.data*40; // The multiplier is a scaling factor from slider to encoder values
			printf("Slider: %d\t",temp);
			break;
		case ID_BTNS:			// Message containing Button information, used to control the Solenoid
			printf("Toggling solenoid\t");
			// We toggle the PB6 during 100 ms, time that the solenoid is pushed
			PORTB &= ~(1<<PB6);
			_delay_ms(100);
			PORTB |= (1<<PB6);
			break;
		default: // If we don't receive any ID in the communication or if it's an unknown ID, break
			printf("No reception or ID unused\n\r");
			break;
		}
		// The detection of ball crossing the line
		if (ADC_read()<500) // If the IR is detecting the ball, ADC < 500
		{
			if (!ball_lost) // Control to not loose points, if the ball gets stuck in the line
			{
				score--;		// We loose points if the ball crosses
				ball_lost = 1;  // While detecting the ball, this boolean is going to be 1
			}
			printf("You loose Claire, you're score is: %d", score);
		}
		else // The ball is not in the line
		{
			ball_lost = 0; // Once the ball has moved from the line, we are going to be able to count points again
		}
		if(current_time-previous_time>16*100) // Time is increasing every 1/16 ms
		{ 	// We enter here every 100 ms
			previous_time = current_time;
			motor_set_speed(pid_Controller(temp,-motor_readEncorder(),&motor_PID));
		}
	}
    return 0;
}
