#ifndef MOTOR_H
#define MOTOR_H


#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
//#include <avr/interrupt.h>

void motor_init();
void set_speed(uint8_t duty);

#endif