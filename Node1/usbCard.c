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


int8_t thresholds(int8_t dir)
{
	if (dir > -THRESHOLD && dir < THRESHOLD)
		dir = 0;
	if (dir > 100)
		dir = 100;
	if (dir <-100)
		dir = -100;
	return dir;
}

int8_t get_x()
{
	int8_t x = (int)(readADC(DIR_X) - xOffstet)/1.275;
	x = thresholds(x);
	return x;
}

int8_t get_y()
{
	int8_t y = (int)(readADC(DIR_Y) - yOffstet)/1.275;
	y = thresholds(y);
	return y;
}


int get_angle()
{
	int8_t x = get_x();

	
	int8_t y = get_y();
	
	int angle = 0;
	if(x != 0)
	{
		angle = (int) (atan2(y,x)*180/PI);
		//printf("\tangle in get_angle: %d\t",angle); 

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


uint8_t get_magnitude()
{
	int8_t x = get_x();

	
	int8_t y = get_y();

	return (int) sqrt(x*x+y*y);
}


uint8_t get_direction()
{
	uint8_t x= get_x();
	uint8_t y= get_y();
	uint8_t dir;
	uint8_t mag = get_magnitude();
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
	int8_t x= get_x(); //debug
	int8_t y= get_y(); // debug
	int angle = get_angle();
	//printf("m = %d \n\r", get_magnitude());

	printf("X: %d %%, Y: %d %% , angle: %d \t", x, y, angle);
	printf("MAG: %d\t", get_magnitude());
	printf("DIRECTION: %d\n\r", get_direction());

	_delay_ms(100);

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
	switch(btn){
	{
                        case BTN_RIGHT:
                            return PINB & (1 << PB0);
                            break;
                        case BTN_LEFT:
                           return PINB & (1 << PB1);
                            break;
                        case BTN_JOYSTICK:
                            return PINB & (1 << PB2);
                            break;
                        default:
                            break;
                    }

	
		
	}
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
