#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>


#include <avr/io.h>
#include <avr/interrupt.h>

//#include "adc.h"
//#include <interrupt.h>



#define DIR_Y 0x7
#define DIR_X 0x6
#define offset 127.5
#define LEFT_SLIDER 0x5
#define RIGHT_SLIDER 0x4
#define F_CPU 4915200
#define PI 3.141592
#define NEUTRAL 0
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

volatile int xOffstet;
volatile int yOffstet;

void initUsbCard();

uint8_t readADC(uint8_t channel);

//thresholds
int thresholds(int dir);

int get_angle(int x, int y);

int get_direction(int x, int y);

int get_magnitude(int x, int y);

void readJoystick();

void readSliders();

void readButtons();

int xJoystickCalibration();

int yJoystickCalibration();

void init_OLED();

void write_c(uint8_t data);
