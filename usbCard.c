#include "usbCard.h"

volatile int xOffstet;
volatile int yOffstet;

void initUsbCard()
{
	xOffstet = xJoystickCalibration();
	yOffstet = yJoystickCalibration();
	printf("offsets : x,y : %d ; %d\n\n",xOffstet, yOffstet);
}


uint8_t readADC(uint8_t channel)
{
	char *ext_adc = (char *) 0x1400;

	ext_adc[0] = channel;
	_delay_us(500);
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


int get_angle()
{
	uint8_t x= read_joystick(DIR_X);
	uint8_t y= read_joystick(DIR_Y);
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


int get_magnitude()
{
	uint8_t x= read_joystick(DIR_X);
	uint8_t y= read_joystick(DIR_Y);
	return (int) sqrt(x*x+y*y);
}


int get_direction()
{
	uint8_t x= read_joystick(DIR_X);
	uint8_t y= read_joystick(DIR_Y);
	int dir;
	int mag = get_magnitude();
	int angle = get_angle();
	if (mag == 0)
	{
		dir = NEUTRAL;
	}else
	{
		if (45 <= angle && angle < 135)
		{
			dir = UP;
		}
		else if (135 <= angle || angle < -135)
		{
			dir = LEFT;
		}
		else if (-135 <= angle && angle < -45)
		{
			dir = DOWN;
		}
		else if (-45 <= angle && angle < 45)
		{
			dir = RIGHT;
		}
	}
	return dir;

}


void printJoystick()
{
	printf("Y : %u; X : %d\t ",readADC(DIR_X), readADC(DIR_Y));
	uint8_t x= read_joystick(DIR_X);
	uint8_t y= read_joystick(DIR_Y);
	int angle = get_angle();
	printf("m = %d \t", get_magnitude());

	printf("X: %d %%, Y: %d %% , angle: %d \t", x, y, angle);
	printf("DIRECTION: %d\t", get_direction());
	//delay_ms(1);

}


void readSliders()
{
	printf("slider L : %d \t",readADC(LEFT_SLIDER));
	printf("slider R : %d \t",readADC(RIGHT_SLIDER));
}

void readButtons()
{

	_Bool btn1 = PINB & (1 << PB0);
	_Bool btn2 = PINB & (1 << PB1);
	_Bool btnJoystick = PINB & (1 << PB2);
	printf("Button left: %d\t, button right: %d\t button joystick: %d \n\r", btn2, btn1, btnJoystick);
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


_Bool read_button(uint8_t btn)
{
	return (_Bool)  PINB & (1 << btn);
}

uint8_t read_joystick(uint8_t dir)
{
	uint8_t result =0;
	if(dir == DIR_X) result = readADC(DIR_X) - xOffstet;
	else if(dir==DIR_Y) result = readADC(DIR_Y) - yOffstet;
	else printf("error, unknown direction");
	result = (int) result/1.275;
	return thresholds(result);
}

