#ifndef MOTOR_H
#define MOTOR_H

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include "TWI_Master.h"
#include <avr/interrupt.h>
#include <util/delay.h>

void motor_init();
void motor_set_speed(int8_t speed);
int16_t motor_readEncorder();
void motor_resetEncoder();
void motor_calibrate();

#endif
