#ifndef TIMER_H
#define TIMER_H


#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
//#include <avr/interrupt.h>

void PWM_init();
void set_PWM(uint8_t duty);
void set_servo(int xJoystick);

#endif