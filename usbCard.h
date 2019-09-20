#define DIR_Y 0x7
#define DIR_X 0x6
#define offset 127.5
#define LEFT_SLIDER 0x5
#define RIGHT_SLIDER 0x4
#define F_CPU 4915200
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

uint8_t readADC(uint8_t channel);

//thresholds
int thresholds(int dir);

int get_angle(int x, int y);

int get_direction(int x, int y);

int get_magnitude(int x, int y);

void readJoystick();

void readSliders();

void readButtons();




