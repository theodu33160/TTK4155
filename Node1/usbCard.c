#include "usbCard.h"

volatile int xOffstet;
volatile int yOffstet;

//initialisation of the USB card
void initUsbCard()
{
	xOffstet = xJoystickCalibration();
	yOffstet = yJoystickCalibration();
	printf("offsets : x,y : %d ; %d\n\n",xOffstet, yOffstet);
}

//function to get the value read by the ADC for the required channel 
uint8_t readADC(uint8_t channel)
{
	char *ext_adc = (char *) 0x1400; // address of the adc where we want to write the channel
	ext_adc[0] = channel; //channel written to this adc address
	_delay_us(500); // delay to let the adc do its measurement
	uint8_t result = ext_adc[0]; // get the channel we want to read
	return result; //return the channel the adc read
}

//function to create thresholds for the joystick 
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

//function to get the position of the joystick on the X axe
int8_t get_x()
{
	int8_t x = (int)(readADC(DIR_X) - xOffstet)/1.275;
	x = thresholds(x);
	return x;
}

//function to get the position of the joystick on the Y axe
int8_t get_y()
{
	int8_t y = (int)(readADC(DIR_Y) - yOffstet)/1.275;
	y = thresholds(y);
	return y;
}

//function to get the angle of the joystick
int16_t get_angle()
{
	int8_t x = get_x();
	int8_t y = get_y();
	int angle = 0;
	if(x != 0)
	{
		angle = (int) (atan2(y,x)*180/PI);
    }
    else
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

//function to get the magnitude of the joystick position (how far is it pushed into a direction)
uint8_t get_magnitude()
{
	int8_t x = get_x();
	int8_t y = get_y();
	return (int) sqrt(x*x+y*y);
}

//function to get the direction of the joystick : UP, DOWN, LEFT or RIGHT
uint8_t get_direction()
{
	uint8_t x= get_x();
	uint8_t y= get_y();
	uint8_t dir;
	uint8_t mag = get_magnitude();
    int16_t angle = get_angle();
	if (mag <= 50)
	{
		dir = NEUTRAL;
	}
	else
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

//function to print all information about the position of the joystick
void printJoystick()
{
	printf("Y : %u; X : %d\t ",readADC(DIR_X), readADC(DIR_Y));
	int8_t x= get_x(); //debug
	int8_t y= get_y(); // debug
	int angle = get_angle();
	printf("X: %d %%, Y: %d %% , angle: %d \t", x, y, angle);
	printf("MAG: %d\t", get_magnitude());
	printf("DIRECTION: %d\n\r", get_direction());
}

//function to print the position of the touch on the sliders
void readSliders()
{
	printf("slider L : %d \t",readADC(LEFT_SLIDER));
	printf("slider R : %d \t",readADC(RIGHT_SLIDER));
}

//function to get the position of the touch on the left slider
uint8_t get_leftSlider()
{
    return readADC(LEFT_SLIDER);
}


//function to get the position of the touch on the right slider
uint8_t get_rightSlider()
{
    return readADC(RIGHT_SLIDER);
}

//function to calibrate the x position of the joystick
uint8_t xJoystickCalibration()
{
	int temp = 0;
    for (uint8_t i =0 ; i<20;i++) temp = temp + readADC(DIR_X);
    return (uint8_t) (temp/20);
}

//function to calibrate the y position of the joystick
uint8_t yJoystickCalibration()
{
	int temp = 0;
    for (uint8_t i =0 ; i<20;i++) temp = temp + readADC(DIR_Y);
    return (uint8_t) (temp/20);
}

//function that returns 1 if the button btn is pressed, otherwise returns 0
_Bool read_button(uint8_t btn)
{
	switch(btn)
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

/// function that returns a number linked to which buttons are pressed
uint8_t read_buttons()
{
	return read_button(BTN_RIGHT)+read_button(BTN_LEFT)<<1+read_button(BTN_JOYSTICK)<<2;
}

///function that returns the position of the joystick according to the required direction dir 
int8_t get_joystick(uint8_t dir)
{
	int result =0;
	if(dir == DIR_X) result = readADC(DIR_X) - xOffstet;
	else if(dir==DIR_Y) result = readADC(DIR_Y) - yOffstet;
	else printf("error, unknown direction");
	result = (int8_t) (result/1.275);
	return thresholds(result);
}

//function that returns filtered position of the joystick according to the required direction dir 
//and the number n of positions we want to mesure before returning the average position 
int8_t get_joystick_filtered(uint8_t dir,uint8_t n)
{
	int16_t temp = 0;
    for(uint8_t i =0;i<n;i++)
	{
		temp+= get_joystick(dir);
		_delay_us(100);
	}
	return (int8_t) (temp/n);
}
