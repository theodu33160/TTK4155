#include "usbCard.h"
#include <util/delay.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include <avr/io.h>


void initUsbCard()
{
	xOffstet = xJoystickCalibration();
	yOffstet = yJoystickCalibration();
	printf("offsets : x,y : %d ; %d\n\n",xOffstet, yOffstet);
}


uint8_t readADC(uint8_t channel)
{
	volatile char *ext_adc = (char *) 0x1400;
	
	ext_adc[0] = channel;
	_delay_us(500) ;
	uint8_t result = ext_adc[0];
	return result;
}


int thresholds(int dir)
{
	if (dir > -5 && dir < 5)
		dir = 0;
	if (dir > 100)
		dir = 100;
	if (dir <-100)
		dir = -100;
	return dir;
}


int get_angle(int x, int y)
{
	int angle = 0;
	if(x != 0)
	{
		angle = (int) (atan2(y,x)*180/PI);
		
	}else
	{
		if (y<0)
		{
			angle = -90;
		}
		else if (y>0)
		{
			angle = 90;
		}
	}
	return angle;
}


int get_magnitude(int x, int y)
{
	return (int) sqrt(x*x+y*y);
}


int get_direction(int x, int y)
{
	int dir;
	int mag = get_magnitude(x,y);
	int angle = get_angle(x,y);
	if (mag = 0)
	{
		dir = NEUTRAL;
	}else
	{
		if (45 < angle && angle < 135)
		{
			dir = UP;
		}
		else if (135 < angle && angle < 225)
		{
			dir = LEFT;
		}
		else if (-135 < angle && angle < -45)
		{
			dir = DOWN;
		}
		else if (-45 < angle  && angle < 0 || 0 < angle && angle < 45)
		{
			dir = RIGHT;
		}		
	}
	return dir;
	
}


void readJoystick()
{
	printf("Y : %u; X : %d\n\r ",readADC(DIR_X), readADC(DIR_Y));
	int x = readADC(DIR_X) - xOffstet;
	x = (int)x/1.275;
	int y = readADC(DIR_Y) - yOffstet;
	y = y/1.275;

	x = thresholds(x);
	y = thresholds(y);
	int angle = get_angle(x,y);
	printf("m = %d \t", get_magnitude(x,y));
	
	printf("X: %d %%, Y: %d %% , angle: %d \n\r", x, y, angle);
	printf("DIRECTION: %d\n\r", get_direction(x,y));	
	//delay_ms(1);	
	
}


void readSliders()
{
	printf("slider L : %d \n\r",readADC(LEFT_SLIDER));
	printf("slider R : %d \n\r",readADC(RIGHT_SLIDER));
}

void readButtons()
{

	_Bool btn1 = PINB & (1 << PB0); 
	_Bool btn2 = PINB & (1 << PB1);
	printf("Button left: %d, button right: %d \n\r", btn2, btn1);
}

int xJoystickCalibration()
{
//	_cli();	// desable ADC interrupt
	int temp = 0;
	for (int i =0 ; i<20;i++) temp = temp + readADC(DIR_X);
//	sei();	 // Enable ADC interrupt
	return (int)temp/20;
}

int yJoystickCalibration()
{
//	_cli();	// desable ADC interrupt
	int temp = 0;
	for (int i =0 ; i<20;i++) temp = temp + readADC(DIR_Y);
//	sei();	 // Enable ADC interrupt
	return (int) temp/20;
}

	




