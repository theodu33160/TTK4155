#ifndef USBCARD_H
#define USBCARD_H

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
#define LEFT_SLIDER 0x5
#define RIGHT_SLIDER 0x4
#define F_CPU 4915200
#define PI 3.141592
#define NEUTRAL 0
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

#define BTN_RIGHT PB0
#define BTN_LEFT PB1
#define BTN_JOYSTICK PB2



void initUsbCard();

uint8_t readADC(uint8_t channel);

//thresholds
int thresholds(int dir);

int get_angle();

int get_direction();

int get_magnitude();

void printJoystick();

void readSliders();

void readButtons();

int xJoystickCalibration();

int yJoystickCalibration();

_Bool read_button(uint8_t btn);

uint8_t read_joystick(uint8_t dir);

#endif
