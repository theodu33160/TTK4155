#ifndef TIMER_H
#define TIMER_H


#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>

void PWM_init();
void set_PWM(uint8_t duty);
void set_servo(int8_t xJoystick);

#endif