#ifndef MOTOR_H
#define MOTOR_H


#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include "TWI_Master.h"
#include <avr/interrupt.h>


void motor_init();
void set_speed(int8_t speed);

#endif